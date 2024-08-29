/*
  Given an unweighted graph (aka an adjacent matrix), return the lowest path cost from the top right corner to the bottom left corner.
  Each step is counted as cost + 1.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility> // for std::pair

using namespace std;

// Directions for moving up, down, left, right
const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

// Function to check if a position is within the bounds of the grid
bool isValid(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

// Function to find the shortest path from the top right to the bottom left in an unweighted grid
int shortestPath(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    
    // Queue for BFS storing the current position and the distance from the start
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    
    // Start BFS from the top right corner
    q.push({0, cols - 1});
    visited[0][cols - 1] = true;
    int steps = 0;

    while (!q.empty()) {
        int size = q.size();
        
        // Process all nodes at the current depth
        for (int i = 0; i < size; i++) {
            auto [x, y] = q.front();
            q.pop();

            // Check if we've reached the bottom left corner
            if (x == rows - 1 && y == 0) {
                return steps;
            }

            // Explore all possible directions
            for (const auto& dir : directions) {
                int newX = x + dir.first;
                int newY = y + dir.second;

                // If the new position is within bounds and not visited, add it to the queue
                if (isValid(newX, newY, rows, cols) && !visited[newX][newY]) {
                    q.push({newX, newY});
                    visited[newX][newY] = true;
                }
            }
        }

        // Increment steps (distance)
        steps++;
    }

    // If no path is found
    return -1;
}

int main() {
    // Example grid, 0 indicates a traversable cell
    vector<vector<int>> grid = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    
    int result = shortestPath(grid);
    
    if (result != -1) {
        cout << "The shortest path has length: " << result << endl;
    } else {
        cout << "No path found." << endl;
    }
    
    return 0;
}
