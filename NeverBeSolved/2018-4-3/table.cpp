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
int sp[20000001], f[20000001], Inv[20000001];
long long C(int n, int m)
{
    if (m > n) return 0;
    return 1ll * f[n] * Inv[m] % MOD * Inv[n - m] % MOD;
}
int Inva, Invb;
int powa[20000001], powinva[20000001], powb[20000001];
int main()
{
    // freopen ("table3.in", "r", stdin);
    // freopen ("table.out", "w", stdout);
    // freopen ("1.in", "r", stdin);
    // freopen ("1.out", "w", stdout);
    int m = read(), n = read(), a = read(), b = read(), p = read(), q = read();
    Inva = pow_mod(a, MOD - 2);
    Invb = pow_mod(b, MOD - 2);
    for (int i = 1; i <= n; i++)
        sp[i] = read();
    f[0] = 1;
    for (int i = 1; i <= n + m; i++)
        f[i] = 1ll * f[i - 1] * i % MOD;
    Inv[n + m] = pow_mod(f[n + m], MOD - 2);
    for (int i = n + m - 1; i >= 0; i--)
        Inv[i] = 1ll * Inv[i + 1] * (i + 1) % MOD;
    powa[0] = powb[0] = powinva[0] = 1;
    for (int i = 1; i <= m + n; i++) powa[i] = 1ll * powa[i - 1] * a % MOD;
    for (int i = 1; i <= m + n; i++) powb[i] = 1ll * powb[i - 1] * b % MOD;
    for (int i = 1; i <= m + n; i++) powinva[i] = 1ll * powinva[i - 1] * Inva % MOD;
    while (q--)
    {
        int x = read(), y = read();
        int ans = 0;
        if (x >= p)
        {
            for (int i = x - p, j = y; i >= 0 && j > 0; i--, j--)
                ans = (ans + 1ll * powa[i] * powb[x - p - i] % MOD * C(x - p, i) % MOD * sp[j] % MOD) % MOD;
        }
        else
        {
            for (int i = 1; i <= y; i++)
                ans = (ans + ((y - i) & 1 ? MOD - 1ll : 1ll) * sp[i] % MOD * powb[y - i] % MOD * C(y - i + p - x - 1, p - x - 1) % MOD * powinva[p - x + y - i] % MOD) % MOD;
        }
        printf ("%d\n", ans);
    }
}