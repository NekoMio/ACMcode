#include <cstdio>
#include <cstring>
#include <algorithm>

// #define int long long
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

using namespace std;

const int MAXN = 1e7;

int prime[MAXN + 2], val[MAXN + 2], Num[MAXN + 2], g[MAXN + 2], cnt;
bool isnprime[MAXN + 2];

void Get_fun()
{
    for (int i = 2; i <= MAXN; i++)
    {
        if (!isnprime[i]) 
        {
            prime[++cnt] = i;
            val[i] = i;
            Num[i] = 1;
            g[i] = 1;
        }
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > MAXN) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                val[i * prime[j]] = val[i] * prime[j];
                Num[i * prime[j]] = Num[i] + 1;
                int t = i / val[i];
                if (t == 1) g[i * prime[j]] = 1;
                else
                {
                    g[i * prime[j]] = (Num[i * prime[j]] == Num[t]) ? -g[t] : 0;
                }
                break;
            }
            Num[i * prime[j]] = 1;
            val[i * prime[j]] = prime[j];
            g[prime[j] * i] = (Num[i] == 1 ? -g[i] : 0);
        }
    }
    for (int i = 1; i <= MAXN; i++)
        g[i] += g[i - 1];
}
signed main()
{
    int T = read();
    Get_fun();
    while (T--)
    {
        int n = read(), m = read();
        if (n > m) swap(n, m);
        int nxt = 1;
        long long ans = 0;
        int cnt = 0;
        for (int i = 1; i <= n; i = nxt + 1)
        {
            nxt = min(n / (n / i), m / (m / i));
            ans += ((long long)g[nxt] - g[i - 1]) * (n / i) * (m / i);
        }
        printf ("%lld\n", ans);
    }
}
