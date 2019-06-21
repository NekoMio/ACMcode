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
const int MOD = 1004535809;
const int MAXN = 1 << 18 + 1;
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
long long Inv;
int N;
int rev[MAXN];
void FFt(long long *a, int op)
{
    long long w, wn, t;
    for (int i = 1; i < N; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int k = 2; k <= N; k <<= 1)
    {
        wn = pow_mod(3, op == 1 ? (MOD - 1) / k : MOD - 1 - (MOD - 1) / k);
        for (int j = 0; j < N; j += k)
        {
            w = 1;
            for (int i = 0; i < (k >> 1); i++, w = w * wn % MOD)
            {
                t = a[i + j + (k >> 1)] * w % MOD;
                a[i + j + (k >> 1)] = (a[i + j] - t + MOD) % MOD;
                a[i + j] = (a[i + j] + t) % MOD;
            }
        }
    }
    if (op == -1)
        for (int i = 0; i < N; i++)
            a[i] = a[i] * Inv % MOD;
}
long long tmp[MAXN];
void Get_Inv(int dep, long long *a, long long *b)
{
    if (dep == 1)
        return b[0] = pow_mod(a[0], MOD - 2), void();
    Get_Inv((dep + 1) >> 1, a, b);
    N = 1;
    while (N < (dep << 1))
        N <<= 1;
    Inv = pow_mod(N, MOD - 2);
    for (int i = 1; i < N; i++)
        if (i & 1)
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
    copy(a, a + dep, tmp);
    fill(tmp + dep, tmp + N, 0);
    FFt(tmp, 1);
    FFt(b, 1);
    for (int i = 0; i < N; i++)
        b[i] = b[i] * ((2 - b[i] * tmp[i] % MOD + MOD) % MOD) % MOD;
    FFt(b, -1);
    fill(b + dep, b + N, 0);
}
long long F_Inv[MAXN];
long long F[MAXN];
long long C[MAXN], G[MAXN], G_Inv[MAXN];
int main()
{
    int n = read();
    F[0] = 1;
    for (int i = 1; i <= n; i++)
        F[i] = F[i - 1] * i % MOD;
    F_Inv[n] = pow_mod(F[n], MOD - 2);
    for (int i = n - 1; i >= 0; i--) F_Inv[i] = F_Inv[i + 1] * (i + 1) % MOD;
    for (int i = 0; i <= n; i++)
        G[i] = (i < 2) ? (1) : pow_mod(2, 1ll * i * (i - 1) / 2 % (MOD - 1)) * F_Inv[i] % MOD;
    for (int i = 0; i < n; i++) C[i] = (i + 1) * G[i + 1] % MOD;
    Get_Inv(n, G, G_Inv);
    N = 1;
    while (N < n << 1)
        N <<= 1;
    Inv = pow_mod(N, MOD - 2);
    for (int i = 1; i < N; i++)
        if (i & 1)
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
    FFt(G_Inv, 1), FFt(C, 1);
    for (int i = 0; i < N; i++) C[i] = C[i] * G_Inv[i] % MOD;
    FFt(C, -1);
    printf ("%d\n", C[n - 1] * F[n - 1] % MOD);
    // while (1);
}