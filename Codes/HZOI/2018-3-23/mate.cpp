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
int MOD, n;
const int MAXN = 1e6 + 5;
long long pow_mod(long long a, int b, int MP)
{
    long long ans = 1;
    // if (b < 0) return 1;
    while (b)
    {
        if (b & 1) ans = ans * a % MP;
        b >>= 1;
        a = a * a % MP;
    }
    return ans;
}
int B, P, K, PhiP;
inline long long rev(long long x)
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
    Num operator / (const Num &c) { return Num(a * rev(c.a) % P, b - c.b); }
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
long long ans[5000], Mp[5000], Phi[5000];
int cnt = 0;
void Solve(int a, int b)
{
    F[0].Set(1);
    cnt++;
    Phi[cnt] = PhiP;
    Mp[cnt] = P;
    for (int i = 1; i <= n; i++) F[i].Set(i);
    for (int i = 1; i <= n; i++) F[i] = F[i - 1] * F[i];
    for (int i = 0; i <= n; i++)
    {
        if (n - 2 * i - a - b < 0) break;
        Num t = F[n] / F[i] / F[i + a] / F[(n - 2 * i - a + b) / 2] / F[(n - 2 * i - a - b) / 2];
        ans[cnt] = (ans[cnt] + t.val()) % P; 
    }
}
void Divide(int x, int a, int b)
{
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0)
        {
            B = i, P = 1, K = 0, PhiP = 1;
            while (x % i == 0)
                x /= i, P *= i, K++, PhiP *= i;
            PhiP /= i; PhiP *= i - 1;
            Solve(a, b);
        }
    if (x != 1) 
    {
        B = x, P = x, K = 1, PhiP = x - 1;
        Solve(a, b);
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
    freopen ("1.out", "w", stdout);
    n = read(), MOD = read();
    int x = read(), y = read();
    if (((x + y) & 1) ^ (n & 1)) return printf ("0\n"), 0;
    Divide(MOD, abs(x), abs(y));
    for (int i = 1; i <= cnt; i++)
        printf ("%lld\n", ans[i]);
    printf ("%lld\n", CRT(Mp, ans, cnt));
    // while (1);
}