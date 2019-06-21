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
const int MAXN = 200005 * 4;
const int MOD = 998244353;
int Inv2 = MOD + 1 >> 1;
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
char s[MAXN];
int F[MAXN], FInv[MAXN];
int g[MAXN], f[MAXN], h[MAXN];
int N, Inv;
int rev[MAXN];
int tmp1[MAXN], tmp2[MAXN];
int Init(int x)
{
    N = 1;
    while (N < (x << 1)) N <<= 1;
    for (int i = 1; i < N; i++)
        if (i & 1)
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
    Inv = pow_mod(N, MOD - 2);
}
void FFt(int *a, int op)
{
    int w, wn, t;
    for (int i = 1; i < N; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int k = 2; k <= N; k <<= 1)
    {
        wn = pow_mod(3, op == 1 ? (MOD - 1) / k : MOD - 1 - (MOD - 1) / k);
        for (int j = 0; j < N; j += k)
        {
            w = 1;
            for (int i = 0; i < (k >> 1); i++, w = 1ll * w * wn % MOD)
            {
                t = 1ll * a[i + j + (k >> 1)] * w % MOD;
                a[i + j + (k >> 1)] = (a[i + j] - t + MOD) % MOD;
                a[i + j] = (a[i + j] + t) % MOD;
            }
        }
    }
    if (op == -1)
        for (int i = 0; i < N; i++)
            a[i] = 1ll * a[i] * Inv % MOD;
}
void Get_Inv(int *a, int *b, int n)
{
    if (n == 1) return b[0] = pow_mod(a[0], MOD - 2), void();
    Get_Inv(a, b, n + 1 >> 1);
    Init(n);
    for (int i = 0; i < n; i++) tmp1[i] = a[i];
    for (int i = n; i < N; i++) tmp1[i] = 0;
    FFt(tmp1, 1), FFt(b, 1);
    for (int i = 0; i < N; i++) 
        b[i] = 1ll * b[i] * ((2 - 1ll * b[i] * tmp1[i] % MOD + MOD) % MOD) % MOD;
    FFt(b, -1);
    for (int i = n; i < N; i++) b[i] = 0;
}
void Sqrt(int *a, int *b, int n)
{
    if (n == 1) return b[0] = 1, void();
    Sqrt(a, b, n + 1 >> 1);
    memset (tmp2, 0, n << 3); Get_Inv(b, tmp2, n);
    for (int i = 0; i < n; i++) tmp1[i] = a[i];
    for (int i = n; i < N; i++) tmp1[i] = 0;
    FFt(tmp1, 1), FFt(b, 1), FFt(tmp2, 1);
    for (int i = 0; i <= N; i++)
        b[i] = 1ll * (tmp1[i] + 1ll * b[i] * b[i] % MOD) % MOD * tmp2[i] % MOD * Inv2 % MOD;
    FFt(b, -1);
    for (int i = n; i < N; i++) b[i] = 0;
}
int Ans[MAXN];
int main()
{
    int m = read(), n = read();
    F[0] = 1;
    // n = n * 2;
    for (int i = 1; i <= n; i++) F[i] = 1ll * F[i - 1] * i % MOD;
    FInv[n] = pow_mod(F[n], MOD - 2);
    for (int i = n - 1; i >= 0; i--) FInv[i] = 1ll * FInv[i + 1] * (i + 1) % MOD;
    for (int i = 1; i <= m; i++)
    {
        int x = read();
        if (x <= n) g[x] = MOD - 4ll % MOD;
    }
    g[0] = 1;
    Sqrt(g, f, n + 1);
    f[0] = 2;
    Get_Inv(f, h, n + 1);
    for (int i = 1; i <= n; i++)
        printf ("%d\n", 2ll * h[i] % MOD);
}