#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

/* ----------------------------------------------
   Adjacency List using unordered_map (for sparse graphs)
   - Efficient for sparse graphs
   - Vertices can be non-sequential or dynamically added
------------------------------------------------*/
unordered_map<int, vector<int>> adjList;

// Function to add edge in Adjacency List
void addEdgeAdjList(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);  // For undirected graph
}

// BFS for Adjacency List
void bfsAdjList(int start) {
    queue<int> q;
    unordered_map<int, bool> visited;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        // Visit all neighbors
        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}

// DFS for Adjacency List
void dfsAdjList(int start) {
    stack<int> s;
    unordered_map<int, bool> visited;

    s.push(start);

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (!visited[node]) {
            cout << node << " ";
            visited[node] = true;

            // Visit all neighbors
            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    s.push(neighbor);
                }
            }
        }
    }
    cout << endl;
}

/* ----------------------------------------------
   Adjacency Matrix using 2D vector (for dense graphs)
   - Efficient for dense graphs
   - Fast access to check existence of edges
------------------------------------------------*/
vector<vector<int>> adjMatrix;

// Function to add edge in Adjacency Matrix
void addEdgeAdjMatrix(int u, int v) {
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;  // For undirected graph
}

// BFS for Adjacency Matrix
void bfsAdjMatrix(int start, int n) {
    queue<int> q;
    vector<bool> visited(n, false);

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        // Visit all neighbors (checking each entry in the matrix row)
        for (int i = 0; i < n; ++i) {
            if (adjMatrix[node][i] == 1 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout << endl;
}

// DFS for Adjacency Matrix
void dfsAdjMatrix(int start, int n) {
    stack<int> s;
    vector<bool> visited(n, false);

    s.push(start);

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (!visited[node]) {
            cout << node << " ";
            visited[node] = true;

            // Visit all neighbors (checking each entry in the matrix row)
            for (int i = 0; i < n; ++i) {
                if (adjMatrix[node][i] == 1 && !visited[i]) {
                    s.push(i);
                }
            }
        }
    }
    cout << endl;
}

int main() {
    // Number of nodes
    int n = 5;

    /* -------------------------------
       Adjacency List Example
       - Better for sparse graphs
       - Dynamic vertex management
    ---------------------------------*/
    cout << "Adjacency List (unordered_map) BFS and DFS:\n";

    // Add edges to the adjacency list
    addEdgeAdjList(0, 1);
    addEdgeAdjList(0, 4);
    addEdgeAdjList(1, 2);
    addEdgeAdjList(1, 3);
    addEdgeAdjList(1, 4);
    addEdgeAdjList(2, 3);
    addEdgeAdjList(3, 4);

    // BFS and DFS using Adjacency List
    cout << "BFS starting from node 0: ";
    bfsAdjList(0);

    cout << "DFS starting from node 0: ";
    dfsAdjList(0);

    /* -------------------------------
       Adjacency Matrix Example
       - Better for dense graphs
       - Fast access to edges
    ---------------------------------*/
    cout << "\nAdjacency Matrix (2D vector) BFS and DFS:\n";

    // Initialize adjacency matrix (n x n)
    adjMatrix.resize(n, vector<int>(n, 0));

    // Add edges to the adjacency matrix
    addEdgeAdjMatrix(0, 1);
    addEdgeAdjMatrix(0, 4);
    addEdgeAdjMatrix(1, 2);
    addEdgeAdjMatrix(1, 3);
    addEdgeAdjMatrix(1, 4);
    addEdgeAdjMatrix(2, 3);
    addEdgeAdjMatrix(3, 4);

    // BFS and DFS using Adjacency Matrix
    cout << "BFS starting from node 0: ";
    bfsAdjMatrix(0, n);

    cout << "DFS starting from node 0: ";
    dfsAdjMatrix(0, n);

    return 0;
}
