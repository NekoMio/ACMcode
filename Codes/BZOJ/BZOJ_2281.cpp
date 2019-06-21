#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
const int MAXN = 10005;
const int MOD = 1e9 + 7;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int C[MAXN][205], f[25][MAXN];
signed main()
{
    int n = read(), K = read() / 2, d = read();
    C[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= min(2 * K, i); j++)
        {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
        }
    }
    f[0][0] = 1;
    for (int i = 0; i <= 20; i++)
    {
        for (int j = 0; j <= n - 2 * K; j++)
        {
            for (int k = 0; k * (d + 1) <= K && j + k * (d + 1) * (1 << i) <= n - 2 * K; k++)
            {
                f[i + 1][j + k * (d + 1) * (1 << i)] = (f[i + 1][j + k * (d + 1) * (1 << i)] + f[i][j] * C[K][k * (d + 1)] % MOD) % MOD;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= n - 2 * K; i++)
        ans = (ans + f[21][i] * C[n - i - K][K] % MOD) % MOD;
    printf ("%d\n", (C[n][K * 2] - ans + MOD) % MOD);
}