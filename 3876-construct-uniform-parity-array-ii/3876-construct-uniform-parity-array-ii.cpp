class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int mn = *min_element(nums1.begin(), nums1.end());

        // If minimum is even, all elements must already be even.
        if (mn % 2 == 0) {
            for (int x : nums1) {
                if (x % 2 != 0)
                    return false;
            }
        }

        return true;
    }
};