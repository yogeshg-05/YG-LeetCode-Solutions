class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        auto dfs = [&](auto&& self, int r, int c) -> void {
            if (r < 0 || r >= m || c < 0 || c >= n ||
                grid[r][c] == 1)
                return;

            grid[r][c] = 1;

            self(self, r + 1, c);
            self(self, r - 1, c);
            self(self, r, c + 1);
            self(self, r, c - 1);
        };

        // Remove all land connected to the boundary.
        for (int i = 0; i < m; i++) {
            dfs(dfs, i, 0);
            dfs(dfs, i, n - 1);
        }

        for (int j = 0; j < n; j++) {
            dfs(dfs, 0, j);
            dfs(dfs, m - 1, j);
        }

        int count = 0;

        // Count the remaining closed islands.
        for (int i = 1; i < m - 1; i++) {
            for (int j = 1; j < n - 1; j++) {
                if (grid[i][j] == 0) {
                    count++;
                    dfs(dfs, i, j);
                }
            }
        }

        return count;
    }
};