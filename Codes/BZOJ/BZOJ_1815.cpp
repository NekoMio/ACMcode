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
const int MAXN = 1005;
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}
int gd[MAXN][MAXN], f[MAXN];
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
int l[MAXN];
long long ans;
int n, m;
void Get_Ans(int cnt)
{
    long long C = 0;
    for (int i = 1; i <= cnt; i++) C = (C + l[i] / 2) % MOD;
    for (int i = 1; i <= cnt; i++)
        for (int j = i + 1; j <= cnt; j++)
            C = (C + gd[l[i]][l[j]]) % MOD;
    long long now = 1, len = 0;
    for (int i = 1; i <= cnt; i++)
    {
        if (l[i] != l[i - 1])
        {
            now = now * f[len] % MOD;
            len = 0;
        }
        len++;
    }
    now = now * f[len] % MOD;
    for (int i = 1; i <= cnt; i++) now = now * l[i] % MOD;
    long long S = f[n] * pow_mod(now, MOD - 2) % MOD;
    ans = (ans + S * pow_mod(m, C) % MOD) % MOD;
}
void DFS(int cnt, int x, int les)
{
    if (les == 0) return Get_Ans(cnt);
    if (les < x) return;
    cnt++;
    while (x <= les)
    {
        l[cnt] = x;
        DFS(cnt, x, les - x);
        x++;
    }
}
int main()
{
    n = read(), m = read();
    MOD = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            gd[i][j] = gcd(i, j);
    0[f] = 1;
    for (int i = 1; i <= n; i++)
        i[f] = 1ll * ((i - 1)[f]) * i % MOD;
    ans = 0;
    DFS(0, 1, n);
    printf ("%lld\n", ans * pow_mod(f[n], MOD - 2) % MOD);
}