#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/*
 * Detecting cycle in a Directed Graph
 * We use DFS and track the recursion stack to find back edges that indicate a cycle.
 */
bool isCyclicDirectedUtil(int v, vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& recStack) {
    if (!visited[v]) {
        visited[v] = true;
        recStack[v] = true;

        for (int neighbor : adj[v]) {
            if (!visited[neighbor] && isCyclicDirectedUtil(neighbor, adj, visited, recStack)) {
                return true;
            } else if (recStack[neighbor]) {
                return true;
            }
        }
    }

    recStack[v] = false; // Remove from recursion stack
    return false;
}

bool isCyclicDirected(int V, vector<vector<int>>& adj) {
    vector<bool> visited(V, false);
    vector<bool> recStack(V, false);

    for (int i = 0; i < V; i++) {
        if (isCyclicDirectedUtil(i, adj, visited, recStack)) {
            return true;
        }
    }
    return false;
}

/*
 * Detecting cycle in an Undirected Graph
 * We use DFS and ensure we don't revisit the parent node.
 */
bool isCyclicUndirectedUtil(int v, vector<vector<int>>& adj, vector<bool>& visited, int parent) {
    visited[v] = true;

    for (int neighbor : adj[v]) {
        if (!visited[neighbor]) {
            if (isCyclicUndirectedUtil(neighbor, adj, visited, v)) {
                return true;
            }
        } else if (neighbor != parent) {
            return true;
        }
    }
    return false;
}

bool isCyclicUndirected(int V, vector<vector<int>>& adj) {
    vector<bool> visited(V, false);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (isCyclicUndirectedUtil(i, adj, visited, -1)) {
                return true;
            }
        }
    }
    return false;
}

/*
 * Detecting cycle in a Binary Tree-like structure
 * We use DFS and track visited nodes using an unordered_set to check for back edges.
 */
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

bool isCyclicTreeUtil(Node* node, unordered_set<Node*>& visited, Node* parent) {
    if (!node) return false;

    if (visited.find(node) != visited.end()) {
        return true;
    }

    visited.insert(node);

    if (node->left && node->left != parent) {
        if (isCyclicTreeUtil(node->left, visited, node)) {
            return true;
        }
    }

    if (node->right && node->right != parent) {
        if (isCyclicTreeUtil(node->right, visited, node)) {
            return true;
        }
    }

    return false;
}

bool isCyclicTree(Node* root) {
    unordered_set<Node*> visited;
    return isCyclicTreeUtil(root, visited, nullptr);
}

// Example for usage
int main() {
    // Example for directed graph cycle detection
    vector<vector<int>> directedAdj = {{1}, {2}, {0}, {4}, {5}, {3}};
    if (isCyclicDirected(6, directedAdj)) {
        cout << "Cycle detected in the directed graph!" << endl;
    } else {
        cout << "No cycle in the directed graph." << endl;
    }

    // Example for undirected graph cycle detection
    vector<vector<int>> undirectedAdj = {{1}, {0, 2}, {1, 3}, {2}};
    if (isCyclicUndirected(4, undirectedAdj)) {
        cout << "Cycle detected in the undirected graph!" << endl;
    } else {
        cout << "No cycle in the undirected graph." << endl;
    }

    // Example for binary tree cycle detection
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->left->right->left = root->left; // Introduce a cycle in the tree

    if (isCyclicTree(root)) {
        cout << "Cycle detected in the binary tree!" << endl;
    } else {
        cout << "No cycle in the binary tree." << endl;
    }

    return 0;
}
