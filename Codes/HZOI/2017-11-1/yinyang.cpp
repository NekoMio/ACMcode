#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int MOD = 1e9 + 7;
int n, m;
char Mp[1005][1005];
long long F[1005][1005];
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int Min[1005], Max[1005];
int Sum1[1005], Sum2[1005], Sum3[1005], Sum4[1005];
int SumB, SumM;
int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
        scanf("%s", Mp[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            SumB += Mp[i][j] == 'B', SumM += Mp[i][j] == 'W';
    // memset (Min, -1, sizeof (Min));
    memset (Max, -1, sizeof (Max));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (Mp[i][j] == 'B' && Max[i] == -1)
                Max[i] = j - 1;
            if (Mp[i][j] == 'W')
                Min[i] = j;
        }
    }
    for (int i = 1; i <= n; i++)
        if (Max[i] == -1)
            Max[i] = m;
    int ans = 0;
    for (int i = Min[1]; i <= Max[1]; i++)
        F[1][i] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = Min[i]; j <= Max[i]; j++)
            for (int k = 0; k <= j; k++)
                (F[i][j] += F[i - 1][k]) %= MOD;
    for (int i = Min[n]; i <= Max[n]; i++)
        (ans += F[n][i]) %= MOD;
    memset(F, 0, sizeof(F));
    for (int i = Min[1]; i <= Max[1]; i++)
        F[1][i] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = Min[i]; j <= Max[i]; j++)
            for (int k = j; k <= m; k++)
                (F[i][j] += F[i - 1][k]) %= MOD;
    for (int i = Min[n]; i <= Max[n]; i++)
        (ans += F[n][i]) %= MOD;
    memset(Max, -1, sizeof(Max));
    memset(Min, 0, sizeof(Min));
    for (int i = 1; i <= n; i++)
    {
        for (int j = m; j >= 1; j--)
        {
            if (Mp[i][j] == 'B' && Max[i] == -1)
                Max[i] = m - j;
            if (Mp[i][j] == 'W')
                Min[i] = m - j + 1;
        }
    }
    for (int i = 1; i <= n; i++)
        if (Max[i] == -1)
            Max[i] = m;
    memset(F, 0, sizeof(F));
    for (int i = Min[1]; i <= Max[1]; i++)
        F[1][i] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = Min[i]; j <= Max[i]; j++)
            for (int k = 0; k <= j; k++)
                (F[i][j] += F[i - 1][k]) %= MOD;
    for (int i = Min[n]; i <= Max[n]; i++)
        (ans += F[n][i]) %= MOD;
    memset(F, 0, sizeof(F));
    for (int i = Min[1]; i <= Max[1]; i++)
        F[1][i] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = Min[i]; j <= Max[i]; j++)
            for (int k = j; k <= m; k++)
                (F[i][j] += F[i - 1][k]) %= MOD;
    for (int i = Min[n]; i <= Max[n]; i++)
        (ans += F[n][i]) %= MOD;
    int t = 0;
    for (int i = 1; i <= n; i++)
    {
        Sum1[i] = Sum1[i - 1], Sum2[i] = Sum2[i - 1];
        for (int j = 1; j <= m; j++)
        {
            Sum1[i] += Mp[i][j] == 'W';
            Sum2[i] += Mp[i][j] == 'B';
        }
        if (Sum1[i] == SumM && Sum2[i] == 0) t++;
        if (Sum1[i] == 0 && Sum2[i] == SumB) t++;
    }
    for (int j = 0; j <= m; j++)
    {
        if (j != 0)
            Sum3[j] = Sum3[j - 1], Sum4[j] = Sum4[j - 1];
        for (int i = 1; i <= n; i++)
        {
            Sum3[j] += Mp[i][j] == 'W';
            Sum4[j] += Mp[i][j] == 'B';
        }
        if (Sum3[j] == SumM && Sum4[j] == 0) t++;
        if (Sum3[j] == 0 && Sum4[j] == SumB) t++;
    }
    printf("%d", (ans - t + MOD) % MOD);
    // while (1);
}