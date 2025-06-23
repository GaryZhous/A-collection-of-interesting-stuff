use std::collections::HashMap;
use std::sync::{Arc, Mutex};
use std::hash::Hash;
// Inspired by Jack's Goose commit: https://github.com/block/goose/pull/2992
// Define a generic lazy cache structure
struct LazyCache<K, V>
where
    K: Eq + Hash + Clone,
{
    compute: Box<dyn Fn(&K) -> V + Send + Sync>,
    store: Arc<Mutex<HashMap<K, V>>>,
}

impl<K, V> LazyCache<K, V>
where
    K: Eq + Hash + Clone,
    V: Clone,
{
    fn new<F>(func: F) -> Self
    where
        F: Fn(&K) -> V + Send + Sync + 'static,
    {
        LazyCache {
            compute: Box::new(func),
            store: Arc::new(Mutex::new(HashMap::new())),
        }
    }

    fn get(&self, key: K) -> V {
        let mut store = self.store.lock().unwrap();
        if let Some(value) = store.get(&key) {
            return value.clone();
        }

        let value = (self.compute)(&key);
        store.insert(key.clone(), value.clone());
        value
    }
}

fn main() {
    // Create a lazy cache that computes the square of an integer
    let cache = LazyCache::new(|key: &u32| {
        println!("Computing for {}", key);
        key * key
    });

    println!("Result: {}", cache.get(10)); // Will compute
    println!("Result: {}", cache.get(10)); // Will reuse
}
