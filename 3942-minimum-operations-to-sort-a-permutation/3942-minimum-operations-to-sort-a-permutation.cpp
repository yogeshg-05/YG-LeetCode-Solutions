class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();

        if (is_sorted(nums.begin(), nums.end()))
            return 0;

        // Case 1: nums is a rotation of [0, 1, ..., n-1].
        bool normal = true;
        for (int i = 0; i < n; i++) {
            if (nums[i] != (nums[0] + i) % n) {
                normal = false;
                break;
            }
        }

        if (normal) {
            int p = nums[0];
            return min(n - p, p + 2);
        }

        // Case 2: nums is a rotation of [n-1, ..., 1, 0].
        bool reversed = true;
        for (int i = 0; i < n; i++) {
            if (nums[i] != (nums[0] - i + n) % n) {
                reversed = false;
                break;
            }
        }

        if (reversed) {
            int p = n - 1 - nums[0];
            return min(p + 1, n - p + 1);
        }

        return -1;
    }
};