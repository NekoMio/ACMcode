#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MOD = 1e8 + 9;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 10000000;
int prime[MAXN + 2], cnt;
long long G[MAXN + 2];
bool isnprime[MAXN + 2];
void Get_mu()
{
    isnprime[1] = 1;
    G[1] = 1;
    for (int i = 2; i <= MAXN; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i, G[i] =  ((i - 1ll * i * i % MOD) % MOD + MOD) % MOD;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > MAXN) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                G[i * prime[j]] = G[i] * prime[j] % MOD;
                break;
            }
            G[i * prime[j]] = G[i] * G[prime[j]] % MOD;
        }
    }
    for (int i = 1; i <= MAXN; i++)
        G[i] = (G[i - 1] + G[i]) % MOD;
}
long long Sum(int x)
{
    // if (x == 1) return 1;
    return 1ll * x * (x + 1) / 2;
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
        long long ans = 0;
        for (int i = 1; i <= n; i = nxt + 1)
        {
            nxt = min(n / (n / i), m / (m / i));
            ans = (ans + 1ll * ((G[nxt] - G[i - 1]) % MOD + MOD) % MOD * (Sum(n / i) % MOD * (Sum(m / i) % MOD) % MOD) % MOD + MOD) % MOD;
        }
        printf ("%lld\n", ans);
    }
    // while (1);
}