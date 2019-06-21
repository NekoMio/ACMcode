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
void Solve(int l, int r)
{
    if (l == r) return;
    int mid = l + r >> 1;
    Solve(l, mid);
    Init(r - l + 1);
    memset (tmp1, 0, N << 2);
    memset (tmp2, 0, N << 2);
    for (int i = l; i <= mid; i++) tmp1[i - l] = f[i];
    for (int i = 0; i <= r - l; i++)
        if (i < l) tmp2[i] = 2 * f[i] % MOD;
        else if (i <= mid) tmp2[i] = f[i];
    FFt(tmp1, 1), FFt(tmp2, 1);
    for (int i = 0; i < N; i++) tmp1[i] = 1ll * tmp1[i] * tmp2[i] % MOD;
    FFt(tmp1, -1);
    for (int i = mid + 1; i <= r; i++) h[i] = (h[i] + tmp1[i - l]) % MOD;
    memset (tmp1, 0, N << 2);
    memset (tmp2, 0, N << 2);
    for (int i = l; i <= mid; i++) tmp1[i - l] = h[i];
    for (int i = 0; i <= r - l; i++) tmp2[i] = g[i];
    FFt(tmp1, 1), FFt(tmp2, 1);
    for (int i = 0; i < N; i++) tmp1[i] = 1ll * tmp1[i] * tmp2[i] % MOD;
    FFt(tmp1, -1);
    for (int i = mid + 1; i <= r; i++) f[i] = (f[i] + 1ll * tmp1[i - l - 1] * F[i - 1] % MOD * FInv[i] % MOD) % MOD;
    Solve(mid + 1, r);
}
int main()
{
    int n = read();
    scanf ("%s", s);
    for (int i = 0; i < n; i++) s[i] -= '0';
    F[0] = 1;
    for (int i = 1; i <= n; i++) F[i] = 1ll * F[i - 1] * i % MOD;
    FInv[n] = pow_mod(F[n], MOD - 2);
    for (int i = n - 1; i >= 0; i--) FInv[i] = 1ll * FInv[i + 1] * (i + 1) % MOD;
    for (int i = 0; i < n; i++) g[i] = 1ll * s[i] * FInv[i] * FInv[2] % MOD;
    f[1] = 1;
    Solve(1, n);
    for (int i = 1; i <= n; i++)
        printf ("%d\n", 1ll * f[i] * F[i] % MOD);
}
