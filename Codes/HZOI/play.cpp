#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1000000007;
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if(b&1)
            ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
long long f[2005], g[2005];
long long fn[2005];
long long C[2005][2005];
int main()
{
    // freopen("play.in", "r", stdin);
    // freopen("play.out", "w", stdout);
    int n;
    scanf("%d",&n);
    C[0][0] = 1;
    for (int i = 1; i <= 2000; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= 2000; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
    for (int i = 1; i <= n; i++)
    {
        f[i] = g[i] = pow_mod(2, (i - 1) * (i - 2) / 2);
        for (int j = 1; j < i; j++)
        {
            f[i] = (f[i] - (f[j] * g[i - j] % MOD) * C[i - 1][j - 1] % MOD + MOD) % MOD;
        }
    }
    printf("%lld", f[n] * C[n][2] % MOD);
}