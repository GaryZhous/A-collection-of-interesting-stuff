import java.util.*;
//Least freuqently used Cache aka LFU implementation in Java
class LFUCache {
    private final int capacity;
    private int minFrequency;
    private final Map<Integer, Integer> keyToValue;
    private final Map<Integer, Integer> keyToFrequency;
    private final Map<Integer, LinkedHashSet<Integer>> frequencyToKeys;

    public LFUCache(int capacity) {
        this.capacity = capacity;
        this.minFrequency = 0;
        this.keyToValue = new HashMap<>();
        this.keyToFrequency = new HashMap<>();
        this.frequencyToKeys = new HashMap<>();
    }

    public int get(int key) {
        if (!keyToValue.containsKey(key)) {
            return -1;
        }
        // Increase the frequency of the key
        int frequency = keyToFrequency.get(key);
        keyToFrequency.put(key, frequency + 1);

        // Remove the key from the current frequency list
        frequencyToKeys.get(frequency).remove(key);

        // If this was the last key in the frequency list and this was the min frequency, update minFrequency
        if (frequencyToKeys.get(frequency).isEmpty()) {
            frequencyToKeys.remove(frequency);
            if (frequency == minFrequency) {
                minFrequency++;
            }
        }

        // Add the key to the new frequency list
        frequencyToKeys.computeIfAbsent(frequency + 1, k -> new LinkedHashSet<>()).add(key);
        return keyToValue.get(key);
    }

    public void put(int key, int value) {
        if (capacity == 0) {
            return;
        }

        // If the key is already present, update the value and its frequency
        if (keyToValue.containsKey(key)) {
            keyToValue.put(key, value);
            get(key); // To increase the frequency
            return;
        }

        // If the cache is full, evict the least frequently used key
        if (keyToValue.size() >= capacity) {
            // Get the least frequently used key (minFrequency)
            int keyToEvict = frequencyToKeys.get(minFrequency).iterator().next();
            frequencyToKeys.get(minFrequency).remove(keyToEvict);

            // Remove the key if it's the last one with this frequency
            if (frequencyToKeys.get(minFrequency).isEmpty()) {
                frequencyToKeys.remove(minFrequency);
            }

            keyToValue.remove(keyToEvict);
            keyToFrequency.remove(keyToEvict);
        }

        // Add the new key-value pair
        keyToValue.put(key, value);
        keyToFrequency.put(key, 1);
        frequencyToKeys.computeIfAbsent(1, k -> new LinkedHashSet<>()).add(key);
        minFrequency = 1; // Since it's a new key, its frequency is 1, so minFrequency is reset to 1
    }
