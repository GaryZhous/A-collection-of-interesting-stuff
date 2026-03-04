use std::collections::HashMap;
use std::hash::Hash;
use std::sync::{Arc, Condvar, Mutex};

#[derive(Debug, Default)]
pub struct LazyCache<K, V> {
    values: Mutex<HashMap<K, Arc<V>>>,
    in_flight: Mutex<HashMap<K, Arc<InFlight>>>,
}

#[derive(Debug, Default)]
struct InFlight {
    done: Mutex<bool>,
    cv: Condvar,
}

impl<K, V> LazyCache<K, V>
where
    K: Eq + Hash + Clone,
{
    pub fn new() -> Self {
        Self::default()
    }

    pub fn get(&self, key: &K) -> Option<Arc<V>> {
        self.values.lock().expect("mutex poisoned").get(key).cloned()
    }

    pub fn get_or_init(&self, key: K, compute: impl FnOnce(&K) -> V) -> Arc<V> {
        self.get_or_try_init(key, |k| Ok::<V, ()>(compute(k)))
            .expect("infallible")
    }

    pub fn get_or_try_init<E>(
        &self,
        key: K,
        compute: impl FnOnce(&K) -> Result<V, E>,
    ) -> Result<Arc<V>, E> {
        // Fast path
        if let Some(v) = self.get(&key) {
            return Ok(v);
        }

        // Establish single-flight for this key
        let (gate, i_am_leader) = {
            let mut flights = self.in_flight.lock().expect("mutex poisoned");
            if let Some(existing) = flights.get(&key) {
                (existing.clone(), false)
            } else {
                let gate = Arc::new(InFlight::default());
                flights.insert(key.clone(), gate.clone());
                (gate, true)
            }
        };

        if i_am_leader {
            // Compute outside locks
            let computed = compute(&key)?;

            let computed = Arc::new(computed);
            // Store result
            {
                let mut vals = self.values.lock().expect("mutex poisoned");
                vals.insert(key.clone(), computed.clone());
            }
            // Mark done + notify
            {
                let mut done = gate.done.lock().expect("mutex poisoned");
                *done = true;
                gate.cv.notify_all();
            }
            // Cleanup in-flight entry
            {
                let mut flights = self.in_flight.lock().expect("mutex poisoned");
                flights.remove(&key);
            }
            Ok(computed)
        } else {
            // Wait for leader
            let mut done = gate.done.lock().expect("mutex poisoned");
            while !*done {
                done = gate.cv.wait(done).expect("mutex poisoned");
            }
            // Now value must exist
            Ok(self
                .get(&key)
                .expect("single-flight completed but value missing"))
        }
    }

    pub fn clear(&self) {
        self.values.lock().expect("mutex poisoned").clear();
        self.in_flight.lock().expect("mutex poisoned").clear();
    }

    pub fn len(&self) -> usize {
        self.values.lock().expect("mutex poisoned").len()
    }
}

fn main() {
    let cache: Arc<LazyCache<String, usize>> = Arc::new(LazyCache::new());
    let key = "item1".to_string();

    let handles: Vec<_> = (0..10)
        .map(|i| {
            let cache = cache.clone();
            let key = key.clone();
            std::thread::spawn(move || {
                let v = cache.get_or_init(key, |_| {
                    // Only one thread should print this for the key
                    println!("Computing in thread {}", i);
                    42
                });
                println!("Got {} in thread {}", v, i);
            })
        })
        .collect();

    for h in handles {
        h.join().unwrap();
    }
}
