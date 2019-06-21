#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 998244353;
long long pow_mod(long long a, long long b)
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
long long f[10000007], Inv[10000007];
long long C(long long n, long long m)
{
    if (m > n || n < 0 || m < 0) return 0;
    return (f[n] * Inv[n - m] % MOD) * Inv[m] % MOD;
}
int main()
{
    // freopen("city.in", "r", stdin);
    // freopen("city.out", "w", stdout);
    f[0] = 1;
    for (int i = 1; i <= 10000000; i++)
        f[i] = f[i - 1] * i % MOD;
    Inv[10000000] = pow_mod(f[10000000], MOD - 2);
    for (int i = 9999999; i >= 0; i--) Inv[i] = Inv[i + 1] * (i + 1) % MOD;
    int n, m, k;
    scanf ("%d%d%d", &n, &m, &k);
    if (n >= m) printf("0\n");
    else
    {
        long long ans = 0;
        for (int i = 1; i <= m; i++)
        {
            if (i & 1)
                ans = (ans + (C(n, i) * C(m - (long long)i * k - 1, n - 1) % MOD)) % MOD;
            else
                ans = (ans - (C(n, i) * C(m - (long long)i * k - 1, n - 1) % MOD) + MOD) % MOD;
        }
        printf("%lld\n", (C(m - 1, m - n) - ans + MOD) % MOD);
    }
    // while(1);
}