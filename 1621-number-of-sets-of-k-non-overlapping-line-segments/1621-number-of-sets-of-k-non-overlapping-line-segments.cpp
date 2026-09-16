class Solution {
public:
    int numberOfSets(int n, int k) {
        const long long MOD=1e9+7;
        long long a=1,b=1;
        int N=n+k-1,R=2*k;

        for(int i=1;i<=R;i++) a=a*(N-R+i)%MOD;
        for(int i=1;i<=R;i++) b=b*i%MOD;

        long long res=1,e=MOD-2;
        while(e){
            if(e&1) res=res*b%MOD;
            b=b*b%MOD;
            e>>=1;
        }

        return a*res%MOD;
    }
};