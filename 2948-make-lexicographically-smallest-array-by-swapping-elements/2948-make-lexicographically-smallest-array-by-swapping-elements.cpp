class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();
        vector<pair<int, int>> a;

        for (int i = 0; i < n; i++)
            a.push_back({nums[i], i});

        sort(a.begin(), a.end());

        int l = 0;

        while (l < n) {
            int r = l;

            while (r + 1 < n && a[r + 1].first - a[r].first <= limit)
                r++;

            vector<int> pos, val;

            for (int i = l; i <= r; i++) {
                val.push_back(a[i].first);
                pos.push_back(a[i].second);
            }

            sort(pos.begin(), pos.end());

            for (int i = 0; i < pos.size(); i++)
                nums[pos[i]] = val[i];

            l = r + 1;
        }

        return nums;
    }
};