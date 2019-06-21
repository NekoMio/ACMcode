#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 20100403;
long long pow_mod(long long a, int b)
{
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
long long f[2000005];
long long C(int n, int m)
{
    if (n < m) return 0;
    return f[n] * pow_mod(f[m] * f[n - m] % MOD, MOD - 2) % MOD;
}
int main()
{
    int n, m;
    f[0] = 1;
    for (int i = 1; i <= 2000000; i++)
        f[i] = f[i - 1] * i % MOD;
    scanf ("%d%d", &n, &m);
    long long ans = (C(n + m, m) - C(n + m, m - 1) + MOD) % MOD;
    printf("%lld", ans);
}