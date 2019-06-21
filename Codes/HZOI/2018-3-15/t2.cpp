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
const int MAXN = 2005;
const int MOD = 1e9 + 7;
long long f[2][MAXN][MAXN];
long long g[3][MAXN][MAXN];
int a[MAXN];
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    long long ans = 0;
    f[0][0][0] = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (a[i + 1] == 0 || a[i + 1] == -1)
            {
                f[1][i + 1][max(j - 1, 0)] = (f[1][i + 1][max(j - 1, 0)] + f[1][i][j] + f[0][i][j]) % MOD;
                f[0][i + 1][max(j - 1, 0)] = (f[0][i + 1][max(j - 1, 0)] + f[0][i][j]) % MOD;
            }
            if (a[i + 1] == 1 || a[i + 1] == -1)
            {
                //if (a[i + 1] == -1) f[1][i + 1][max(2, j + 1)] = (f[1][i + 1][max(j + 1, 2)] + f[1][i][j] + f[0][i][j]) % MOD;
                //else 
                f[1][i + 1][max(2, j + 1)] = (f[1][i + 1][max(j + 1, 2)] + f[1][i][j]) % MOD;
                // f[1][i + 1][max(2, j + 1)] = (f[1][i + 1][max(j + 1, 2)] + f[1][i][j] + f[0][i][j]) % MOD;
                f[0][i + 1][max(2, j + 1)] = (f[0][i + 1][max(j + 1, 2)] + f[0][i][j]) % MOD;
            }
        }
    }
    g[0][n + 1][0] = 1;
    for (int i = n + 1; i >= 2; i--)
    {
        for (int j = 0; j <= n; j++)
        {
            if (a[i - 1] == 1 || a[i - 1] == -1)
            {
                g[2][i - 1][max(j - 1, 0)] = (g[2][i - 1][max(j - 1, 0)] + g[2][i][j] + 2 * g[1][i][j] + g[0][i][j]) % MOD;
                g[1][i - 1][max(j - 1, 0)] = (g[1][i - 1][max(j - 1, 0)] + g[1][i][j] + g[0][i][j]) % MOD;
                g[0][i - 1][max(j - 1, 0)] = (g[0][i - 1][max(j - 1, 0)] + g[0][i][j]) % MOD;
            }
            if (a[i - 1] == 0 || a[i - 1] == -1)
            {
                g[2][i - 1][max(1, j + 1)] = (g[2][i - 1][max(j + 1, 1)] + g[2][i][j]) % MOD;
                g[1][i - 1][max(1, j + 1)] = (g[1][i - 1][max(j + 1, 1)] + g[1][i][j]) % MOD;
                g[0][i - 1][max(1, j + 1)] = (g[0][i - 1][max(j + 1, 1)] + g[0][i][j]) % MOD;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        //f0[i-1][0]*g2[i][0]+f1[i-1][0]*g1[i][0]
        // printf ("%lld %lld %lld %lld\n", f[0][i - 1][0], g[2][i][0], f[1][i - 1][0], g[1][i][0]);
        ans = (ans + f[0][i - 1][0] * g[2][i][0] % MOD + f[1][i - 1][0] * g[1][i][0] % MOD) % MOD; 
    }
    printf ("%lld\n", ans);
}