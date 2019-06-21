#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1e5;
int prime[MAXN + 2], mu[MAXN + 2], phi[MAXN + 2], cnt;
bool isnprime[MAXN + 2];
int Sum[MAXN + 2];
map<int, int> mp[MAXN + 2];
const int MOD = 998244353;
inline int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}
void Get_phi()
{
    mu[1] = 1;
    phi[1] = 1;
    for (int i = 2; i <= MAXN; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i, mu[i] = -1, phi[i] = i - 1;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > MAXN) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                mu[i * prime[j]] = 0;
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            mu[i * prime[j]] = -mu[i];
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
    for (int i = 1; i <= MAXN; i++)
        Sum[i] = (Sum[i - 1] + phi[i] * mu[i] % MOD + MOD) % MOD;
}
int H(int n, int m)
{
    if (n == 1) return Sum[m];
    if (mp[n].count(m)) return mp[n][m];
    int ans = 0;
    for (int i = 1; i <= m; i++)
        ans = (ans + 1ll * mu[i * n] * phi[i * n] % MOD + MOD) % MOD;
    return mp[n][m] = ans;
}
int S(int n, int m)
{
    if (n == 1) return Sum[m];
    if (m == 1) return phi[n];
    int ans = 0;
    for (int i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            ans = (ans + 1ll * phi[n / i] * H(i, m / i) % MOD + MOD) % MOD;
            if (i * i != n) 
                ans = (ans + 1ll * phi[i] * H(n / i, m / (n / i)) % MOD + MOD) % MOD;
        }
    }
    return ans;
}
int main()
{
    Get_phi();
    int n = read(), m = read();
    register int ans = 0;
    register int g = 0;
    register int i, j;
    if (n > m) swap(n, m);
    for (i = 1; i <= n; i++)
        if (mu[i])
            ans = (ans + 1ll * mu[i] * S(i, m) % MOD + MOD) % MOD;
    printf ("%d\n", ans);
}