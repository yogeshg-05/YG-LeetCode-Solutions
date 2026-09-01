class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = 0, sc = 0, litter = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }
                if (classroom[i][j] == 'L') {
                    litter++;
                }
            }
        }

        if (litter == 0) return 0;

        int total = m * n;
        int maskSize = 1 << litter;

        vector<pair<int,int>> lp;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'L')
                    lp.push_back({i, j});
            }
        }

        vector<vector<int>> id(m, vector<int>(n, -1));
        for (int i = 0; i < litter; i++)
            id[lp[i].first][lp[i].second] = i;

        vector<vector<vector<int>>> dist(
            m, vector<vector<int>>(n, vector<int>(maskSize, -1))
        );

        queue<array<int,4>> q;

        int startMask = 0;
        dist[sr][sc][0] = energy;
        q.push({sr, sc, energy, 0});

        int moves = 0;
        int dr[] = {1, -1, 0, 0};
        int dc[] = {0, 0, 1, -1};

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                auto [r, c, e, mask] = q.front();
                q.pop();

                if (mask == maskSize - 1)
                    return moves;

                if (e == 0) continue;

                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    if (classroom[nr][nc] == 'X')
                        continue;

                    int ne = e - 1;
                    int nmask = mask;

                    if (classroom[nr][nc] == 'L') {
                        nmask |= (1 << id[nr][nc]);
                    }

                    if (classroom[nr][nc] == 'R') {
                        ne = energy;
                    }

                    if (dist[nr][nc][nmask] < ne) {
                        dist[nr][nc][nmask] = ne;
                        q.push({nr, nc, ne, nmask});
                    }
                }
            }

            moves++;
        }

        return -1;
    }
};