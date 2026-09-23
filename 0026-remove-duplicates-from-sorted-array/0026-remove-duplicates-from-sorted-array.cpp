class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int k=0;
        for(int x:nums)
            if(k==0 || nums[k-1]!=x)
                nums[k++]=x;
        return k;
    }
};