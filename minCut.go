/*This problem can be solved efficiently using dynamic programming (DP) with memoization and precomputed palindrome checking.

  Approach:
  1. Precompute Palindromes: Use a 2D DP table isPalindrome[i][j] to check if s[i:j+1] is a palindrome in 𝑂(𝑛^2).
  2. DP for Minimum Cuts: Use a 1D DP array dp[i] where dp[i] represents the minimum cuts needed to partition s[0:i+1] into palindromic substrings.
  
  Optimized DP Formula:
  - If s[0:i] is a palindrome, dp[i] = 0 (no cuts needed).
  - Otherwise, we try every possible partition s[j:i] where j ≤ i, and if s[j:i] is a palindrome, we update dp[i] = min(dp[i], dp[j-1] + 1).
*/

func minCut(s string) int {
    n := len(s)
    if n == 0 {
        return 0
    }

    // Step 1: Precompute palindrome table
    isPalindrome := make([][]bool, n)
    for i := range isPalindrome {
        isPalindrome[i] = make([]bool, n)
    }
    
    for end := 0; end < n; end++ {
        for start := 0; start <= end; start++ {
            if s[start] == s[end] && (end-start <= 2 || isPalindrome[start+1][end-1]) {
                isPalindrome[start][end] = true
            }
        }
    }

    // Step 2: DP array for minimum cuts
    dp := make([]int, n)
    for i := range dp {
        dp[i] = i // worst case: cut at every character
    }

    for i := 0; i < n; i++ {
        if isPalindrome[0][i] {
            dp[i] = 0
        } else {
            for j := 1; j <= i; j++ {
                if isPalindrome[j][i] {
                    dp[i] = min(dp[i], dp[j-1] + 1)
                }
            }
        }
    }

    return dp[n-1]
}

func min(a, b int) int {
    if a < b {
        return a
    }
    return b
}
