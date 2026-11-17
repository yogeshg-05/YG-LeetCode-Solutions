class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.length();
        
        // Step 1: Precompute valid divisors for each length up to n
        vector<vector<int>> divisors(n + 1);
        for (int len = 2; len <= n; ++len) {
            for (int d = 1; d < len; ++d) {
                if (len % d == 0) {
                    divisors[len].push_back(d);
                }
            }
        }
        
        // Step 2: Precompute cost[i][j] for all substrings
        // cost[i][j] = min changes to make s[i...j] a semi-palindrome
        vector<vector<int>> cost(n, vector<int>(n, 1e9));
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int L = j - i + 1;
                int min_changes = 1e9;
                
                for (int d : divisors[L]) {
                    int current_changes = 0;
                    
                    for (int offset = 0; offset < d; ++offset) {
                        int left = i + offset;
                        int right = i + offset + (L / d - 1) * d;
                        
                        // Check if group is a palindrome
                        while (left < right) {
                            if (s[left] != s[right]) {
                                current_changes++;
                            }
                            left += d;
                            right -= d;
                        }
                    }
                    min_changes = min(min_changes, current_changes);
                }
                cost[i][j] = min_changes;
            }
        }
        
        // Step 3: Dynamic Programming
        // dp[p][i] = min changes to partition prefix s[0...i-1] into p substrings
        vector<vector<int>> dp(k + 1, vector<int>(n + 1, 1e9));
        dp[0][0] = 0;
        
        for (int p = 1; p <= k; ++p) {
            for (int i = 1; i <= n; ++i) {
                // j is the start index of the last partition. 
                // Length must be at least 2, so j <= i - 2
                for (int j = 0; j <= i - 2; ++j) {
                    if (dp[p - 1][j] != 1e9) {
                        dp[p][i] = min(dp[p][i], dp[p - 1][j] + cost[j][i - 1]);
                    }
                }
            }
        }
        
        return dp[k][n];
    }
};