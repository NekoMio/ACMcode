#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long F[65][65];
long long ans = 1;
int main()
{
    freopen("hanoi.in", "r", stdin);
    freopen("hanoi.out", "w", stdout);
    int n, m;
    scanf ("%d%d", &n, &m);
    if (m == 3)
    {
        for (int i = 1; i <= n; i++)
            ans = ans * 2;
        printf ("%lld\n", ans - 1);
    }
    else
    {
        memset (F, 0x3f, sizeof (F));
        F[1][3] = 1;
        for (int i = 2; i <= n; i++) F[i][3] = F[i - 1][3] * 2 + 1;
        for (int j = 4; j <= m; j++)
        {
            F[1][j] = 1;
            for (int i = 2; i <= n; i++)
                for (int k = 1; k < i; k++)
                    F[i][j] = min(F[i][j], 2 * F[k][j] + F[i - k][j - 1]);
        }
        printf ("%lld\n", F[n][m]);
    }
    fclose(stdin), fclose(stdout);
    return 0;
}