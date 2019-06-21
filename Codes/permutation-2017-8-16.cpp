#include <cstdio>
#include <cstring>
using namespace std;
#define LL long long
const LL MOD = 1e9 + 7;
LL F[1000005], g[1000005];
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
LL C(LL n, LL m)
{
    if (n < m)
        return 0;
    return F[n] * pow_mod(F[m] * F[n - m] % MOD, MOD - 2) % MOD;
}
int main()
{
    //freopen("permutation.in","r",stdin);
    //freopen("permutation.out","w",stdout);
    F[0] = 1;
    memset(g, -1, sizeof(g));
    g[1] = 0;
    g[0] = 1;
    for (int i = 1; i <= 1000000; i++)
        F[i] = F[i - 1] * i % MOD;
    for (int i = 2; i <= 1000000; i++)
        g[i] = (g[i - 1] + g[i - 2]) * (i - 1) %MOD;
    int T;
    scanf("%d", &T);
    LL n, m;
    while (T--)
    {
        scanf("%lld%lld", &n, &m);
        printf("%lld\n", g[n-m] * C(n, m) % MOD);
    }
}