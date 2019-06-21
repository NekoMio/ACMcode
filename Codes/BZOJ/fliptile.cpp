#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
int n, m;
int b[17][17], a[17][17], op[17][17];
inline void DoChange(int x)
{
    for (int j = 1; j <= n; j++)
    {
        if (op[x][j])
        {
            a[x - 1][j] ^= 1;
            a[x][j - 1] ^= 1;
            a[x][j + 1] ^= 1;
            a[x + 1][j] ^= 1;
        }
    }
}
inline bool ok()
{
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (a[i][j] == 1)
                return 0;
        }
    }
    return 1;
}
inline void print()
{
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%d ", op[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    //freopen("fliptile.in", "r", stdin);
    //freopen("fliptile.out", "w", stdout);
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &b[i][j]);
        }
    int N = (1 << n) - 1;
    for (int i = 0; i <= N; i++)
    {
        memcpy(a, b, sizeof(a));
        memset(op, 0, sizeof(op));
        for (int j = 1; j <= n; j++)
        {
            if (i & (1 << (j - 1)))
            {
                op[1][j] = 1;
                a[1 - 1][j] ^= 1;
                a[1][j - 1] ^= 1;
                a[1][j] ^= 1;
                a[1][j + 1] ^= 1;
                a[1 + 1][j] ^= 1;
            }
        }
        for (int j = 1; j < m; j++)
        {
            for (int k = 1; k <= n; k++)
            {
                if (a[j][k])
                {
                    op[j + 1][k] = 1;
                    a[j][k] ^= 1;
                    a[j + 1][k] ^= 1;
                    a[j + 1][k - 1] ^= 1;
                    a[j + 1][k + 1] ^= 1;
                    a[j + 2][k] ^= 1;
                }
            }
        }
        if (ok())
        {
            print();
            //while (1);
            exit(0);
        }
    }
    printf("IMPOSSIBLE\n");
}