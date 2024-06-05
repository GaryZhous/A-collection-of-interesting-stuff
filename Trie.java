import java.util.*;
import dacheng.utils.*;
class TrieNode {
    public TrieNode children[] = new TrieNode[26];
    public boolean isEndOfWord;
    
    public TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; ++i) {
            children[i] = null;
        }
    }
};

class Trie {
    /** Initialize your data structure here. */
    public TrieNode root;
    
    public Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    public void insert(String word) {
        TrieNode node = root;
        for (char c : word.toCharArray()) {
            int index = c - 'a';
            if (node.children[index] == null) {
                node.children[index] = new TrieNode();
            }
            node = node.children[index];
        }
        node.isEndOfWord = true;
    }
    
    /** Returns if the word is in the trie. */
    public boolean search(String word) {
        TrieNode node = root;
        for (char c : word.toCharArray()) {
            int index = c - 'a';
            if (node.children[index] == null)
                return false;
            node = node.children[index];
        }
        return node.isEndOfWord;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    public boolean startsWith(String prefix) {
        TrieNode node = root;
        for (char c : prefix.toCharArray()) {
            int index = c - 'a';
            if (node.children[index] == null)
                return false;
            node = node.children[index];
        }
        return true;
    }
}
