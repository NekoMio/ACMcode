#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1e6 * 4;
const int MOD  = 998244353;
const int L = (1 << 18) + 1;
const int LM = (1 << 16) + 1;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int N, Inv, rev[MAXN];
int Sum = 0, n, m;
struct data
{
    int e, f, g, id;
}s[60005];
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
int ans[MAXN], cnt;
void insert(int a, int b, int c, int d, int id)
{
    if (b == 0)
    {
        ans[id] = ((1ll * a * Sum) + (1ll * c * n)) % MOD * pow_mod(d, MOD - 2) % MOD;
        return;
    }
    s[++cnt].f = (1ll * b * c - 1ll * a * d) % MOD;
    b = pow_mod(b, MOD - 2);
    s[cnt].e = 1ll * a * b % MOD, s[cnt].g = 1ll * d * b % MOD;
    b = 1ll * b * b % MOD; s[cnt].f = 1ll * s[cnt].f * b % MOD;
    if (s[cnt].f < 0) s[cnt].f += MOD;
    s[cnt].id = id;
}
void Init(int x)
{
    N = 1;
    while (N < (x << 1)) N <<= 1;
    Inv = pow_mod(N, MOD - 2);
    for (int i = 1; i < N; i++)
        if (i & 1)
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
}
inline int Calc(int x)
{
    N = 1;
    while (N < (x << 1)) N <<= 1;
    return N;
}
void FFt(int *a, int op)
{
    int w, wn, t;
    for (int i = 0; i < N; i++)
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
int tmp[MAXN], x[MAXN];
void Get_Inv(int *a, int *b, int n)
{
    if (n == 1) return b[0] = pow_mod(a[0], MOD - 2), void();
    Get_Inv(a, b, n + 1 >> 1);
    Init(n);
    for (int i = 0; i < n; i++) tmp[i] = a[i];
    for (int i = n; i < N; i++) tmp[i] = 0;
    FFt(tmp, 1), FFt(b, 1);
    for (int i = 0; i < N; i++) 
        b[i] = 1ll * b[i] * ((2 - 1ll * b[i] * tmp[i] % MOD + MOD) % MOD) % MOD;
    FFt(b, -1);
    for (int i = n; i < N; i++) b[i] = 0;
}
int Get_mod(int *a, int ra, int *b, int rb, int *c)
{
    while (ra && !a[ra - 1]) --ra;
    while (rb && !b[rb - 1]) --rb;
    if (ra < rb)
    {
        memcpy (c, a, ra << 2);
        memset (c + ra, 0, (rb - ra) << 2);
        return rb;
    }
    static int tmp1[MAXN], tmp2[MAXN];
    int rc = ra - rb + 1;
    int l = Calc(rc);
    for (int i = 0; i < l; i++) tmp1[i] = 0;
    reverse_copy(b, b + rb, tmp1);
    for (int i = 0; i < l; i++) tmp2[i] = 0; 
    Get_Inv(tmp1, tmp2, rc);
    for (int i = rc; i < l; i++) tmp2[i] = 0;
    reverse_copy(a, a + ra, tmp1);
    for (int i = rc; i < l; i++) tmp1[i] = 0;
    Init(rc), FFt(tmp1, 1), FFt(tmp2, 1);
    for (int i = 0; i < N; i++) tmp1[i] = 1ll * tmp1[i] * tmp2[i] % MOD;
    FFt(tmp1, -1); 
    reverse(tmp1, tmp1 + rc); 
    Init(ra);
    for (int i = 0; i < rb; i++) tmp2[i] = b[i];
    for (int i = rb; i < N; i++) tmp2[i] = 0;
    for (int i = rc; i < N; i++) tmp1[i] = 0;
    FFt(tmp1, 1), FFt(tmp2, 1);
    for (int i = 0; i < N; i++) tmp1[i] = 1ll * tmp1[i] * tmp2[i] % MOD;
    FFt(tmp1, -1);
    for (int i = 0; i < rb; i++) c[i] = (a[i] - tmp1[i] + MOD) % MOD;
    for (int i = rb; i < N; i++) c[i] = 0;
    while (rb && !c[rb - 1]) --rb;
    return rb;
}
int Solve0(int *a, int l, int r)
{
    int ra = r - l + 2;
    if (ra <= 256)
    {
        memset(a, 0, ra << 2), a[0] = 1;
        for (int i = l; i <= r; i++)
            for (int v = x[i], j = i - l; j != -1; j--)
            {
                a[j + 1] = (a[j + 1] + a[j]) % MOD;
                a[j] = 1ll * a[j] * v % MOD;
            }
        return ra;
    }
    int mid = l + r >> 1;
    int *f1 = a, r1 = Solve0(f1, l, mid);
    int *f2 = a + r1, r2 = Solve0(f2, mid + 1, r);
    N = 1;
    while (N < ra) N <<= 1;
    Inv = pow_mod(N, MOD - 2);
    for (int i = 1; i < N; i++)
        if (i & 1)
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
    static int tmp1[L], tmp2[L];
    memcpy(tmp1, f1, r1 << 2), memset (tmp1 + r1, 0, (N - r1) << 2), FFt(tmp1, 1);
    memcpy(tmp2, f2, r2 << 2), memset (tmp2 + r2, 0, (N - r2) << 2), FFt(tmp2, 1);
    for (int i = 0; i < N; i++) a[i] = 1ll * tmp1[i] * tmp2[i] % MOD;
    FFt(a, -1);
    return ra;
}
int *p[L];
int sta[MAXN];
int mem[LM << 4], *head = mem;
inline int Solve1(int id, int l, int r)
{
    int ra = r - l + 2;
    if (ra <= 256)
    {
        int *f = p[id] = head; head += ra;
        memset (f, 0, ra << 2), 0[f] = 1;
        for (int i = l; i <= r; i++)
            for (int v = (MOD - sta[i]) % MOD, j = i - l; j != -1; j--)
                f[j + 1] = (f[j + 1] + f[j]) % MOD, f[j] = 1ll * f[j] * v % MOD;
        return ra;
    }
    int mid = l + r >> 1;
    int r1 = Solve1(id << 1, l, mid), *f1 = p[id << 1];
    int r2 = Solve1(id << 1 | 1, mid + 1, r), *f2 = p[id << 1 | 1];
    N = 1;
    while (N < ra) N <<= 1;
    Inv = pow_mod(N, MOD - 2);
    for (int i = 1; i < N; i++)
        if (i & 1)
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
    static int tmp1[LM], tmp2[LM];
    memcpy(tmp1, f1, r1 << 2), memset (tmp1 + r1, 0, (N - r1) << 2), FFt(tmp1, 1);
    memcpy(tmp2, f2, r2 << 2), memset (tmp2 + r2, 0, (N - r2) << 2), FFt(tmp2, 1);
    int *f = p[id] = head; head += ra;
    for (int i = 0; i < N; i++) f[i] = 1ll * tmp1[i] * tmp2[i] % MOD;
    FFt(f, -1);
    return ra; 
}
int val0[LM], val[LM];
void Solve2(int id, int *a, int *b, int l, int r, int deg)
{
    int ra = r - l + 2;
    if (deg <= 256)
    {
        int F, G;
        for (int i = l; i <= r; i++)
        {
            F = G = 0;
            int u = sta[i], v = 1;
            for (int j = 0; j <= deg; j++)
            {
                F = (F + 1ll * v * a[j]) % MOD;
                G = (G + 1ll * v * b[j]) % MOD;
                v = 1ll * v * u % MOD;
            }
            val0[i] = F, val[i] = G;
        }
        return;
    }
    int mid = l + r >> 1;
    int r1 = Get_mod(a, deg, p[id], ra, a + deg); a += deg;
    int r2 = Get_mod(b, deg, p[id], ra, b + deg); b += deg;
    ra = min(r1, r2);
    Solve2(id << 1, a, b, l, mid, ra), Solve2(id << 1 | 1, a, b, mid + 1, r, ra);
}
int g[MAXN], h[MAXN];
int main()
{
    n = read(), m = read();
    Sum = 0;
    for (int i = 1; i <= n; i++)
        x[i] = read() % MOD, Sum = (Sum + x[i]) % MOD;
    int A = 1, B = 0, C = 0, D = 1;
    for (int i = 1; i <= m; i++)
    {
        if (read() == 1)
        {
            int v = read() % MOD;
            A = (A + 1ll * v * B % MOD) % MOD;
            C = (C + 1ll * v * D % MOD) % MOD;
            insert(A, B, C, D, i);
        }
        else
        {
            swap(A, B);
            swap(C, D);
            insert(A, B, C, D, i);
        }
    }
    if (cnt)
    {
        for (int i = 1; i <= cnt; i++) sta[i] = s[i].g;
        sort(sta + 1, sta + cnt + 1);
        int lenth = unique(sta + 1, sta + cnt + 1) - sta - 1;
        for (int i = 1; i <= cnt; i++)
            s[i].g = lower_bound(sta + 1, sta + lenth + 1, s[i].g) - sta;
        Solve0(g, 1, n);
        for (int i = 1; i <= n; i++) h[i - 1] = 1ll * g[i] * i % MOD;
        Solve1(1, 1, lenth);
        Solve2(1, g, h, 1, lenth, n + 1);
        for (int i = 1; i <= cnt; i++)
            ans[s[i].id] = (1ll * s[i].e * n % MOD + 1ll * s[i].f * val[s[i].g] % MOD * pow_mod(val0[s[i].g], MOD - 2) % MOD) % MOD;
    }
    for (int i = 1; i <= m; i++)
        printf ("%d\n", ans[i]);
    // while (1);
}