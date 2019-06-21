#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline long long read()
{
    long long x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MOD = 258280327;
const int Inv2= 129140164;
int Inv9;
long long pow_mod(long long a, long long b)
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
const int MAXN = 7e6 + 5;
int prime[MAXN + 2], mu[MAXN + 2], S[MAXN + 2], cnt;
bool isnprime[MAXN + 2];
void Get_mu()
{
    isnprime[1] = 1;
    mu[1] = 1;
    for (int i = 2; i <= MAXN; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > MAXN) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                mu[i * prime[j]] = 0;
                break;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 1; i <= MAXN; i++)
        S[i] = (S[i - 1] + i * mu[i] % MOD + MOD) % MOD;
}
struct Hash_Table
{
    struct data
    {
        long long x, v;
        int next;
    }v[MAXN];
    int first[2332334], p;
    Hash_Table()
    {
        memset (first, -1, sizeof (first));
        p = 0;
    }
    long long &operator[] (const long long &x)
    {
        int H = x % 2332333;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].x == x)
                return v[i].v;
        v[p].x = x;
        v[p].next = first[H];
        first[H] = p++;
        return v[p - 1].v = 0;
    }
    bool count(const long long &x)
    {
        int H = x % 2332333;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].x == x)
                return 1;
        return 0;
    }
}Hash;
long long Sum(long long x)
{
    x %= MOD;
    return x * (x + 1) % MOD * Inv2 % MOD;
}
long long Calc(long long n)
{
    long long t = pow_mod(10, n);
    return (n % MOD * t % MOD - (t - 1) * Inv9 % MOD + MOD) % MOD * 10 % MOD * Inv9 % MOD;
}
long long g(long long x)
{
    if (x <= MAXN) return S[x];
    if (Hash.count(x)) return Hash[x];
    long long ans = 1;
    long long nxt = 0;
    for (long long i = 2; i <= x; i = nxt + 1)
    {
        nxt = x / (x / i);
        ans = (ans - (Sum(nxt) - Sum(i - 1) + MOD) % MOD * g(x / i) % MOD + MOD) % MOD;
    }
    return Hash[x] = ans;
}
int main()
{
    // freopen ("1.out", "w", stdout);
    long long n = read();
    Get_mu();
    Inv9 = pow_mod(9, MOD - 2);
    long long ans = 0;
    long long nxt = 0;
    // printf ("%lld\n", Calc(100000));
    for (long long i = 1; i <= n; i = nxt + 1)
    {
        nxt = n / (n / i);
        ans = (ans + ((g(nxt) - g(i - 1) + MOD) % MOD) * Calc(n / i) % MOD) % MOD;
        // printf ("%lld\n", ans);
    }
    printf ("%lld\n", ans);
    // while (1);
}