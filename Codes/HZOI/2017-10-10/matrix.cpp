#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
long long f[35][35][2000];
int a[35][35];
int main()
{
    int T;
    scanf ("%d", &T);
    while (T--)
    {
        int n, m;
        scanf ("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                scanf ("%d", &a[i][j]);
        memset (f, 0x3f, sizeof (f));
        f[0][1][0] = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                for (int k = 0; k <= 1900; k++)
                {
                    if (f[i - 1][j][k] >= 0x3f3f3f3f3f && f[i][j - 1][k] >= 0x3f3f3f3f3f) continue;
                    f[i][j][k + a[i][j]] = min(f[i - 1][j][k], f[i][j - 1][k]) + (n + m - 1) * a[i][j] * a[i][j] - a[i][j] * a[i][j] - 2 * k * a[i][j];
                }
            }
        }
        long long ans = 0x3f3f3f3f3f;
        for (int i = 0; i <= 1900; i++)
        {
            ans = min(ans, f[n][m][i]);
        }
        printf("%lld\n", ans);
    }
}