#include <vector>

int largestSubgrid(vector<vector<int>> grid, int maxSum) {
   int n = grid.size();
   int m = grid[0].size();
   vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
   for (int i = 1; i <= n; i++) {
     for (int j = 1; j <= m; j++) {
        dp[i][j] = grid[i-1][j-1] + dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
     }
    }
   int ans = 0;
   for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
         for (int k = ans+1; k <= n; k++) {
             if (dp[k][j] - dp[k-ans-1][j] > maxSum) break;
                  for (int l = ans+1; l <= m; l++) {
                      if (dp[k][l] - dp[k][l-ans-1] > maxSum)
                      break;
                      if (dp[k][l] - dp[k-ans-1][l] - dp[k][l-ans-1] + dp[k-ans-1][l-ans-1] <= maxSum) {
                      ans = max(ans, k-i+1);
                  }
          }
       }
     }
   }
return ans;
}
