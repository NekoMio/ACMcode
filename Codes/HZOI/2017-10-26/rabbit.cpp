#include <cstdio>
const int MAXN = 2005;
long long f[MAXN][MAXN], Sum;
int MOD;
int main()
{
    // freopen("rabbit.in", "r", stdin);
    // freopen("rabbit.out", "w", stdout);
    int n;
    scanf ("%d%d", &n, &MOD);
    f[1][1] = 1 % MOD;
    for (int i = 2; i <= n; i++)
    {
        Sum = 0;
        for (int j = 1; j <= i; j++)
        {
            Sum = (Sum + f[i - 1][i - j]) % MOD;
            f[i][j] = Sum;
        }
    }
    printf ("%lld", f[n][n] * 2 % MOD);
    // fclose(stdin);
    // fclose(stdout);
}
