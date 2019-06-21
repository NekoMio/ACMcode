#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define LL long long
LL MOD;
LL pow_mod(LL a, LL b)
{
    LL ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
LL f[100005], Inv[100005];
LL C(LL n, LL m)
{
    if (n < m) return 0;
    if (m == n || m == 0) return 1;
    return ((f[n] * Inv[m]) % MOD * Inv[n - m]) % MOD;
}
LL lucas(LL n, LL m)
{
    if (n == m || m == 0) return 1;
    if (n < m) return 0;
    return lucas(n / MOD, m / MOD) * C(n % MOD, m % MOD) % MOD;
}
int main()
{
    LL n, m;
    scanf ("%lld%lld%lld", &n, &m, &MOD);
    f[0] = 1;
    for (int i = 1; i < MOD; i++)
        f[i] = f[i - 1] * i % MOD;
    Inv[MOD - 1] = pow_mod(f[MOD - 1], MOD - 2) % MOD;
    for (int i = MOD - 2; i >= 0; i--)
        Inv[i] = Inv[i + 1] * (i + 1) % MOD;
    printf ("%lld", lucas(n ,m));
}