class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        for(int i=0;i<nums.size();i++){
            int x=nums[i], sum=0;
            while(x){
                sum+=x%10;
                x/=10;
            }
            if(sum==i) return i;
        }
        return -1;
    }
};