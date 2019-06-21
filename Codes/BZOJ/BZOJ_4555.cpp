#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 998244353;
const int MAXN = 300005;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
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
int Inv, N;
int rev[MAXN];
void FFt(int *a, int op)
{
    int wn, w, t;
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
int F[MAXN];
int a[MAXN], b[MAXN];
int main()
{
    int n = read();
    F[0] = 1;
    for (int i = 1; i <= n; i++)
        F[i] = 1ll * F[i - 1] * i % MOD;
    int m = 2 * n;
    N = 1;
    while (N <= m) 
        N <<= 1;
    for (int i = 1; i < N; i++)
        if (i & 1)
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
    Inv = pow_mod(N, MOD - 2);
    for (int i = 0; i <= n; i++)
    {
        a[i] = pow_mod(F[i], MOD - 2);
        if (i & 1) a[i] = MOD - a[i];
        b[i] = (1 - pow_mod(i, n + 1) + MOD) % MOD;
        b[i] = 1ll * b[i] * pow_mod((1 - i + MOD) % MOD, MOD - 2) % MOD;
        b[i] = 1ll * b[i] * ((i & 1) ? (MOD - a[i]) : a[i]) % MOD;
    }
    b[1] = n + 1;
    FFt(a, 1), FFt(b, 1);
    for (int i = 0; i <= N; i++) a[i] = 1ll * a[i] * b[i] % MOD;
    FFt(a, -1);
    int ans = 0;
    for (int i = 0; i <= n; i++)
    {
        int now = 1ll * F[i] * pow_mod(2, i) % MOD * a[i] % MOD;
        ans = (ans + now) % MOD;
    }
    printf("%d\n", ans);
}