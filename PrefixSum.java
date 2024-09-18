import java.util.*;
//a typical leetcode problem asking the minimum number of operations to let every element of the nums array to equal to each element of the queries array (+1 or -1 counts as one operation at once)
class Solution {
    public List<Long> minOperations(int[] nums, int[] queries) {
        int n = nums.length;
        // Sort the nums array
        Arrays.sort(nums);
        
        // Create the prefix sum array
        long[] prefixSum = new long[n+1];
        for (int i = 0; i < n; i++) {
            prefixSum[i+1] = prefixSum[i] + nums[i];
        }
        
        List<Long> answer = new ArrayList<>();
        
        // For each query, calculate the number of operations
        for (int q : queries) {
            // Use binary search to find the position where nums[i] >= q
            int idx = Arrays.binarySearch(nums, q);
            if (idx < 0) {
                idx = -(idx + 1); // If not found, this gives the insertion point
            }
            
            // Calculate the operations for elements less than q
            long leftOperations = (long) q * idx - prefixSum[idx];
            
            // Calculate the operations for elements greater than or equal to q
            long rightOperations = (prefixSum[n] - prefixSum[idx]) - (long) q * (n - idx);
            
            // Total operations for this query
            answer.add(leftOperations + rightOperations);
        }
        
        return answer;
    }
}
