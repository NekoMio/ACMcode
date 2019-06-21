#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
char s[50];
int mp[50][50];
const int INF = 0x3f3f3f3f;
int F[2][(1 << 9) + 1][4097];
int Min[4097];
int Get(int S, int x)
{
    S >>= x;
    S &= 1;
    return S;
}
int Set(int S, int j, int l)
{
    int x = S >> j;
    S -= (x << j);
    x >>= 1;
    S += (x << (j + 1));
    S += (l << j);
    return S;
}
int tmp[(1 << 9) + 1][4097];
void Solve(int n, int m, int A, int B, int Q)
{
    memset (Min, 0x3f, sizeof (Min));
    memset (F, 0x3f, sizeof (F));
    int N = (1 << (m + 1)) - 1;
    F[0][0][0] = 0;
    int now = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            now ^= 1;
            memset (F[now], 0x3f, sizeof (F[now]));
            for (int S = 0; S <= N; S++)
            {
                for (int k = 0; k <= Q; k++)
                {
                    if (F[now ^ 1][S][k] == INF) continue;
                    int L = Get(S, j - 1), U = Get(S, j);
                    if (!mp[i][j])
                    {
                        if (L == 0 && U == 0)
                        {
                            Min[k] = min(F[now ^ 1][S][k], Min[k]);
                            F[now][S][k] = min(F[now][S][k], F[now ^ 1][S][k]);
                        }
                        continue;
                    }
                    if (L == 0 && U == 0)
                    {
                        Min[k] = min(F[now ^ 1][S][k], Min[k]);
                        F[now][S][k] = min(F[now][S][k], F[now ^ 1][S][k]);
                        int nxt = Set(S, j - 1, 1);
                        if (i != n && mp[i + 1][j]) F[now][nxt][k + 1] = min(F[now][nxt][k + 1], F[now ^ 1][S][k]);
                        nxt = Set(S, j, 1);
                        if (j != m && mp[i][j + 1]) F[now][nxt][k + 1] = min(F[now][nxt][k + 1], F[now ^ 1][S][k]);
                        nxt = Set(nxt, j - 1, 1);
                        if (j != m && i != n && mp[i][j + 1] && mp[i + 1][j]) F[now][nxt][k + 2] = min(F[now][nxt][k + 2], F[now ^ 1][S][k] + A);
                    }
                    if (L == 1 && U == 0)
                    {
                        Min[k] = min(F[now ^ 1][S][k], Min[k]);
                        int nxt = Set(S, j - 1, 0);
                        F[now][nxt][k] = min(F[now][nxt][k], F[now ^ 1][S][k]);
                        if (i != n && mp[i + 1][j]) F[now][S][k + 1] = min(F[now][S][k + 1], F[now ^ 1][S][k] + A);
                        nxt = Set(nxt, j, 1);
                        if (j != m && mp[i][j + 1]) F[now][nxt][k + 1] = min(F[now][nxt][k + 1], F[now ^ 1][S][k] + B);
                        nxt = nxt | S;
                        if (i != n && j != m && mp[i + 1][j] && mp[i][j + 1]) F[now][nxt][k + 2] = min(F[now][nxt][k + 2], F[now ^ 1][S][k] + 2 * A + B);
                    }
                    if (L == 0 && U == 1)
                    {
                        Min[k] = min(F[now ^ 1][S][k], Min[k]);
                        int nxt = Set(S, j, 0);
                        F[now][nxt][k] = min(F[now][nxt][k], F[now ^ 1][S][k]);
                        if (j != m && mp[i][j + 1]) F[now][S][k + 1] = min(F[now][S][k + 1], F[now ^ 1][S][k] + A);
                        nxt = Set(nxt, j - 1, 1);
                        if (i != n && mp[i + 1][j]) F[now][nxt][k + 1] = min(F[now][nxt][k + 1], F[now ^ 1][S][k] + B);
                        nxt = nxt | S;
                        if (i != n && j != m && mp[i + 1][j] && mp[i][j + 1]) F[now][nxt][k + 2] = min(F[now][nxt][k + 2], F[now ^ 1][S][k] + 2 * A + B);
                    }
                    if (L == 1 && U == 1)
                    {
                        Min[k] = min(F[now ^ 1][S][k] + A, Min[k]);
                        int nxt = Set(S, j, 0); nxt = Set(nxt, j - 1, 0);
                        F[now][nxt][k] = min(F[now][nxt][k], F[now ^ 1][S][k] + A);
                        nxt = Set(nxt, j, 1);
                        if (j != m && mp[i][j + 1]) F[now][nxt][k + 1] = min(F[now][nxt][k + 1], F[now ^ 1][S][k] + 2 * A + B);
                        nxt = Set(S, j, 0);
                        if (i != n && mp[i + 1][j]) F[now][nxt][k + 1] = min(F[now][nxt][k + 1], F[now ^ 1][S][k] + 2 * A + B);
                        if (i != n && j != m && mp[i + 1][j] && mp[i][j + 1]) F[now][S][k + 2] = min(F[now][S][k + 2], F[now ^ 1][S][k] + 4 * A + 2 * B);
                    }
                    int x = 0;
                }
            }
        }
        memset (tmp, 0x3f, sizeof (tmp));
        for (int S = 0; S <= N; S++)
            for (int k = 0; k <= Q; k++)
                tmp[(S << 1) & N][k] = min(tmp[(S << 1) & N][k], F[now][S][k]);
        for (int S = 0; S <= N; S++)
            for (int k = 0; k <= Q; k++)
                F[now][S][k] = tmp[S][k];
    }
}
int main()
{
    int t = read();
    int n = read(), m = read(), A = read(), B = read();
    for (int i = 1; i <= n; i++)
    {
        scanf ("%s", s + 1);
        for (int j = 1; j <= m; j++)
            mp[i][j] = (s[j] == '0');
    }
    int Q = read();
    Solve(n, m, A, B, Q);
    for (int i = 1; i <= Q; i++)
        printf ("%d\n", Min[i]);
}