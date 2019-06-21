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
const int MAXN = 200005 * 4;
int F[MAXN], FInv[MAXN];
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
int N, Inv;
int rev[MAXN];
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
        for (int i = 1; i < N; i++)
            a[i] = 1ll * a[i] * Inv % MOD;
}
int A[MAXN], B[MAXN];
int main()
{
    int n = read(), k = read(); 
    F[0] = 1;
    for (int i = 1; i <= k; i++)
        F[i] = 1ll * F[i - 1] * i % MOD;
    FInv[k] = pow_mod(F[k], MOD - 2);
    for (int i = k - 1; i >= 0; i--) FInv[i] = 1ll * FInv[i + 1] * (i + 1) % MOD;
    for (int i = 0; i <= k; i++)
        A[i] = (((i & 1) ? (-1) : (1)) * FInv[i] + MOD) % MOD;
    for (int i = 0; i <= k; i++)
        B[i] = pow_mod(i, k) * FInv[i] % MOD;
    N = 1;
    while (N <= (k << 1))
        N <<= 1;
    Inv = pow_mod(N, MOD - 2);
    for (int i = 1; i < N; i++)
        if (i & 1)
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
    FFt(A, 1), FFt(B, 1);
    for (int i = 0; i < N; i++)
        A[i] = 1ll * A[i] * B[i] % MOD;
    FFt(A, -1);
    int ans = 0;
    int Sum = 1;
    for (int i = 0; i <= k; i++)
    {
        ans = (ans + 1ll * A[i] * Sum % MOD * pow_mod(2, n - i - 1) % MOD) % MOD;
        Sum = 1ll * Sum * (n - i - 1) % MOD;
    }
    ans = 1ll * ans * n % MOD;
    ans = 1ll * ans * pow_mod(2, (1ll * (n - 2) * (n - 1) / 2) % (MOD - 1)) % MOD;
    printf ("%d\n", ans);
}