class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int n = nums.size();
        int minSum = INT_MAX;

        // Iterate over every possible starting index
        for (int i = 0; i < n; ++i) {
            int currentSum = 0;
            // Extend the subarray up to length r
            for (int j = i; j < n && (j - i + 1) <= r; ++j) {
                currentSum += nums[j];
                int len = j - i + 1;
                
                // Check if length is within [l, r] and sum is strictly positive
                if (len >= l && currentSum > 0) {
                    minSum = min(minSum, currentSum);
                }
            }
        }

        return (minSum == INT_MAX) ? -1 : minSum;
    }
};