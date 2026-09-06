class Solution {
public:
    int numDistinct(string s, string t) {
        int n = t.size();

        vector<int> dp(n + 1, 0);
        dp[0] = 1;

        for (int i = 1; i <= s.size(); i++) {
            for (int j = n; j >= 1; j--) {
                if (s[i - 1] == t[j - 1]) {
                    long long val = (long long)dp[j] + dp[j - 1];

                    if (val > INT_MAX)
                        dp[j] = INT_MAX;
                    else
                        dp[j] = val;
                }
            }
        }

        return dp[n];
    }
};