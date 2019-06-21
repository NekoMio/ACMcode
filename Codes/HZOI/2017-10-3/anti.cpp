#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1e9 + 7;
long long pow_mod(long long a, long long b)
{
    if (a < 0) return 0;
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
int main()
{
    long long n, m;
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%lld%lld", &n, &m);
        long long ans = m % MOD;
        if(n > 1) ans = ans * ((m - 1 + MOD) % MOD) % MOD;
        if(n > 2) ans = ans * pow_mod((m - 2 + MOD) % MOD, n - 2) % MOD;
        printf ("%lld\n", ans);
    }
}