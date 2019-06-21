// 100 pts nlog^2(m)
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
const int MOD = 998244353;
int g[25][100005];
int f[100005][2];
int main()
{
    int n = read(), m = read();
    for (int i = 1; i <= m; i++) g[1][i] = 1, g[1][0]++;
    for (int i = 2; i <= 20; i++)
        for (int j = 1; j <= m; j++)
        {
            for (int k = 2 * j; k <= m; k += j)
                (g[i][j] += g[i - 1][k]) %= MOD;
            (g[i][0] += g[i][j]) %= MOD;
        }
    f[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int k = 0; k <= 1; k++)
            for (int j = 0; (1 << (j - 1)) <= m; j++)
                (f[i][(k + j) & 1] += 1ll * f[i - j - 1][k] * g[j + 1][0] % MOD) %= MOD;
    printf ("%d\n", (f[n][0] - f[n][1] + MOD) % MOD);
}