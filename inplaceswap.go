package main

import "fmt"

/*Given an unsorted integer array nums. Return the smallest positive integer that is not present in nums.

  You must implement an algorithm that runs in O(n) time and uses O(1) auxiliary space.

*/

func firstMissingPositive(nums []int) int {
    n := len(nums)
    
    // Place each number in its correct position
    for i := 0; i < n; i++ {
        for nums[i] > 0 && nums[i] <= n && nums[nums[i]-1] != nums[i] {
            nums[nums[i]-1], nums[i] = nums[i], nums[nums[i]-1]
        }
    }
    
    // Find the first missing positive
    for i := 0; i < n; i++ {
        if nums[i] != i+1 {
            return i + 1
        }
    }
    
    // If all positions are correct, return n+1
    return n + 1
}
