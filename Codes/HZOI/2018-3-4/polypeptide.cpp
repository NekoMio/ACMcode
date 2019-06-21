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
const int MOD = 1005060097;
const int MAXN = 4e5 + 5;
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
void Init(int n)
{
    N = 1;
    while (N < (n << 1)) N <<= 1;
    Inv = pow_mod(N, MOD - 2) % MOD;
    for (int i = 1; i <= N; i++)
        if (i & 1)
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
}
void FFt(int *a, int op)
{
    int w, wn, t;
    for (int i = 1; i <= N; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int k = 2; k <= N; k <<= 1)
    {
        wn = pow_mod(5, op == 1 ? (MOD - 1) / k : MOD - 1 - (MOD - 1) / k);
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
int tmp[MAXN];
void Get_Inv(int *a, int *b, int n)
{
    if (n == 1) return b[0] = pow_mod(a[0], MOD - 2), void();
    Get_Inv(a, b, (n + 1) >> 1);
    Init(n);
    for (int i = 0; i < n; i++) tmp[i] = a[i];
    for (int i = n; i < N; i++) tmp[i] = 0;
    FFt(tmp, 1), FFt(b, 1);
    for (int i = 0; i < N; i++)
        b[i] = 1ll * b[i] * (2 - 1ll * tmp[i] * b[i] % MOD + MOD) % MOD;
    FFt(b, -1);
    for (int i = n; i < N; i++) b[i] = 0;
}
int a[MAXN], b[MAXN];
int main()
{
    freopen ("polypeptide.in", "r", stdin);
    freopen ("polypeptide.out", "w", stdout);
    int n = read(), m = read();
    for (int i = 1; i <= m; i++)
        a[read()]--;
    for (int i = 1; i <= n; i++)
        if (a[i] < 0) 
            a[i] += MOD;
    a[0] = 1;
    Get_Inv(a, b, n + 1);
    printf ("%d\n", b[n]);
}