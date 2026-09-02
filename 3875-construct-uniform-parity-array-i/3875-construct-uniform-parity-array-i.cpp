class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        bool even = false, odd = false;

        for (int x : nums1) {
            if (x % 2 == 0)
                even = true;
            else
                odd = true;
        }

        return true;
    }
};