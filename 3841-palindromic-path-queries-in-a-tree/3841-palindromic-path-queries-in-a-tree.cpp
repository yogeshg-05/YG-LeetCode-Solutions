class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int LOG = 1;
        while ((1 << LOG) <= n) ++LOG;

        vector<int> tin(n), tout(n), depth(n);
        vector<vector<int>> up(LOG, vector<int>(n));
        int timer = 0;

        auto dfs = [&](auto&& self, int u, int p) -> void {
            tin[u] = timer++;
            up[0][u] = p;

            for (int j = 1; j < LOG; ++j)
                up[j][u] = up[j - 1][up[j - 1][u]];

            for (int v : adj[u]) {
                if (v == p) continue;
                depth[v] = depth[u] + 1;
                self(self, v, u);
            }

            tout[u] = timer;
        };

        dfs(dfs, 0, 0);

        // Fenwick tree supports XOR updates and prefix queries.
        vector<int> bit(n + 1, 0);

        auto update = [&](int idx, int val) {
            for (++idx; idx <= n; idx += idx & -idx)
                bit[idx] ^= val;
        };

        auto prefixXor = [&](int idx) {
            int res = 0;
            for (++idx; idx > 0; idx -= idx & -idx)
                res ^= bit[idx];
            return res;
        };

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);

            int diff = depth[u] - depth[v];
            for (int j = 0; j < LOG; ++j)
                if (diff & (1 << j))
                    u = up[j][u];

            if (u == v) return u;

            for (int j = LOG - 1; j >= 0; --j) {
                if (up[j][u] != up[j][v]) {
                    u = up[j][u];
                    v = up[j][v];
                }
            }
            return up[0][u];
        };

        // Difference array: each node's character affects its subtree.
        for (int i = 0; i < n; ++i) {
            int mask = 1 << (s[i] - 'a');
            update(tin[i], mask);
            if (tout[i] < n) update(tout[i], mask);
        }

        auto nodeMask = [&](int u) {
            return prefixXor(tin[u]);
        };

        vector<bool> ans;

        for (const string& q : queries) {
            stringstream ss(q);
            string type;
            int u;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int change = (1 << (s[u] - 'a')) ^
                             (1 << (c - 'a'));

                update(tin[u], change);
                if (tout[u] < n) update(tout[u], change);

                s[u] = c;
            } else {
                int v;
                ss >> v;

                int w = lca(u, v);
                int mask = nodeMask(u) ^ nodeMask(v) ^
                           (1 << (s[w] - 'a'));

                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};