#include <cstdio>
#include <algorithm>
#include <cstring>
#define int long long
const int MOD = 1e9 + 7;
using namespace std;
int f[100050];
int Pow[100050], g[100050];
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return ans;
}
signed main()
{
    freopen("xvii.in", "r", stdin);
    freopen("xvii.out", "w", stdout);
    int n;
    scanf ("%lld", &n);
    f[0] = 1, Pow[0] = 1;
    for (int i = 1; i <= n; i++)
        f[i] = f[i - 1] * i % MOD, Pow[i] = Pow[i - 1] * 2 % MOD;
    for (int i = 1; i <= n; i++)
        g[i] = (g[i - 1] * i + (Pow[i - 1] - 1) * f[i - 1] % MOD) % MOD;
    printf ("%lld", g[n] * pow_mod(f[n], MOD - 2) % MOD);
}