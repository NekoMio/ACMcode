#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int mp[205][6];
bool Use[205][6], Q[205][6];
int ans = 0, n, Max;
int f[205][2005][6];
int g[2005][6][6];
int main()
{
    // freopen ("snakevsblock.in", "r", stdin);
    // freopen ("snakevsblock.out", "w", stdout);
    n = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= 5; j++)
        {
            mp[i][j] = read();
            if (mp[i][j] > 0) Max += mp[i][j];
        }
    int m = read(), a, b;
    for (int i = 1; i <= m; i++)
        a = read(), b = read(), Q[a][b] = 1;
    memset (f, 0x80, sizeof (f));
    Max += 4;
    f[0][4][3] = 0;
    for (int i = 1; i <= n; i++)
    {
        memset (g, 0x80, sizeof (g));
        for (int j = 0; j <= Max; j++)
            for (int k = 1; k <= 5; k++)
                if (j >= mp[i][k])
                    g[j][k][k] = f[i - 1][j - mp[i][k]][k] + max(-mp[i][k], 0);
        for (int l = 2; l <= 5; l++)
            for (int k = 1; k <= 5 - l + 1; k++)
                for (int j = 0; j <= Max; j++)
                {
                    if (!Q[i][k] && j >= mp[i][k]) g[j][k][k + l - 1] = max(g[j][k][k + l - 1], g[j - mp[i][k]][k + 1][k + l - 1] + max(-mp[i][k], 0));
                    if (!Q[i][k + l - 2] && j >= mp[i][k + l - 1]) g[j][k][k + l - 1] = max(g[j][k][k + l - 1], g[j - mp[i][k + l - 1]][k][k + l - 2] + max(-mp[i][k + l - 1], 0));
                }
        for (int j = 0; j <= Max; j++)
            for (int k = 1; k <= 5; k++)
                for (int l = 1; l <= k; l++)
                    for (int r = k; r <= 5; r++)
                        f[i][j][k] = max(g[j][l][r], f[i][j][k]);
        for (int j = 0; j <= Max; j++)
            for (int k = 1; k <= 5; k++)
                ans = max(ans, f[i][j][k]);
    }
    printf ("%d", ans);
}