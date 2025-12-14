/*
  Design a search autocomplete system for a search engine. Users may input a sentence (at least one word and end with a special character '#').
  
  • You are given a string array sentences and an integer array times both of length n where sentences[i] is a previously typed sentence and times[i] is the corresponding number of times the sentence was typed. For each input character except '#', return the top 3 historical hot sentences that have the same prefix as the part of the sentence already typed.
  • Here are the specific rules:
      1. The hot degree for a sentence is defined as the number of times a user typed the exactly same sentence before.
      2. The returned top 3 hot sentences should be sorted by hot degree (The first is the hottest one). If several sentences have the same hot degree, use ASCII-code order (smaller one appears first).
      3. If less than 3 hot sentences exist, return as many as you can.
      4. When the input is a special character, it means the sentence ends, and in this case, you need to return an empty list.
  • Implement the AutocompleteSystem class:
      1. AutocompleteSystem(String[] sentences, int[] times) Initializes the object with the sentences and times arrays.
      2. List<String> input(char c) This indicates that the user typed the character c.
      3. Returns an empty array [] if c == '#' and stores the inputted sentence in the system.
      4. Returns the top 3 historical hot sentences that have the same prefix as the part of the sentence already typed. If there are fewer than 3 matches, return them all.
*/

import java.util.*;

class AutocompleteSystem {

    private static class TrieNode {
        TrieNode[] next = new TrieNode[128]; // ASCII
        List<String> top = new ArrayList<>(); // up to 3 best sentences for this prefix
    }

    private final TrieNode root = new TrieNode();
    private final Map<String, Integer> freq = new HashMap<>();
    private final StringBuilder cur = new StringBuilder();
    private TrieNode curNode = root;

    public AutocompleteSystem(String[] sentences, int[] times) {
        for (int i = 0; i < sentences.length; i++) {
            String s = sentences[i];
            freq.put(s, freq.getOrDefault(s, 0) + times[i]);
            insertOrUpdateCaches(s);
        }
    }

    public List<String> input(char c) {
        if (c == '#') {
            String sentence = cur.toString();
            freq.put(sentence, freq.getOrDefault(sentence, 0) + 1);

            // Update trie caches along the path of this sentence
            insertOrUpdateCaches(sentence);

            // reset state
            cur.setLength(0);
            curNode = root;
            return new ArrayList<>();
        }

        cur.append(c);

        // walk trie for current prefix
        if (curNode != null) {
            if (curNode.next[c] == null) curNode.next[c] = new TrieNode();
            curNode = curNode.next[c];
            return new ArrayList<>(curNode.top);
        }

        // if prefix path somehow absent (shouldn’t happen with above), no matches
        return new ArrayList<>();
    }

    // Inserts sentence into trie (creating nodes) and refreshes top-3 caches along the path
    private void insertOrUpdateCaches(String sentence) {
        TrieNode node = root;
        for (int i = 0; i < sentence.length(); i++) {
            char ch = sentence.charAt(i);
            if (node.next[ch] == null) node.next[ch] = new TrieNode();
            node = node.next[ch];
            refreshTop(node, sentence);
        }
    }

    // Ensure node.top contains best 3 sentences for this prefix using freq + ASCII tie-break
    private void refreshTop(TrieNode node, String sentence) {
        if (!node.top.contains(sentence)) node.top.add(sentence);

        node.top.sort((a, b) -> {
            int fa = freq.getOrDefault(a, 0);
            int fb = freq.getOrDefault(b, 0);
            if (fa != fb) return Integer.compare(fb, fa); // higher freq first
            return a.compareTo(b); // ASCII order
        });

        if (node.top.size() > 3) {
            node.top = new ArrayList<>(node.top.subList(0, 3));
        }
    }
}
