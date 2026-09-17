class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n=arr.size(), ans=INT_MAX, sum=0;
        vector<int> best(n,INT_MAX);

        for(int i=0,j=0;i<n;i++){
            sum+=arr[i];
            while(sum>target) sum-=arr[j++];

            if(sum==target){
                int len=i-j+1;
                if(j>0 && best[j-1]!=INT_MAX)
                    ans=min(ans,len+best[j-1]);
                best[i]=len;
            }
            if(i>0) best[i]=min(best[i],best[i-1]);
        }
        return ans==INT_MAX?-1:ans;
    }
};