class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        long long total=accumulate(nums.begin(),nums.end(),0LL);
        long long target=total-x,sum=0;
        int l=0,best=-1;

        if(target==0) return nums.size();

        for(int r=0;r<nums.size();r++){
            sum+=nums[r];
            while(l<=r && sum>target) sum-=nums[l++];
            if(sum==target) best=max(best,r-l+1);
        }

        return best==-1?-1:nums.size()-best;
    }
};