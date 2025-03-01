#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

/* UnionFind class with support for both regular union-find operations and
 * weighted union-find for cases such as division equations.
 */
class UnionFind {
public:
    unordered_map<string, string> parent; // Stores the parent of each element
    unordered_map<string, double> weight; // Stores the weight for each element relative to its parent

    // Find with path compression and weight adjustment (for weighted union-find)
    string find(const string& x) {
        if (parent[x] != x) {
            string original_parent = parent[x];
            parent[x] = find(parent[x]);  // Path compression
            weight[x] *= weight[original_parent];  // Update weight to the root
        }
        return parent[x];
    }

    // Union with ratio handling, useful for division equations
    void unite(const string& x, const string& y, double value) {
        if (!parent.count(x)) {
            parent[x] = x;
            weight[x] = 1.0;
        }
        if (!parent.count(y)) {
            parent[y] = y;
            weight[y] = 1.0;
        }

        string rootX = find(x);
        string rootY = find(y);

        if (rootX != rootY) {
            parent[rootX] = rootY;
            weight[rootX] = value * weight[y] / weight[x];  // Set the weight ratio
        }
    }

    // Check if two elements are connected and return the division result
    double connected(const string& x, const string& y) {
        if (parent.count(x) && parent.count(y) && find(x) == find(y)) {
            return weight[x] / weight[y];
        } else {
            return -1.0;
        }
    }
};

// Function to evaluate division equations using Union-Find
vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
    UnionFind uf;

    // Step 1: Build the Union-Find structure with weights
    for (int i = 0; i < equations.size(); ++i) {
        uf.unite(equations[i][0], equations[i][1], values[i]);
    }

    // Step 2: Process each query
    vector<double> results;
    for (const auto& query : queries) {
        results.push_back(uf.connected(query[0], query[1]));
    }
    return results;
}

// Main function to demonstrate usage of Union-Find in division equations
int main() {
    // Example input for the division equations problem
    vector<vector<string>> equations = {{"a", "b"}, {"b", "c"}};
    vector<double> values = {2.0, 3.0};
    vector<vector<string>> queries = {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};

    // Calculate results
    vector<double> results = calcEquation(equations, values, queries);

    // Output the results
    for (double result : results) {
        cout << result << " ";
    }
    cout << endl;
    // Expected Output: [6.0, 0.5, -1.0, 1.0, -1.0]

    return 0;
}
