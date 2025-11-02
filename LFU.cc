#include <bits/stdc++.h>
using namespace std;

class LFUCache {
private:
    int capacity;
    int minFreq;

    // key -> (value, freq)
    unordered_map<int, pair<int, int>> keyValueFreq;

    // freq -> list of keys (order of insertion = recency)
    unordered_map<int, list<int>> freqList;

    // key -> iterator in freqList[freq]
    unordered_map<int, list<int>::iterator> keyIter;

public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        this->minFreq = 0;
    }

    int get(int key) {
        if (keyValueFreq.find(key) == keyValueFreq.end())
            return -1;

        // extract old frequency
        int freq = keyValueFreq[key].second;
        int value = keyValueFreq[key].first;

        // erase from old freq list
        freqList[freq].erase(keyIter[key]);
        if (freqList[freq].empty()) {
            freqList.erase(freq);
            if (minFreq == freq)
                minFreq++;
        }

        // update frequency
        freq++;
        keyValueFreq[key].second = freq;
        freqList[freq].push_front(key);
        keyIter[key] = freqList[freq].begin();

        return value;
    }

    void put(int key, int value) {
        if (capacity == 0) return;

        // if already present, update and promote frequency
        if (keyValueFreq.find(key) != keyValueFreq.end()) {
            keyValueFreq[key].first = value;
            get(key); // reuse get() to handle frequency increment
            return;
        }

        // if at capacity, evict LFU (least freq + oldest)
        if (keyValueFreq.size() == capacity) {
            int oldKey = freqList[minFreq].back();
            freqList[minFreq].pop_back();

            if (freqList[minFreq].empty())
                freqList.erase(minFreq);

            keyValueFreq.erase(oldKey);
            keyIter.erase(oldKey);
        }

        // insert new key
        keyValueFreq[key] = {value, 1};
        freqList[1].push_front(key);
        keyIter[key] = freqList[1].begin();
        minFreq = 1;
    }
};
