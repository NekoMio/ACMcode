#include <cstdio>
#include <cstring>
#include <algorithm>
int MOD = 1e9 + 7;
using namespace std;
long long f[3][205][205];
char A[1005], B[205];
int main()
{
    freopen ("2015substring.in", "r", stdin);
    freopen ("2015substring.out", "w", stdout);
    int n, m, k;
    scanf ("%d%d%d", &n, &m, &k);
    scanf ("%s%s", A + 1, B + 1);
    f[0][0][0] = f[1][0][0] = f[2][0][0] = 1;
    int now = 0;
    for (int i = 1; i <= n; i++)
    {
        (now += 1) %= 3;
        memset (f[now], 0, sizeof (f[now]));
        f[now][0][0] = 1;
        for (int j = 1; j <= m; j++)
        {
            for (int l = 1; l <= k; l++)
            {
                (f[now][j][l] += f[(now + 2) % 3][j][l]) %= MOD; 
                if (A[i] == B[j] && l) (f[now][j][l] += f[(now - 1 + 3) % 3][j - 1][l - 1]) %= MOD;
                if (A[i] == B[j] && A[i - 1] == B[j - 1] && i >= 2)
                    (f[now][j][l] += (f[(now + 2) % 3][j - 1][l] - f[(now + 1) % 3][j - 1][l]) % MOD + MOD) %= MOD;
                // printf ("i = %d, j = %d, l = %d: f = %d\n", i, j, l, f[now][j][l]);
            }
        }
    }
    printf ("%lld", f[now][m][k]);
    // while (1);
}