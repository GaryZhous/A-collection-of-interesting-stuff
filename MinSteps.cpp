#include <bits/stdc++.h>
using namespace std;
/*You are asked to transform a given array into the desired array with these requirements:
  1. Pick the last element from the given array and insert it at any position of the array, as one operation.
  2. Find the minimum number of operations to convert the given array to the desired array.
*/
int getMinSteps(vector<int> current, vector<int> desired) {
    int n = current.size();
    unordered_map<int, int> pos;

    // Store positions of elements in the desired order
    for (int i = 0; i < n; i++) {
        pos[desired[i]] = i;
    }

    // Find the longest suffix match in correct order
    int matchIndex = n - 1;
    for (int i = n - 1; i >= 0; i--) {
        if (current[i] == desired[matchIndex]) {
            matchIndex--;
            if (matchIndex < 0) break;  // Matched all elements
        }
    }

    // Moves required = elements not in the matched suffix
    return matchIndex + 1;
}

int main() {
    vector<int> current = {2, 1, 3, 5, 4};
    vector<int> desired = {2, 4, 1, 5, 3};
    
    cout << getMinSteps(current, desired) << endl; // Expected output: 2
    return 0;
}
