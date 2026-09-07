class Solution {
public:
    int distinctSubseqII(string s) {
        const int MOD = 1000000007;

        // dp[i] = number of distinct subsequences
        // after processing the first i characters.
        vector<long long> dp(s.size() + 1, 0);
        dp[0] = 1; // empty subsequence

        // Store the last contribution of each character.
        vector<long long> last(26, 0);

        for (int i = 1; i <= s.size(); i++) {
            int c = s[i - 1] - 'a';

            // Every existing subsequence can either:
            // 1. not use s[i-1]
            // 2. append s[i-1]
            dp[i] = (2 * dp[i - 1]) % MOD;

            // Remove duplicates created by previous occurrence
            // of the same character.
            dp[i] = (dp[i] - last[c] + MOD) % MOD;

            // Contribution of this character for future positions.
            last[c] = dp[i - 1];
        }

        // Remove the empty subsequence.
        return (dp[s.size()] - 1 + MOD) % MOD;
    }
};