class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        
        int case1 = nums[n - 1] - nums[2];     // Change 2 smallest
        int case2 = nums[n - 3] - nums[0];     // Change 2 largest
        int case3 = nums[n - 2] - nums[1];     // Change 1 smallest & 1 largest
        
        return min({case1, case2, case3});
    }
};