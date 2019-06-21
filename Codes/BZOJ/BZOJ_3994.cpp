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
const int MAXN = 50000;
int prime[MAXN + 2], mu[MAXN + 2], Sum_mu[MAXN + 2], d[MAXN + 2], e[MAXN + 2], cnt;
long long Sum_d[MAXN + 2];
bool isnprime[MAXN + 2];
void Get_d()
{
    mu[1] = 1, d[1] = 1, isnprime[1] = 1;
    for (int i = 2; i <= MAXN; i++)
    {
        if (!isnprime[i])
        {
            prime[++cnt] = i;
            e[i] = 1;
            d[i] = 2;
            mu[i] = -1;
        }
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > MAXN) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                mu[i * prime[j]] = 0;
                d[i * prime[j]] = d[i] / (e[i] + 1) * (e[i] + 2);
                e[i * prime[j]] = e[i] + 1; 
                break;
            }
            mu[i * prime[j]] = -mu[i];
            d[i * prime[j]] = d[i] * 2;
            e[i * prime[j]] = 1;
        }
    }
    for (int i = 1; i <= MAXN; i++)
    {
        Sum_mu[i] = Sum_mu[i - 1] + mu[i];
        Sum_d[i] = Sum_d[i - 1] + d[i];
    }
}
int main()
{
    int t = read();
    Get_d();
    while (t--)
    {
        int n = read(), m = read();
        if (n > m) swap(n, m);
        int nxt = 1;
        long long ans = 0;
        for (int i = 1; i <= n; i = nxt + 1)
        {
            nxt = min(n / (n / i), m / (m / i));
            ans += 1ll * (Sum_mu[nxt] - Sum_mu[i - 1]) * Sum_d[n / i] * Sum_d[m / i];
        }
        printf ("%lld\n", ans);
    }
    // while (1);
}