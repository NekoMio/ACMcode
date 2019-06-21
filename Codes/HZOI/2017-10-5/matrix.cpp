#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int MOD = 998244353;
int l[3005], r[3005];
long long f[3005][3005], A[3005][3005];
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    A[0][0] = 1;
    for (int i = 1; i <= 3000; i++)
    {
        A[i][0] = 1;
        for (int j = 1; j <= 3000; j++)
            A[i][j] = A[i][j - 1] * (i - j + 1) % MOD;
    }
    int a, b;
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &a, &b), l[a]++, r[b]++;
    for (int i = 1; i <= m; i++)
        l[i] += l[i - 1], r[i] += r[i - 1];
    f[1][0] = 1;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 0; j <= r[i]; j++)
        {
            if (j <= i - l[i - 1])
                f[i][j] = f[i][j] * A[i - l[i - 1] - j][l[i] - l[i - 1]] % MOD;
            else
                f[i][j] = 0;
        }
        if (i == m) break;
        for (int j = 0; j <= r[i]; j++)
        {
            f[i + 1][j] = (f[i + 1][j] + f[i][j]) % MOD;
            if (j != r[i + 1])
                f[i + 1][j + 1] = (f[i + 1][j + 1] + f[i][j] * (r[i + 1] - j) % MOD) % MOD;
        }
    }
    printf("%lld", f[m][n]);
}