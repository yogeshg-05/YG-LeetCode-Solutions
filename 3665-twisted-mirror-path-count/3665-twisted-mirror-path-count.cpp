class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;

        int m = grid.size();
        int n = grid[0].size();
        int N = m * n;

        // enterRight[id]: endpoint when a mirror is entered from the left.
        // enterDown[id]: endpoint when a mirror is entered from above.
        // -1 means the movement goes out of bounds.
        vector<int> enterRight(N, -1);
        vector<int> enterDown(N, -1);

        auto id = [&](int r, int c) {
            return r * n + c;
        };

        // Precompute mirror transitions.
        // Reverse order ensures dependent states are already calculated.
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (grid[i][j] == 0) continue;

                int cur = id(i, j);

                // Entered mirror while moving RIGHT:
                // Reflect DOWN.
                if (i + 1 < m) {
                    if (grid[i + 1][j] == 0) {
                        enterRight[cur] = id(i + 1, j);
                    } else {
                        enterRight[cur] = enterDown[id(i + 1, j)];
                    }
                }

                // Entered mirror while moving DOWN:
                // Reflect RIGHT.
                if (j + 1 < n) {
                    if (grid[i][j + 1] == 0) {
                        enterDown[cur] = id(i, j + 1);
                    } else {
                        enterDown[cur] = enterRight[id(i, j + 1)];
                    }
                }
            }
        }

        // DP: number of ways to reach each cell.
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = 1;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1 || dp[i][j] == 0)
                    continue;

                int ways = dp[i][j];

                // Move RIGHT.
                if (j + 1 < n) {
                    int dest;

                    if (grid[i][j + 1] == 0) {
                        dest = id(i, j + 1);
                    } else {
                        dest = enterRight[id(i, j + 1)];
                    }

                    if (dest != -1) {
                        int r = dest / n;
                        int c = dest % n;

                        dp[r][c] = (dp[r][c] + ways) % MOD;
                    }
                }

                // Move DOWN.
                if (i + 1 < m) {
                    int dest;

                    if (grid[i + 1][j] == 0) {
                        dest = id(i + 1, j);
                    } else {
                        dest = enterDown[id(i + 1, j)];
                    }

                    if (dest != -1) {
                        int r = dest / n;
                        int c = dest % n;

                        dp[r][c] = (dp[r][c] + ways) % MOD;
                    }
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};