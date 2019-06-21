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
const int MAXN = 300005;
long long a[MAXN], b[MAXN], c[MAXN], g[MAXN];
int Sum[MAXN], n, m;
long long B, P, PhiP, K;
long long pow_mod(long long a, int b, long long MP)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % MP;
        b >>= 1;
        a = a * a % MP;
    }
    return ans;
}
long long Inv(long long x)
{
    return pow_mod(x, PhiP - 1, P);
}
struct Num
{
    long long a, b;
    Num(){a = 0, b = 0; }
    Num(int _a)
    {
        a = _a;
        while (a % B == 0)
            a /= B, b++;
    }
    Num(long long _a, long long _b): a(_a), b(_b) {}
    Num operator * (const Num &c) { return Num(a * c.a % P, b + c.b); }
    Num operator / (const Num &c) { return Num(a * Inv(c.a) % P, b - c.b); }
    long long val()
    {
        if (!a || b >= K) return 0;
        long long x = a, k = b, c = B;
        while (k)
        {
            if (k & 1) x = x * c % P;
            k >>= 1;
            c = c * c % P;
        }
        return x;
    }
    void Set(int x)
    {
        a = x, b = 0;
        while (a % B == 0)
            a /= B, b++;
    }
}F[MAXN];
#define lowbit(_) ((_) & (-_))
void A(int x, int c)
{
    for (int i = x; i <= n; i += lowbit(i))
        Sum[i] += c;
}
int Q(int x)
{
    int ans = 0;
    for (int i = x; i >= 1; i -= lowbit(i))
        ans += Sum[i];
    return ans;
}
int cnt;
long long ans[5000], Mp[5000], Phi[5000];
void Solve()
{
    cnt++;
    Mp[cnt] = P, Phi[cnt] = PhiP;
    F[0].Set(1);
    for (int i = 1; i <= n; i++) F[i].Set(i);
    for (int i = 1; i <= n; i++) F[i] = F[i] * F[i - 1];
    for (int i = 1; i <= n; i++) c[i] = 0;
    for (int i = 1; i <= n; i++) c[a[i]]++;
    Num t(1, 0), tmp;
    for (int i = 1; i <= n; i++) t = t * F[c[i]];
    for (int i = 1; i <= n; i++)
    {
        if (g[i]) tmp.Set(g[i]), ans[cnt] = (ans[cnt] + (tmp * F[n - i] / t).val()) % P;
        t = t / F[c[a[i]]] * F[c[a[i]] - 1];
        c[a[i]]--;
    }
}
void Divide(int x)
{
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0)
        {
            B = i, P = 1, PhiP = 1, K = 0;
            while (x % i == 0)
                P *= i, PhiP *= i, K++, x /= i;
            PhiP /= i, PhiP *= i - 1;
            Solve();
        }
    if (x != 1)
    {
        B = x, P = x, PhiP = x - 1, K = 1;
        Solve();
    }
}
long long CRT(long long *a, long long *b, int n)
{
    long long N = 1, Ni, now, ans = 0;
    for (int i = 1; i <= n; i++) N *= a[i];
    for (int i = 1; i <= n; i++)
    {
        Ni = N / a[i];
        now = pow_mod(Ni, Phi[i] - 1, a[i]);
        ans = (ans + (b[i] * now % N) * Ni % N) % N;    
    }
    return ans;
}
int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
        b[i] = a[i] = read();
    sort(b + 1, b + n + 1);
    int cnt = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(b + 1, b + cnt + 1, a[i]) - b;
    for (int i = 1; i <= n; i++)
        c[a[i]]++;
    for (int i = 1; i <= n; i++) A(i, c[i]);
    for (int i = 1; i <= n; i++)
        g[i] = Q(a[i] - 1), A(a[i], -1);
    Divide(m);
    printf ("%lld\n", (CRT(Mp, ans, ::cnt) + 1) % m);
}
