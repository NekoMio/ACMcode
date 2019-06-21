#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1e6;
const int MOD = 1e9 + 7;
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
int mu[MAXN + 2], prime[MAXN + 2], Sum[MAXN + 2], cnt;
long long f[MAXN + 2];
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
        Sum[i] = Sum[i - 1] + mu[i];
    f[0] = 1;
    f[1] = 1, f[2] = 1;
    for (int i = 3; i <= MAXN; i++)
        f[i] = (f[i - 1] + f[i - 2]) % MOD;
    for (int i = 2; i <= MAXN; i++)
        f[i] = f[i] * f[i - 1] % MOD;
}
long long G(int n, int m)
{
    if (n > m) swap(n, m);
    int nxt = 1;
    long long ans = 0;
    for (int i = 1; i <= n; i = nxt + 1)
    {
        nxt = min(n / (n / i), m / (m / i));
        ans += 1ll * (Sum[nxt] - Sum[i - 1]) * (n / i) * (m / i);
    }
    return ans;
}
int main()
{
    int t = read();
    Get_mu();
    while (t--)
    {
        int n = read(), m = read();
        if (n > m) swap(n, m);
        int nxt = 1;
        long long ans = 1;
        for (int i = 1; i <= n; i = nxt + 1)
        {
            nxt = min(n / (n / i), m / (m / i));
            ans = ans * pow_mod(f[nxt] * pow_mod(f[i - 1], MOD - 2) % MOD, G(n / i, m / i)) % MOD;
        }
        printf ("%lld\n", ans);
    }
}