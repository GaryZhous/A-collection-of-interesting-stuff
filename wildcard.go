/*Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:
  1. '?' Matches any single character.
  2. '*' Matches any sequence of characters (including the empty sequence).
  3. The matching should cover the entire input string (not partial).
  Atlassian Interview question
*/

func isMatch(s string, p string) bool {
    m, n := len(s), len(p)
    dp := make([]bool, n+1)
    
    // Base case: Empty pattern matches empty string
    dp[0] = true
    
    // Handle cases where pattern starts with '*'
    for j := 1; j <= n; j++ {
        if p[j-1] == '*' {
            dp[j] = dp[j-1]
        }
    }

    for i := 1; i <= m; i++ {
        prev := dp[0] // Store dp[i-1][j-1] for previous row
        dp[0] = false // Only empty pattern can match empty string
        
        for j := 1; j <= n; j++ {
            temp := dp[j] // Store current dp[i-1][j] before updating
            if p[j-1] == s[i-1] || p[j-1] == '?' {
                dp[j] = prev
            } else if p[j-1] == '*' {
                dp[j] = dp[j] || dp[j-1]
            } else {
                dp[j] = false
            }
            prev = temp // Move to next character
        }
    }
    
    return dp[n]
}
