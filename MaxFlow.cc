#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 500; // Maximum number of nodes
const int INF = 1e9;

vector<int> adj[MAXN];  // Adjacency list
int capacity[MAXN][MAXN]; // Capacity matrix
int parent[MAXN];  // Parent array for BFS

// BFS to find an augmenting path
bool bfs(int s, int t) {
    memset(parent, -1, sizeof(parent));
    parent[s] = -2; // Mark the source as visited
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next] > 0) {
                // If the next node is unvisited and has capacity left
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t) return true; // Found an augmenting path
                q.push({next, new_flow});
            }
        }
    }
    return false;
}

// Edmonds-Karp: Maximum Flow Algorithm
int maxFlow(int s, int t) {
    int flow = 0;

    while (bfs(s, t)) {
        int cur = t;
        int path_flow = INF;

        // Find the bottleneck capacity in the augmenting path
        while (cur != s) {
            int prev = parent[cur];
            path_flow = min(path_flow, capacity[prev][cur]);
            cur = prev;
        }

        // Update capacities along the path
        cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= path_flow;
            capacity[cur][prev] += path_flow;
            cur = prev;
        }

        flow += path_flow;
    }

    return flow;
}

int main() {
    int n, k, c; // Number of doctors, vacation periods, max days per doctor
    cin >> n >> k >> c;

    vector<vector<int>> Dj(k); // Vacation days for each period
    int total_days = 0;

    // Input vacation days
    for (int i = 0; i < k; i++) {
        int m; // Number of days in this vacation period
        cin >> m;
        total_days += m;
        Dj[i].resize(m);
        for (int j = 0; j < m; j++) {
            cin >> Dj[i][j];
        }
    }

    int N = total_days; // Total number of vacation days
    int s = 0, t = n + N + 1; // Source and sink nodes

    // Input doctor availability
    for (int i = 1; i <= n; i++) {
        int m; // Number of days this doctor is available
        cin >> m;
        for (int j = 0; j < m; j++) {
            int day;
            cin >> day;
            adj[i].push_back(n + day);
            adj[n + day].push_back(i);
            capacity[i][n + day] = 1;
        }
        adj[s].push_back(i);
        adj[i].push_back(s);
        capacity[s][i] = c;
    }

    // Connect vacation days to sink
    for (int day = 1; day <= N; day++) {
        adj[n + day].push_back(t);
        adj[t].push_back(n + day);
        capacity[n + day][t] = 1;
    }

    // Calculate maximum flow
    int flow = maxFlow(s, t);

    if (flow == N) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}
