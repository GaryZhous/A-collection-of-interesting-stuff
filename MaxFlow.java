import java.util.*;

// Main class for the Maximum Flow problem
public class MaxFlow {

    // Method to find the maximum flow using Edmonds-Karp
    public static int edmondsKarp(int[][] capacity, int source, int sink) {
        int n = capacity.length; // Number of nodes in the graph
        int[][] residualCapacity = new int[n][n]; // Residual capacity graph
        for (int i = 0; i < n; i++) {
            System.arraycopy(capacity[i], 0, residualCapacity[i], 0, n);
        }

        int maxFlow = 0; // Variable to store the maximum flow

        // While there is an augmenting path from source to sink
        while (true) {
            int[] parent = new int[n]; // To store the path from source to sink
            Arrays.fill(parent, -1);
            boolean foundPath = bfs(residualCapacity, source, sink, parent);

            if (!foundPath) break; // No more augmenting paths, break the loop

            // Find the minimum capacity in the augmenting path
            int flow = Integer.MAX_VALUE;
            int current = sink;
            while (current != source) {
                int prev = parent[current];
                flow = Math.min(flow, residualCapacity[prev][current]);
                current = prev;
            }

            // Update the residual capacities of the edges and reverse edges
            current = sink;
            while (current != source) {
                int prev = parent[current];
                residualCapacity[prev][current] -= flow; // Reduce capacity along the path
                residualCapacity[current][prev] += flow; // Increase reverse capacity
                current = prev;
            }

            maxFlow += flow; // Add the flow of this path to the total flow
        }

        return maxFlow;
    }

    // Breadth-First Search to find an augmenting path
    private static boolean bfs(int[][] residualCapacity, int source, int sink, int[] parent) {
        int n = residualCapacity.length;
        boolean[] visited = new boolean[n]; // Track visited nodes
        Queue<Integer> queue = new LinkedList<>();
        queue.add(source);
        visited[source] = true;

        while (!queue.isEmpty()) {
            int u = queue.poll();

            // Explore all neighbors of u
            for (int v = 0; v < n; v++) {
                // If there is residual capacity and v is not visited
                if (!visited[v] && residualCapacity[u][v] > 0) {
                    parent[v] = u; // Store the path
                    visited[v] = true;
                    if (v == sink) return true; // Path to sink found
                    queue.add(v);
                }
            }
        }

        return false; // No augmenting path found
    }

    // Main method to test the algorithm
    public static void main(String[] args) {
        // Example graph (capacity matrix)
        int[][] capacity = {
            {0, 10, 10, 0, 0, 0}, // Node 0 (source)
            {0, 0, 2, 4, 8, 0},   // Node 1
            {0, 0, 0, 0, 9, 0},   // Node 2
            {0, 0, 0, 0, 0, 10},  // Node 3
            {0, 0, 0, 6, 0, 10},  // Node 4
            {0, 0, 0, 0, 0, 0}    // Node 5 (sink)
        };

        int source = 0; // Source node
        int sink = 5;   // Sink node

        int maxFlow = edmondsKarp(capacity, source, sink);
        System.out.println("Maximum Flow: " + maxFlow);
    }
}
