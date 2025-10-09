/*A no-zero integer is a positive integer that does not contain the digit 0 in its decimal representation.
  Given an integer n, count the number of pairs (a, b) where:
    1. a and b are no-zero integers.
    2. a + b = n
  Return an integer denoting the number of such pairs. 
*/
/*only 10.8% acceptance rate on LeetCode*/
class Solution {
public:
    string s;
    long long dp[20][20][2][2];

    long long solve(int ind, int carry, bool za, bool zb) {

        if (ind == s.length()) {
            if (carry) {
                return 0;
            }
            return 1;
        }

        int n = s.length();

        if (dp[ind][carry][za][zb] != -1) {
            return dp[ind][carry][za][zb];
        }

        int eda = (za ? 0 : 9);
        int edb = (zb ? 0 : 9);
        int sa = ((ind == 0) ? 1 : 0);
        int sb = ((ind == 0) ? 1 : 0);

        int num = s[ind] - '0';

        long long cnt = 0;

        for (int i = sa; i <= eda; i++) {
            for (int j = sb; j <= edb; j++) {
                int x = i + j + carry;
                if (x % 10 == num) {
                    cnt += solve(ind + 1, x / 10, za | (i == 0), zb | (j == 0));
                }
            }
        }

        return dp[ind][carry][za][zb] = cnt;
    }

    long long countNoZeroPairs(long long n) {

        this->s = to_string(n);
        reverse(s.begin(), s.end());
        memset(dp, -1, sizeof(dp));

        return solve(0, 0, false, false);
    }
};
