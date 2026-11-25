class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 1;

        // Append sentinel 0 (all nums[i] >= 1)
        vector<int> s = nums;
        s.push_back(0);
        int m = n + 1;
        int alphabet = *max_element(s.begin(), s.end()) + 1;

        vector<int> p(m), c(m), cnt(max(alphabet, m), 0);
        for (int i = 0; i < m; ++i) cnt[s[i]]++;
        for (int i = 1; i < alphabet; ++i) cnt[i] += cnt[i - 1];
        for (int i = 0; i < m; ++i) p[--cnt[s[i]]] = i;

        c[p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < m; ++i) {
            if (s[p[i]] != s[p[i - 1]]) classes++;
            c[p[i]] = classes - 1;
        }

        vector<int> pn(m), cn(m);
        for (int h = 0; (1 << h) < m; ++h) {
            for (int i = 0; i < m; ++i) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0) pn[i] += m;
            }
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i = 0; i < m; ++i) cnt[c[pn[i]]]++;
            for (int i = 1; i < classes; ++i) cnt[i] += cnt[i - 1];
            for (int i = m - 1; i >= 0; --i) p[--cnt[c[pn[i]]]] = pn[i];

            cn[p[0]] = 0;
            classes = 1;
            for (int i = 1; i < m; ++i) {
                pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % m]};
                pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % m]};
                if (cur != prev) classes++;
                cn[p[i]] = classes - 1;
            }
            c.swap(cn);
            if (classes == m) break;
        }

        // Drop sentinel suffix at p[0]
        vector<int> sa(p.begin() + 1, p.end());
        vector<int> rnk(n);
        for (int i = 0; i < n; ++i) rnk[sa[i]] = i;

        // Kasai's algorithm for LCP
        vector<int> lcp(n - 1, 0);
        int k = 0;
        for (int i = 0; i < n; ++i) {
            if (rnk[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = sa[rnk[i] + 1];
            while (i + k < n && j + k < n && nums[i + k] == nums[j + k]) {
                k++;
            }
            lcp[rnk[i]] = k;
            if (k > 0) k--;
        }

        int ans = n;
        for (int i = 0; i < n; ++i) {
            int left_lcp = (i > 0) ? lcp[i - 1] : 0;
            int right_lcp = (i + 1 < n) ? lcp[i] : 0;
            int max_dup = max(left_lcp, right_lcp);
            if (sa[i] + max_dup < n) {
                ans = min(ans, max_dup + 1);
            }
        }

        return ans;
    }
};