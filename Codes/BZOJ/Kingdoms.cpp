#include <cstdio>
#include <cstring>
#include <algorithm>
int ans[25];
int a[25][25];
bool ok[(1 << 20) + 1];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &a[i][j]);
        memset(ok, 0, sizeof(ok));
        int N = (1 << n) - 1;
        ok[N] = 1;
        for (int i = N; i >= 0; i--)
        {
            if (ok[i])
            {
                for (int j = 0; j < n; j++)
                    if (i & (1 << j))
                    {
                        int Sum = 0;
                        for (int k = 0; k < n; k++)
                            if (i & (1 << k))
                                Sum += a[j][k];
                        if (Sum > 0)
                            ok[i ^ (1 << j)] = 1;
                    }
            }
        }
        ans[0] = 0;
        for (int i = 0; i < n; i++)
            if (ok[1 << i])
                ans[++ans[0]] = i + 1;
        if (ans[0])
        {
            for (int i = 1; i < ans[0]; i++)
                printf("%d ", ans[i]);
            printf("%d\n", ans[ans[0]]);
        }
        else
            printf("0\n");
    }
}