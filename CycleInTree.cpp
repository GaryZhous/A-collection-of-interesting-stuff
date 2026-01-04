#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Helper function to detect a cycle in a binary tree-like structure using unordered_set
bool isCyclicUtilSet(Node* node, unordered_set<Node*>& visited, Node* parent) {
    if (!node) return false;

    // If the current node is already visited, there's a cycle
    if (visited.find(node) != visited.end()) {
        return true;
    }

    // Mark the current node as visited
    visited.insert(node);

    // Check left and right children, making sure we don't revisit the parent
    if (node->left && node->left != parent) {
        if (isCyclicUtilSet(node->left, visited, node)) {
            return true;
        }
    }

    if (node->right && node->right != parent) {
        if (isCyclicUtilSet(node->right, visited, node)) {
            return true;
        }
    }

    return false;
}

// Cycle detection using unordered_set
bool isCyclicWithSet(Node* root) {
    unordered_set<Node*> visited;
    return isCyclicUtilSet(root, visited, nullptr);
}

// Helper function to detect a cycle in a binary tree-like structure using vector
bool isCyclicUtilVector(Node* node, vector<Node*>& visited, Node* parent) {
    if (!node) return false;

    // If the current node is already visited, there's a cycle
    for (Node* v : visited) {
        if (v == node) {
            return true;
        }
    }

    // Mark the current node as visited by adding it to the vector
    visited.push_back(node);

    // Check left and right children, making sure we don't revisit the parent
    if (node->left && node->left != parent) {
        if (isCyclicUtilVector(node->left, visited, node)) {
            return true;
        }
    }

    if (node->right && node->right != parent) {
        if (isCyclicUtilVector(node->right, visited, node)) {
            return true;
        }
    }

    return false;
}

// Cycle detection using vector
bool isCyclicWithVector(Node* root) {
    vector<Node*> visited;
    return isCyclicUtilVector(root, visited, nullptr);
}

// Example of main function
int main() {
    // Create a simple binary tree with a cycle
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    // Introduce a cycle: point node 5's left child to node 2
    root->left->right->left = root->left; // This creates a cycle

    // Using unordered_set for cycle detection
    if (isCyclicWithSet(root)) {
        cout << "Cycle detected in the binary tree using unordered_set!" << endl;
    } else {
        cout << "No cycle in the binary tree using unordered_set." << endl;
    }

    // Using vector for cycle detection
    if (isCyclicWithVector(root)) {
        cout << "Cycle detected in the binary tree using vector!" << endl;
    } else {
        cout << "No cycle in the binary tree using vector." << endl;
    }

    return 0;
}
