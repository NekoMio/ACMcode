#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1005;
const int MOD = 105225319;
long long g[MAXN], f[MAXN], ans[MAXN];
long long C[MAXN][MAXN];
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
int main()
{
    int n = read(), m = read();
    if (n == 1) return printf ("0\n"), 0;
    C[0][0] = 1;
    for (int i = 1; i <= 1000; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= 1000; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
    g[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= i; j++)
            g[i] = (g[i] + C[i][j] * pow_mod(m + 1, (i - j) * j) % MOD * pow_mod(2, MOD - 2) % MOD) % MOD;
    f[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j <= i - 2; j++)
            f[i] = (f[i] + C[i - 1][j] * 2 % MOD * f[j + 1] % MOD * g[i - j - 1] % MOD) % MOD;
        f[i] = (g[i] - f[i] + MOD) % MOD;
    }
    ans[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= i - 1; j++)
            ans[i] = (ans[i] + C[i - 1][j] * f[j + 1] % MOD * ans[i - j - 1] % MOD) % MOD;
    printf ("%lld\n", ans[n]);
}