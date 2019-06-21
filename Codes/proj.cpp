#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int F[52][(1 << 8) + 1][(1 << 8) + 1], G[52][(1 << 8) + 1][(1 << 8) + 1];
int a[55][55], n, m, N;
int check(int x, int S)
{
    int ans = 0;
    for (int i = 1; i <= m; i++)
    {
        if (((1 << (i - 1)) & S))
            ans += a[x][i];
    }
    return ans;
}
int Get_num(int x)
{
    int ans = 0;
    while (x)
    {
        if (x & 1)
            ans++;
        x >>= 1;
    }
    return ans;
}
int main()
{
    //freopen("proj.in", "r", stdin);
    //freopen("proj.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    memset(F, 0x3f, sizeof(F));
    N = (1 << m) - 1;
    for (int i = 0; i <= N; i++)
    {
        //if ((((i >> 1) | (i << 1) | i) & N) == N)
        //{
            int ans = check(1, i);
            F[1][0][i] = ans;
            G[1][0][i] = Get_num(i);
        //}
    }
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= N; j++)
            for (int k = 0; k <= N; k++)
                for (int m = 0; m <= N; m++)
                    if (((j | k | m | (k << 1) | (k >> 1)) & (N)) == N)
                    {
                        if (F[i][j][k] + check(i + 1, m) < F[i + 1][k][m])
                        {
                            F[i + 1][k][m] = F[i][j][k] + check(i + 1, m);
                            G[i + 1][k][m] = G[i][j][k] + Get_num(m);
                        }
                    }
    int ans = 0x3f3f3f4f, num = 0;
    for (int i = 0; i <= N; i++)
    {
        if (F[n + 1][i][0] < ans)
        {
            ans = F[n + 1][i][0];
            num = G[n + 1][i][0];
        }
        else if (F[n + 1][i][0] == ans)
        {
            if (num > G[n + 1][i][0])
                num = G[n + 1][i][0];
        }
    }
    printf("%d %d", num, ans);
    //while (1)
    ;
}