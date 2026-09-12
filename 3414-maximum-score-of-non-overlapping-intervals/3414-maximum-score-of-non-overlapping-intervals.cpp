class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& a) {
        int n = a.size();
        vector<array<int,4>> v;
        for(int i=0;i<n;i++) v.push_back({a[i][0],a[i][1],a[i][2],i});
        sort(v.begin(),v.end());

        vector<vector<pair<long long,vector<int>>>> dp(n+1,
            vector<pair<long long,vector<int>>>(5));

        for(int i=n-1;i>=0;i--)
            for(int k=1;k<=4;k++) {
                auto x=dp[i+1][k];
                int j=upper_bound(v.begin(),v.end(),v[i][1],
                    [](int x,const array<int,4>& y){return x<y[0];})-v.begin();
                auto y=dp[j][k-1];
                y.first+=v[i][2];
                y.second.push_back(v[i][3]);
                sort(y.second.begin(),y.second.end());
                dp[i][k]=(y.first>x.first||(y.first==x.first&&y.second<x.second))?y:x;
            }

        return dp[0][4].second;
    }
};