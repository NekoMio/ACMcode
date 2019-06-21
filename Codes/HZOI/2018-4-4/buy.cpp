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
const int MAXN = 15;
int c[MAXN], n, m, k, cnt;
int use[(1 << 11) + 1];
const int MOD = 998244353;
int Num(unsigned int x)
{
    unsigned int tmp;
    tmp = x 
        - ((x >> 1) & 033333333333)
        - ((x >> 2) & 011111111111);
    tmp = (tmp + (tmp >> 3)) & 030707070707;
    return tmp % 63;
}
bool Judge(int x)
{
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (x & (1 << (i - 1)))
            ans = ans + c[i];
    return ans <= m;
}
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
int status[(1 << 11) + 1];
long long f[(1 << 11) + 1][15];
long long pw[15];
long long F[1000005], Inv[1000005];
long long C(int n, int m)
{
    if (n < m) return 0;
    return F[n] * Inv[m] % MOD * Inv[n - m] % MOD;
}
int DP(int S)
{
    if (!S) return pow_mod(cnt, k);
    memset (f, 0, sizeof (f));
    memset (status, 0, sizeof (status));
    int tot = 0;
    for (int i = 1; i <= cnt; i++)
        if (!(use[i] & S)) ++tot;
        else status[use[i] & S]++;
    f[0][0] = 1;
    for (int i = S; i; i = S & (i - 1))
    {
        int t = i ^ S;
        for (int j = 0; j <= Num(t); j++)
            if (f[t][j])
                for (int z = i; z; z = (z - 1) & i)
                    f[t | z][j + 1] = (f[t | z][j + 1] + f[t][j] * status[z] % MOD) % MOD;
    }
    for (int i = 0; i <= n; i++)
        if (i <= k) pw[i] = pow_mod(tot, k - i);
        else pw[i] = 0;
    int ans = 0;
    for (int i = S; ; i = (i - 1) & S)
    {
        for (int j = 0; j <= Num(i); j++)
            ans = (ans + 1ll * f[i][j] * C(k, j) % MOD * pw[j] % MOD) % MOD;
        if (!i) break;
    }
    return ans;
}
int main()
{
    n = read(), m = read(), k = read();
    F[0] = 1;
    for (int i = 1; i <= k; i++)
        F[i] = F[i - 1] * i % MOD;
    Inv[k] = pow_mod(F[k], MOD - 2);
    for (int i = k - 1; i >= 0; i--)
        Inv[i] = Inv[i + 1] * (i + 1) % MOD;
    for (int i = 1; i <= n; i++)
        c[i] = read();
    int N = (1 << n) - 1;
    for (int i = 0; i <= N; i++)
        if (Judge(i))
            use[++cnt] = i;
    long long ans = 0;
    for (int i = 0; i <= N; i++)
    {
        int t = Num(i) & 1;
        if (t) 
            ans = (ans - DP(i) + MOD) % MOD;
        else 
            ans = (ans + DP(i) + MOD) % MOD;
    }
    printf ("%lld\n", ans);
    // while (1);
}