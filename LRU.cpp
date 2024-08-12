/*
  Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.
  Implement the LRUCache class:
  -LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
  -int get(int key) Return the value of the key if the key exists, otherwise return -1.
  -void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
  -The functions get and put must each run in O(1) average time complexity.
*/

class LRUCache {
private:
    int capacity;
    std::list<std::pair<int, int>> cache; // Doubly linked list to store keys and values
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> map; // Hash map to store key and iterator to the corresponding list node

public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        auto it = map.find(key);
        if (it == map.end()) {
            return -1;
        } else {
            cache.splice(cache.begin(), cache, it->second); // Move the accessed node to the front (most recently used)
            return it->second->second; // Return the value of the node
        }
    }

    void put(int key, int value) {
        auto it = map.find(key);
        if (it != map.end()) {
            // If key exists, update the value and move the node to the front
            it->second->second = value;
            cache.splice(cache.begin(), cache, it->second);
        } else {
            // If the cache is full, remove the least recently used item
            if (cache.size() == capacity) {
                int lruKey = cache.back().first;
                cache.pop_back();
                map.erase(lruKey);
            }
            // Insert the new key-value pair
            cache.emplace_front(key, value);
            map[key] = cache.begin();
        }
    }
};
