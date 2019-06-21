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
const int MAXN = 2e6;
const long long MOD = 998244353;
long long A[MAXN], B[MAXN], N;
long long Inv;
int rev[MAXN];
long long pow_mod(long long a, long long b, long long P)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % P;
        b >>= 1;
        a = a * a % P;
    }
    return ans;
}
void FFt(long long *a, int op)
{
    long long w, wn, t;
    for (int i = 0; i < N; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int k = 2; k <= N; k <<= 1)
    {
        wn = pow_mod(3, op == 1 ? (MOD - 1) / k : MOD - 1 - (MOD - 1) / k, MOD);
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
void FFt(const int *a, const int *b, int *res, int n)
{
    N = 1;
    while (N < n)
        N <<= 1;
    Inv = pow_mod(N, MOD - 2, MOD);
    for (int i = 0; i < N; i++)
        if (i & 1)
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
    for (int i = 0; i < N; i++)
        A[i] = a[i], B[i] = b[i];
    FFt(A, 1), FFt(B, 1);
    for (int i = 0; i < N; i++)
        A[i] = A[i] * B[i] % MOD;
    FFt(A, -1);
    for (int i = 0; i < N; i++)
        res[i] = A[i];
}
int a[MAXN], b[MAXN];
int main()
{
    int n = read();
    n--;
    for (int i = 0; i <= n; i++)
    {
        a[i] = read();
        b[n - i] = read();
    }
    FFt(a, b, a, n + n + 1);
    for (int i = n; i <= 2 * n; i++)
        printf ("%d\n", a[i]);
    // while (1);
}