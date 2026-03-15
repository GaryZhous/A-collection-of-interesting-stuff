/*
  Design a data structure that follows the constraints of a Least Frequently Used (LFU) cache.
  Implement the LFUCache class:
  - LFUCache(int capacity) Initialize the LFU cache with positive size capacity.
  - int get(int key) Return the value of the key if the key exists, otherwise return -1.
  - void put(int key, int value) Update the value of the key if the key exists. Otherwise,
    add the key-value pair to the cache. If the number of keys exceeds the capacity from this
    operation, evict the least frequently used key. For ties, the least recently used key among
    them is evicted.
  - The functions get and put must each run in O(1) average time complexity.
*/
#include <list>
#include <unordered_map>

class LFUCache {
private:
    int capacity;
    int minFreq;

    // key -> (value, freq)
    std::unordered_map<int, std::pair<int, int>> keyValueFreq;

    // freq -> list of keys (front = most recently accessed, back = eviction candidate)
    std::unordered_map<int, std::list<int>> freqList;

    // key -> iterator in freqList[freq]
    std::unordered_map<int, std::list<int>::iterator> keyIter;

    void incrementFreq(int key) {
        int freq = keyValueFreq[key].second;

        freqList[freq].erase(keyIter[key]);
        if (freqList[freq].empty()) {
            freqList.erase(freq);
            if (minFreq == freq)
                minFreq++;
        }

        freq++;
        keyValueFreq[key].second = freq;
        freqList[freq].push_front(key);
        keyIter[key] = freqList[freq].begin();
    }

public:
    LFUCache(int capacity) : capacity(capacity), minFreq(0) {}

    int get(int key) {
        if (keyValueFreq.find(key) == keyValueFreq.end())
            return -1;

        incrementFreq(key);
        return keyValueFreq[key].first;
    }

    void put(int key, int value) {
        if (capacity <= 0) return;

        // if already present, update value and promote frequency
        if (keyValueFreq.find(key) != keyValueFreq.end()) {
            keyValueFreq[key].first = value;
            incrementFreq(key);
            return;
        }

        // if at capacity, evict LFU (least freq + oldest among ties)
        if (static_cast<int>(keyValueFreq.size()) == capacity) {
            int oldKey = freqList[minFreq].back();
            freqList[minFreq].pop_back();

            if (freqList[minFreq].empty())
                freqList.erase(minFreq);

            keyValueFreq.erase(oldKey);
            keyIter.erase(oldKey);
        }

        // insert new key with frequency 1
        keyValueFreq[key] = {value, 1};
        freqList[1].push_front(key);
        keyIter[key] = freqList[1].begin();
        minFreq = 1;
    }
};
