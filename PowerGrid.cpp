#include <bits/stdc++.h>
using namespace std;
/*
  Key observations:
  
    1. The graph’s connected components (power grids) never change.
    
    2. Only nodes switch from online → offline, never back.
    
    3. For each component, we need to know the smallest-id online station at any time.
    
    4. For a query [1, x]:
    
      -> If x is online → answer is x itself.
        
      -> If x is offline → answer is the smallest online id in x's component, or -1 if none.
  
  So the plan:
  
    1. Use DSU (Disjoint Set Union / Union-Find) on connections to find the component (root) of each station.
    
    2. For each component root, keep a std::set<int> of online stations in that component.
    
      -> Initially, all stations are online → insert each station i into compSet[root[i]].
    
    3. Maintain a boolean array online[i] initialized to true.
  
  Process queries in order:
  
    Type [1, x]:
    
      If online[x] → answer = x.
      
      Else:
      
        Let r = root[x].
      
      If compSet[r] is empty → answer = -1.
      
      Else → answer = *compSet[r].begin() (smallest id online in that component).
    
    Type [2, x]:
    
      If online[x] is true, set it to false and erase x from compSet[root[x]].
      (If offline already, do nothing.)
  
  Complexities:
  
    1. Building DSU: O((c + n) α(c)).
    
    2. Building sets: O(c log c) overall (each node inserted once).
  
  Each query:
    
    Type 1: O(1) for online[x] check, and up to O(1) / O(log c) for set access.
    
    Type 2: O(log c) for erase.
  
  Total: O((c + n + q) log c) worst-case, which is fine for typical constraints.
*/
struct DSU {
    vector<int> parent, rnk;

    DSU(int n) : parent(n), rnk(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (rnk[a] < rnk[b]) swap(a, b);
        parent[b] = a;
        if (rnk[a] == rnk[b]) ++rnk[a];
    }
};

class Solution {
public:
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        // DSU with 1-based indexing; size c+1 and ignore index 0
        DSU dsu(c + 1);

        // Build connected components from connections
        for (const auto &e : connections) {
            int u = e[0];
            int v = e[1];
            dsu.unite(u, v);
        }

        // Compute root (component representative) for each station
        vector<int> root(c + 1);
        for (int i = 1; i <= c; ++i) {
            root[i] = dsu.find(i);
        }

        // For each component root, maintain an ordered set of online stations
        vector< set<int> > compSet(c + 1);
        for (int i = 1; i <= c; ++i) {
            compSet[root[i]].insert(i);  // initially all online
        }

        vector<char> online(c + 1, 1);  // 1 = online, 0 = offline

        vector<int> result;
        for (const auto &q : queries) {
            int type = q[0];
            int x    = q[1];

            if (type == 1) {
                // Maintenance check for station x
                if (online[x]) {
                    // If x is online, it serves the request
                    result.push_back(x);
                } else {
                    int r = root[x];      // component of x
                    auto &st = compSet[r];
                    if (st.empty()) {
                        result.push_back(-1);
                    } else {
                        // smallest operational id in this component
                        result.push_back(*st.begin());
                    }
                }
            } else if (type == 2) {
                // Station x goes offline
                if (online[x]) {
                    online[x] = 0;
                    int r = root[x];
                    auto &st = compSet[r];
                    auto it = st.find(x);
                    if (it != st.end()) st.erase(it);
                }
            }
        }

        return result;
    }
};
