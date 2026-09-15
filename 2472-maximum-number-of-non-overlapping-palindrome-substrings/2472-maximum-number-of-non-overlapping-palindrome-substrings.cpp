class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n=s.size(), ans=0, last=0;
        vector<vector<char>> p(n,vector<char>(n));

        for(int i=n-1;i>=0;i--)
            for(int j=i;j<n;j++)
                p[i][j]=(s[i]==s[j] && (j-i<2 || p[i+1][j-1]));

        for(int r=0;r<n;r++) {
            for(int l=last;l<=r-k+1;l++) {
                if(p[l][r]) {
                    ans++;
                    last=r+1;
                    break;
                }
            }
        }
        return ans;
    }
};