class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1)
            return INT_MAX;

        long long a = llabs((long long)dividend);
        long long b = llabs((long long)divisor);
        long long ans = 0;

        for (int i = 31; i >= 0; i--) {
            if ((a >> i) >= b) {
                a -= (b << i);
                ans += (1LL << i);
            }
        }

        if ((dividend < 0) != (divisor < 0))
            ans = -ans;

        return (int)ans;
    }
};