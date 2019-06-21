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
const int MOD = 1e9 + 7;
const int MAXN = 52;
int g[MAXN][MAXN][MAXN];
int C[MAXN][MAXN], F[MAXN], d[MAXN];
int f[MAXN][MAXN];
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++) d[i] = read();
    g[0][0][0] = 1;
    F[0] = 1, F[1] = 1, F[2] = 1;
    for (int i = 3; i <= n; i++) F[i] = 1ll * F[i - 1] * i % MOD;
    C[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= n; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
    for (int j = 0; j <= n; j++)
        for (int k = 0; k + j <= n; k++)
            if (j + k > 0)
            {
                if (j == 0 && k > 1)
                    for (int l = 2; l <= k; l++)
                        g[0][j][k] = (g[0][j][k] + 1ll * g[0][j][k - l - 1] * C[k - 1][l] % MOD * F[l] % MOD) % MOD;
                if (j > 1) g[0][j][k] = (g[0][j][k] + 1ll * g[0][j - 2][k] * (j - 1) % MOD) % MOD;
                if (k > 0) g[0][j][k] = (g[0][j][k] + 1ll * g[0][j][k - 1] * k % MOD) % MOD;
            }
    for (int i = 1; i <= n; i++)
        for (int j = 0; j + i <= n; j++)
            for (int k = 0; j + k + i <= n; k++)
            {
                if (j > 0) g[i][j][k] = (g[i][j][k] + 1ll * g[i - 1][j - 1][k] * j % MOD) % MOD;
                if (k > 0) g[i][j][k] = (g[i][j][k] + 1ll * g[i - 1][j + 1][k - 1] * k % MOD) % MOD;
            }
    f[d[1] + 1][d[1]] = 1;
    for (int i = d[1] + 2; i <= n; i++)
        for (int j = 1; j <= i - d[1] - 1; j++)
        {
            int p2 = 0, p3 = 0;
            for (int k = 1; k <= i - j; k++)
            {
                if (d[i - j - k + 1] == 2) p2++;
                else p3++;
                f[i][j] = (f[i][j] + 1ll * f[i - j][k] * g[j][p2][p3] % MOD) % MOD; 
            }
        }
    int p2(0), p3(0);
    int ans = 0;
    for (int j = 1; j < n; j++)
    {
        if (d[n - j + 1] == 2) p2++;
        else p3++;
        ans = (ans + 1ll * f[n][j] * g[0][p2][p3] % MOD) % MOD;
    }
    printf ("%d\n", ans);
}
