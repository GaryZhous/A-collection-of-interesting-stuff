// main.rs
//
// Build/run (needs Cargo.toml dependency):
// tokio = { version = "1", features = ["full"] }
//
// This single file demonstrates BOTH:
//   A) std::thread concurrency:
//        - Arc<Mutex<_>> shared counter
//        - Arc<RwLock<_>> read-heavy shared data
//        - mpsc channels as a work queue
//   B) Tokio async concurrency:
//        - tokio::sync::{Mutex, RwLock}
//        - tokio::sync::mpsc channels
//        - many async tasks on the runtime
//
// ------------------------------------------------------------

use std::sync::{mpsc, Arc, Mutex, RwLock};
use std::thread;
use std::time::Duration;

// --------------------
// Fake "CPU work"
// --------------------
fn expensive_cpu(x: u64) -> u64 {
    (0..50_000).fold(x, |acc, i| acc.wrapping_mul(31).wrapping_add(i))
}

// ============================================================
// A) std::thread demo (Mutex + RwLock + channels)
// ============================================================
fn demo_std_threads() {
    println!("\n========== std::thread demo ==========");

    // 1) Shared mutable state: Arc<Mutex<_>>
    let counter = Arc::new(Mutex::new(0u64));

    // 2) Read-heavy shared data: Arc<RwLock<_>>
    let shared_data = Arc::new(RwLock::new(vec![10, 20, 30]));

    // 3) Work queue: channels
    let (job_tx, job_rx) = mpsc::channel::<u64>();
    let (res_tx, res_rx) = mpsc::channel::<(u64, u64)>();

    // std::sync::mpsc::Receiver isn't cloneable; simplest “one queue, many workers”:
    // wrap receiver with Arc<Mutex<_>> so workers take turns calling recv().
    let job_rx = Arc::new(Mutex::new(job_rx));

    // Spawn a writer that updates the RwLock once.
    {
        let shared_data = Arc::clone(&shared_data);
        thread::spawn(move || {
            let mut w = shared_data.write().unwrap();
            w.push(99);
            println!("[std writer] updated shared_data");
        })
        .join()
        .unwrap();
    }

    // Spawn workers
    let mut handles = Vec::new();
    for wid in 0..4 {
        let counter = Arc::clone(&counter);
        let shared_data = Arc::clone(&shared_data);
        let job_rx = Arc::clone(&job_rx);
        let res_tx = res_tx.clone();

        handles.push(thread::spawn(move || loop {
            // Receive one job (serialized by Mutex on receiver)
            let job = {
                let rx_guard = job_rx.lock().unwrap();
                rx_guard.recv()
            };

            let job = match job {
                Ok(j) => j,
                Err(_) => break, // channel closed
            };

            // Read shared data (many readers can do this at once)
            {
                let r = shared_data.read().unwrap();
                println!("[std worker {wid}] read shared_data = {:?}", *r);
            }

            // CPU work
            let out = expensive_cpu(job);

            // Update shared counter (exclusive)
            {
                let mut c = counter.lock().unwrap();
                *c += 1;
            }

            // Send result
            res_tx.send((job, out)).unwrap();
        }));
    }

    drop(res_tx); // main doesn't need a sender

    // Send jobs
    for j in 1..=10 {
        job_tx.send(j).unwrap();
    }
    drop(job_tx); // close => workers exit

    // Read results
    for (job, out) in res_rx.iter() {
        println!("[std result] job {job} -> {out}");
    }

    for h in handles {
        h.join().unwrap();
    }

    println!(
        "[std final] processed jobs = {}",
        *counter.lock().unwrap()
    );
    println!(
        "[std final] shared_data = {:?}",
        *shared_data.read().unwrap()
    );
}

// ============================================================
// B) Tokio demo (async tasks + tokio Mutex/RwLock + tokio mpsc)
// ============================================================
async fn demo_tokio() {
    println!("\n========== tokio demo ==========");

    use tokio::sync::{mpsc as tokio_mpsc, Mutex as TokioMutex, RwLock as TokioRwLock};

    // 1) Shared mutable state: Arc<tokio::sync::Mutex<_>>
    let counter = Arc::new(TokioMutex::new(0u64));

    // 2) Read-heavy shared data: Arc<tokio::sync::RwLock<_>>
    let shared_data = Arc::new(TokioRwLock::new(vec![100, 200, 300]));

    // 3) Work queue: tokio mpsc
    let (job_tx, job_rx) = tokio_mpsc::channel::<u64>(64);
    let (res_tx, mut res_rx) = tokio_mpsc::channel::<(u64, u64)>(64);

    // tokio mpsc::Receiver also isn’t cloneable; common pattern:
    // put receiver behind a tokio Mutex so multiple tasks can recv() in a loop.
    let job_rx = Arc::new(TokioMutex::new(job_rx));

    // Writer task modifies RwLock
    {
        let shared_data = Arc::clone(&shared_data);
        tokio::spawn(async move {
            let mut w = shared_data.write().await;
            w.push(999);
            println!("[tokio writer] updated shared_data");
        })
        .await
        .unwrap();
    }

    // Spawn async workers
    let mut joins = Vec::new();
    for wid in 0..6 {
        let counter = Arc::clone(&counter);
        let shared_data = Arc::clone(&shared_data);
        let job_rx = Arc::clone(&job_rx);
        let res_tx = res_tx.clone();

        joins.push(tokio::spawn(async move {
            loop {
                // Receive one job (serialized by TokioMutex on receiver)
                let job_opt = {
                    let mut rx_guard = job_rx.lock().await;
                    rx_guard.recv().await
                };

                let job = match job_opt {
                    Some(j) => j,
                    None => break, // channel closed
                };

                // Read shared data concurrently
                {
                    let r = shared_data.read().await;
                    println!("[tokio worker {wid}] read shared_data = {:?}", *r);
                }

                // Simulate async-friendly delay (I/O-like)
                tokio::time::sleep(Duration::from_millis(10)).await;

                // If you *must* do CPU work in Tokio, use spawn_blocking:
                let out = tokio::task::spawn_blocking(move || expensive_cpu(job)).await.unwrap();

                // Update shared counter
                {
                    let mut c = counter.lock().await;
                    *c += 1;
                }

                // Send result
                if res_tx.send((job, out)).await.is_err() {
                    break;
                }
            }
        }));
    }

    drop(res_tx); // main task doesn't need a sender

    // Produce jobs
    for j in 1..=12 {
        job_tx.send(j).await.unwrap();
    }
    drop(job_tx); // close => workers exit

    // Collect results
    while let Some((job, out)) = res_rx.recv().await {
        println!("[tokio result] job {job} -> {out}");
    }

    // Wait workers
    for j in joins {
        let _ = j.await;
    }

    println!(
        "[tokio final] processed jobs = {}",
        *counter.lock().await
    );
    println!(
        "[tokio final] shared_data = {:?}",
        *shared_data.read().await
    );
}

// ============================================================
// Main: run std demo + tokio demo in one file
// ============================================================
#[tokio::main(flavor = "multi_thread", worker_threads = 4)]
async fn main() {
    demo_std_threads();
    demo_tokio().await;
}
