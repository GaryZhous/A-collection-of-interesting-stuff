use std::collections::HashMap;
use std::sync::{Arc, Mutex};
use std::sync::Once;

pub struct LazyCache<K, V> {
    values: Arc<Mutex<HashMap<K, V>>>,
    init_once: Once,
}

impl<K, V> LazyCache<K, V>
where
    K: std::hash::Hash + Eq,
{
    pub fn new() -> Self {
        LazyCache {
            values: Arc::new(Mutex::new(HashMap::new())),
            init_once: Once::new(),
        }
    }

    pub fn get_or_try_init<F>(&self, key: K, initializer: F) -> V
    where
        F: FnOnce() -> V,
    {
        // Try to lock the mutex and check if the key exists
        let mut values = self.values.lock().unwrap();
        if let Some(value) = values.get(&key) {
            return value.clone();
        }

        // First-time initialization with single-flight
        let mut value = initializer();
        self.init_once.call_once(|| { // Ensures that initialization only happens once
            values.insert(key, value.clone());
        });

        value
    }

    pub fn get_or_init<F>(&self, key: K, initializer: F) -> V
    where
        F: FnOnce() -> V,
    {
        self.get_or_try_init(key, initializer)
    }
}

fn main() {
    let cache: LazyCache<String, i32> = LazyCache::new();
    let key = "item1".to_string();

    // Concurrent initialization example
    let handles: Vec<_> = (0..10)
        .map(|i| {
            let cache = &cache;
            std::thread::spawn(move || {
                let value = cache.get_or_try_init(key.clone(), || {
                    println!("Initializing value for {} from thread {}", key, i);
                    i
                });
                println!("Value for {} is {} from thread {}", key, value, i);
            })
        })
        .collect();

    for handle in handles {
        handle.join().unwrap();
    }
}