class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k), dp(k), ndp(k);
        
        for(int x : nums) {
            fill(ndp.begin(), ndp.end(), 0);
            ndp[x % k]++;
            
            for(int r=0;r<k;r++)
                ndp[(r*(x%k))%k] += dp[r];
            
            dp = ndp;
            for(int r=0;r<k;r++)
                ans[r] += dp[r];
        }
        
        return ans;
    }
};