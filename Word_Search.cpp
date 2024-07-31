/*Given an m x n board of characters and a list of strings words, provided with a list of strings to be found, find all the matched words on the board.
  Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. 
  The same letter cell may not be used more than once in a word.*/

class TrieNode {
public:
    TrieNode* children[26];
    bool isEndOfWord;
    
    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
    }
};

class Trie {
public:
    TrieNode* root;
    
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }
    
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (node->children[index] == nullptr)
                return false;
            node = node->children[index];
        }
        return true;
    }
    
    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (node->children[index] == nullptr)
                return false;
            node = node->children[index];
        }
        return node->isEndOfWord;
    }
};

//use of Trie and DFS to find all matched words on the board
class Word_Search{
private:
    Trie trie;
    unordered_set<string> foundWords;
    int m, n;

    void dfs(vector<vector<char>>& board, int i, int j, TrieNode* node, string currentWord) {
        char c = board[i][j];
        if (c == '#' || node->children[c - 'a'] == nullptr) return;

        node = node->children[c - 'a'];
        currentWord += c;

        if (node->isEndOfWord) {
            foundWords.insert(currentWord);
        }

        board[i][j] = '#'; // Mark as visited

        if (i > 0) dfs(board, i - 1, j, node, currentWord);
        if (j > 0) dfs(board, i, j - 1, node, currentWord);
        if (i < m - 1) dfs(board, i + 1, j, node, currentWord);
        if (j < n - 1) dfs(board, i, j + 1, node, currentWord);

        board[i][j] = c; // Unmark as visited
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) { 
        m = board.size();
        n = board[0].size();

        // Build Trie
        for (string& word : words) {
            trie.insert(word);
        }

        // Start DFS from each cell
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                dfs(board, i, j, trie.root, "");
            }
        }

        return vector<string>(foundWords.begin(), foundWords.end());
    }
};
