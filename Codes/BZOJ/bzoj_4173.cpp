#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const long long MOD = 998244353;
long long phi(long long x)
{
    double ans = x;
    int i = 2;
    int Sqrt = ceil(sqrt(x));
    while (x != 1)
    {
        if (i > Sqrt)
        {
            ans *= (1 - (double)1 / x);
            break;
        }
        if (x % i == 0)
        {
            ans *= (1 - (double)1 / i);
            while (x % i == 0)
                x /= i;
        }
        i++;
    }
    return (long long)round(ans);
}
int main()
{
    long long a,b;
    scanf("%lld%lld",&a,&b);
    printf("%lld",((((a%MOD)*(b%MOD)%MOD)*(phi(a)%MOD)%MOD)*(phi(b)%MOD))%MOD);
    //while(1);
}
