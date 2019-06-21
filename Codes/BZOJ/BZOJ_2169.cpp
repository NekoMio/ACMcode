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
const int MAXN = 1005;
const int MOD = 10007;
int du[MAXN];
int DP[MAXN][MAXN];
int C[MAXN][MAXN];
int pow_mod(int a, int b)
{
    int ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
int Inv(int x)
{
    return pow_mod(x, MOD - 2);
}
int main()
{
    int n = read(), m = read(), k = read();
    for (int i = 1; i <= m; i++)
    {
        int a = read(), b = read();
        du[a]++, du[b]++;
    }
    C[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= n; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
    int tmp = 0;
    for (int i = 1; i <= n; i++)
        if (du[i] & 1)
            tmp++;
    DP[0][tmp] = 1;
    for (int i = 1; i <= k; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (j + 2 <= n) DP[i][j] = (DP[i][j] + DP[i - 1][j + 2] * C[j + 2][2] % MOD) % MOD;
            if (j >= 2) DP[i][j] = (DP[i][j] + DP[i - 1][j - 2] * C[n - j + 2][2] % MOD) % MOD;
            DP[i][j] = (DP[i][j] + DP[i - 1][j] * (n - j) % MOD * j % MOD) % MOD;
            if (i >= 2) DP[i][j] = ((DP[i][j] - DP[i - 2][j] * (C[n][2] - (i - 2)) % MOD) % MOD + MOD) % MOD;
            DP[i][j] = DP[i][j] * Inv(i) % MOD;
        }
    }
    printf ("%d\n", DP[k][0]);
    // while (1);
}