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
int MOD; 
const int MAXN = 65;
int a[MAXN];
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
int vis[MAXN], st[MAXN];
int dfs(int x, int C)
{
    if (vis[x] == C) return 0;
    vis[x] = C;
    return dfs(a[x], C) + 1;
}
int DP[2][25][25][25];
int main()
{
    int Sr = read(), Sb = read(), Sg = read(), m = read();
    MOD = read();
    int n = Sr + Sb + Sg;
    int Ans = 0;
    memset (vis, -1, sizeof (vis));
    for (int i = 0; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
            a[j] = (i == 0 ? (j) : read());
        int cnt = 0;
        for (int j = 1; j <= n; j++)
            if (vis[j] != i)
                st[++cnt] = dfs(j, i);
        memset (DP, 0, sizeof (DP));
        DP[0][Sr][Sb][Sg] = 1;
        int now = 0;
        for (int j = 1; j <= cnt; j++)
        {
            now ^= 1;
            memset(DP[now], 0, sizeof (DP[now]));
            for (int r = 0; r <= Sr; r++)
                for (int b = 0; b <= Sb; b++)
                    for (int g = 0; g <= Sg; g++)
                    {
                        if (r + st[j] <= Sr) DP[now][r][b][g] = (DP[now][r][b][g] + DP[now ^ 1][r + st[j]][b][g]) % MOD;
                        if (b + st[j] <= Sb) DP[now][r][b][g] = (DP[now][r][b][g] + DP[now ^ 1][r][b + st[j]][g]) % MOD;
                        if (g + st[j] <= Sg) DP[now][r][b][g] = (DP[now][r][b][g] + DP[now ^ 1][r][b][g + st[j]]) % MOD;
                    }
        }
        Ans = (DP[now][0][0][0] + Ans) % MOD;
    }
    printf ("%d\n", 1ll * Ans * pow_mod(m + 1, MOD - 2) % MOD);
}