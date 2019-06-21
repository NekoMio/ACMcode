#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1004535809;
const int MAXN = 20000;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
long long pow_mod(long long a, int b, int P)
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
int N, Inv;
int rev[MAXN];
void FFt(int *a, int op)
{
    int wn, w, t;
    for (int i = 1; i < N; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int k = 2; k <= N; k <<= 1)
    {
        wn = pow_mod(3, op == 1 ? (MOD - 1) / k : MOD - 1 - (MOD - 1) / k, MOD);
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
int Log[MAXN];
int a[MAXN], b[MAXN];
int TMP[100005];
int Get_G(int p)
{
    int phi = p - 1;
    int num = 0;
    for (int i = 2; i * i <= phi; i++)
    {
        if (phi % i == 0)
            TMP[++num] = i;
        if (i * i != phi) TMP[++num] = phi / i;
    }
    for (int g = 2; g < p; g++)
    {
        bool flag = 0;
        for (int i = 1; i <= num; i++)
            if (pow_mod(g, TMP[i], p) == 1)
                flag = 1;
        if (!flag) return g;
    }
}
int main()
{
    int k = read(), n = read(), x = read(), m = read();
    int now = 1;
    int G = Get_G(n);
    for (int i = 0; i < n - 1; i++)
    {
        Log[now] = i;
        now = now * G % n;
    }
    for (int i = 1; i <= m; i++)
    {
        int s = read();
        if (s) a[Log[s]]++;
    }
    n--;
    N = 1;
    while (N < (n << 1)) N <<= 1;
    for (int i = 1; i < N; i++)
        if (i & 1)
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
    Inv = pow_mod(N, MOD - 2, MOD);
    b[0] = 1;
    while (k)
    {
        if (k & 1)
        {
            FFt(a, 1);
            FFt(b, 1);
            for (int i = 0; i < N; i++)
                b[i] = 1ll * b[i] * a[i] % MOD;
            FFt(b, -1);
            FFt(a, -1);
            for (int i = n; i <= N; i++)
            {
                b[i - n] = (b[i - n] + b[i]) % MOD;
                b[i] = 0;
            }
        }
        k >>= 1;
        FFt(a, 1);
        for (int i = 0; i < N; i++)
            a[i] = 1ll * a[i] * a[i] % MOD;
        FFt(a, -1);
        for (int i = n; i <= N; i++)
        {
            a[i - n] = (a[i - n] + a[i]) % MOD;
            a[i] = 0;
        }
    }
    printf ("%d\n", b[Log[x]]);
    // while (1);
}