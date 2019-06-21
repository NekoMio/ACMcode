#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int m;
double ans = 0;
double dp[1005][1005][15], s[1005][1005];
double a[1005][15], g[1005][1005][15];
int main()
{
#ifndef ONLINE_JUDGE
    freopen("necklace.in", "r", stdin);
    freopen("necklace.out", "w", stdout);
#endif
    int n, m;
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%lf", &a[i][j]);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            g[i][i][j] = a[i][j];
        for (int j = i + 1; j <= n; j++)
            for (int k = 1; k <= m; k++)
                g[i][j][k] = g[i][j - 1][k] * a[j][k];
    }
    for (int i = 0; i <= n; i++) s[0][i] = 1; 
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k <= m; k++)
            {
                dp[i][j][k] = s[i - 1][j] * g[i][i][k] - (i - j - 1 >= 0 ? (s[i - j - 1][j] - dp[i - j - 1][j][k]) * g[i - j][i][k] : 0);
                s[i][j] += dp[i][j][k];
            }
        }
    }
    for (int i = 1; i <= n; i++)
            ans += (s[n][i] - s[n][i - 1]) * i;
    printf("%.5lf", ans);
    // while (1);
}