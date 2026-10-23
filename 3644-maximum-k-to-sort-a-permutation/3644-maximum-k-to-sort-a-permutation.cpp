class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int n = nums.size();
        int ans = -1;

        for (int i = 0; i < n; i++) {
            if (nums[i] != i) {
                if (ans == -1)
                    ans = nums[i] & i;
                else
                    ans &= (nums[i] & i);
            }
        }

        return ans == -1 ? 0 : ans;
    }
};