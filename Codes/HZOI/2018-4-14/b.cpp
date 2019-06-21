#include <cstdio>
#include <stdint.h>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MOD = 10007;
int f[2][(1 << 7) + 1][(1 << 7) + 1];
int Num[4] = {0, 1, 1, 2};
int Calc(int S, int j)
{
    int U = (S >> j) & 1, L = (S >> (j - 1)) & 1;
    return U + L;
}
int Clear(int x, int j)
{
    if (x & (1 << (j - 1))) x ^= (1 << (j - 1));
    if (x & (1 << j)) x ^= (1 << j);
    return x;
}
bool Judge(int S, int t, int i, int j, int n, int m)
{
    if (i == n && (t & 1)) return 0;
    if (j == m && (t & 2)) return 0;
    return 1;
}
int mp[67][7];
int tmp[(1 << 7) + 1][(1 << 7) + 1];
int DP(int n, int m)
{
    f[0][0][0] = 1;
    int now = 0;
    int M = (1 << (m + 1)) - 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            now ^= 1;
            memset (f[now], 0, sizeof (f[now]));
            for (int k = 0; k <= M; k++)
                for (int l = 0; l <= M; l++) if (f[now ^ 1][k][l])
                    for (int t = 0; t <= 3; t++) if ((Num[t] + Calc(k, j) == mp[i][j] || mp[i][j] == -1) && Judge(k, t, i, j, n, m))
                        for (int g = 0; g <= 3; g++)
                            if (Num[g] + Calc(l, j) == Num[t] + Calc(k, j) && Judge(l, g, i, j, n, m))
                                (f[now][Clear(k, j) | (t << (j - 1))][Clear(l, j) | (g << (j - 1))] += f[now ^ 1][k][l]) %= MOD;
        }
        for (int j = M; j >= 0 ; j--)
            for (int k = M; k >= 0; k--)
                tmp[(j << 1) & M][(k << 1) & M] = f[now][j][k];
        for (int j = 0; j <= M; j++)
            for (int k = 0; k <= M; k++)
                f[now][j][k] = tmp[j][k];
    }
    return f[now][0][0];
}
int main()
{
    int n = read(), m = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            mp[i][j] = read();
    printf ("%d\n", DP(n, m));
}