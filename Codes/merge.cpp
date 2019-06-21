#include <cstdio>
#include <cstring>
#include <bitset>
using namespace std;
int a[400], c;
int s[1 << 8];
long long w[1 << 8], f[305][305][1 << 8], INF, ans;
int main()
{
    // freopen("merge.in","r",stdin);
    // freopen("merge.out","w",stdout);
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%1d", &a[i]);
    for (int i = 0; i < (1 << k); i++)
        scanf("%d%lld", &s[i], &w[i]);
    memset(f, 0x80, sizeof(f));
    memset(&INF, 0x80, sizeof(INF));
    for (int i = 1; i <= n; i++)
        f[i][i][a[i]] = 0;
    for (int l = 2; l <= n; l++)
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            int len = j - i;
            while (len >= k)
                len -= k - 1;
            for (int m = j; m > i; m -= k - 1)
            {
                for (int S = 0; S < (1 << len); S++)
                {
                    if (f[i][m - 1][S] != INF)
                    {
                        if (f[m][j][0] != INF)
                            f[i][j][S << 1] = max(f[i][j][S << 1], f[i][m - 1][S] + f[m][j][0]);
                        if (f[m][j][1] != INF)
                            f[i][j][S << 1 | 1] = max(f[i][j][S << 1 | 1], f[i][m - 1][S] + f[m][j][1]);
                    }
                }
            }
            if (len == k - 1)
            {
                long long g[2];
                g[0] = g[1] = INF;
                for (int S = 0; S < (1 << k); S++)
                    if (f[i][j][S] != INF)
                        g[s[S]] = max(g[s[S]], f[i][j][S] + w[S]);
                f[i][j][0] = g[0];
                f[i][j][1] = g[1];
            }
        }
    }
    for (int i = 0; i < (1 << k); i++)
        ans = max(ans, f[1][n][i]);
    printf("%lld\n", ans);
    //while(1);
}