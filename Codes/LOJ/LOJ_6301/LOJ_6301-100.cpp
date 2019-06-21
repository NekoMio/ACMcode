#include <cstdio>
#include <stdint.h>
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
const int MAXN = 200000, BASE = 76543;
const int32_t MOD = 1e9 + 7;
int f[20][20][(1 << 18) + 1], g[20][20][(1 << 18) + 1];
int a[20][20], ans[20][20];
// int tmp[(1 << 18) + 1];
int DP1(int n, int m)
{
    // f[0].clear();
    int M = (1 << (m + 1)) - 1;
    f[1][0][0] = 1;
    // int now = 0;
    // int Ans = 0;
    register int32_t k = 0, i, j;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
        {
            // now ^= 1;
            // f[now].clear();
            for (k = 0; k <= M; k++)
            {
                int S = k;
                int Sum = f[i][j - 1][k];
                char L = (S >> (j - 1)) & 1, U = (S >> j) & 1;
                if (a[i][j])
                {
                    if (L == 0 && U == 0)
                        f[i][j][S] = (f[i][j][S] + Sum) % MOD;
                    continue;
                }
                else if (L == 1 && U != 1)
                {
                    int nxt = S ^ (1 << (j - 1));
                    f[i][j][nxt] = (f[i][j][nxt] + Sum) % MOD;
                }
                else if (L != 1 && U == 1)
                {
                    int nxt = S ^ (1 << j);
                    f[i][j][nxt] = (f[i][j][nxt] + Sum) % MOD;
                }
                else if (L != 1 && U != 1)
                {
                    int nxt = S ^ (1 << (j - 1));
                    if (i != n)
                        f[i][j][nxt] = (f[i][j][nxt] + Sum) % MOD;
                    nxt = S ^ (1 << j);
                    if (j != m) 
                        f[i][j][nxt] = (f[i][j][nxt] + Sum) % MOD;
                    f[i][j][S] = (f[i][j][S] + Sum) % MOD;
                }
                // if (S == 0)
                //     Ans += Sum;
            }
        }
        for (int k = 0; k <= M; k++)
            f[i + 1][0][k << 1] = f[i][m][k];
        // for (k = 0; k < f[now].p; k++)
        //     f[now].v[k].Id <<= 1;
    }
    return f[n][m][0];
}

// f->g
int DP2(int n, int m)
{
    // f[0].clear();
    int M = (1 << (m + 1)) - 1;
    g[n][m + 1][0] = 1;
    // int now = 0;
    // int Ans = 0;
    register int32_t k = 0, i, j;
    for (i = n; i >= 1; i--)
    {
        for (j = m; j >= 1; j--)
        {
            // now ^= 1;
            // f[now].clear();
            for (k = 0; k <= M; k++)
            {
                int S = k;
                int Sum = g[i][j + 1][k];
                char L = (S >> (j - 1)) & 1, U = (S >> j) & 1;
                if (a[i][j])
                {
                    if (L == 0 && U == 0)
                        g[i][j][S] = (g[i][j][S] + Sum) % MOD;
                    continue;
                }
                else if (L == 1 && U != 1)
                {
                    int nxt = S ^ (1 << (j - 1));
                    g[i][j][nxt] = (g[i][j][nxt] + Sum) % MOD;
                }
                else if (L != 1 && U == 1)
                {
                    int nxt = S ^ (1 << j);
                    g[i][j][nxt] = (g[i][j][nxt] + Sum) % MOD;
                }
                else if (L != 1 && U != 1)
                {
                    int nxt = S ^ (1 << (j - 1));
                    if (j != 1)
                        g[i][j][nxt] = (g[i][j][nxt] + Sum) % MOD;
                    nxt = S ^ (1 << j);
                    if (i != 1) 
                        g[i][j][nxt] = (g[i][j][nxt] + Sum) % MOD;
                    g[i][j][S] = (g[i][j][S] + Sum) % MOD;
                }
                // if (S == 0)
                //     Ans += Sum;
            }
        }
        for (int k = M; k >= 0; k--)
        // {
            g[i - 1][m + 1][k >> 1] = g[i][1][k];
            // printf ("%d %d %d %d\n", k >> 1, k, g[i - 1][m + 1][k >> 1], g[i][1][k]);
        // }
        // for (k = 0; k < f[now].p; k++)
        //     f[now].v[k].Id <<= 1;
    }
    return g[1][1][0];
}
int main()
{

    char n = read(), m = read();
    register int i, j, k;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            a[i][j] = read();
    DP1(n, m), DP2(n, m);
    int M = (1 << (m + 1)) - 1;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
        {
            if (a[i][j]) continue;
            int Sum = 0;
            for (k = 0; k <= M; k++)
            {
                char L = (k >> (j - 1)) & 1, U = (k >> j) & 1;
                if (L == 0 && U == 0)
                    (Sum += 1ll * f[i][j - 1][k] * g[i][j + 1][k] % MOD) %= MOD;
            }
            ans[i][j] = Sum;
        }
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            printf ("%d%c", ans[i][j], " \n"[j == m]);
    // while (1);
}