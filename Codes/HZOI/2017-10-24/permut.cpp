#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1005;
int f[MAXN][MAXN], Sum[MAXN][MAXN];
const int MOD = 10000;
int main()
{
    int T;
    scanf ("%d", &T);
    while (T--)
    {
        int n, k;
        scanf ("%d%d", &n, &k);
        memset(f, 0, sizeof (f));
        memset(Sum, 0, sizeof (Sum));
        f[1][0] = 1;
        for (int i = 0; i <= k; i++) Sum[1][i] = 1;
        for (int i = 2; i <= n; i++)
            for (int j = 0; j <= k; j++)
            {
                f[i][j] = (Sum[i - 1][j] - (j >= i ? Sum[i - 1][j - i] : 0) + MOD) % MOD;
                Sum[i][j] = (Sum[i][j - 1] + f[i][j]) % MOD;
            }
        printf("%d\n", f[n][k]);
    }
}
