#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1e7;


bool isnprime[MAXN + 2];
int prime[MAXN + 2], cnt, mu[MAXN + 2];
int Sum[MAXN + 2], g[MAXN + 2];

void Get_fun()
{
    // mu[1] = 1;
    isnprime[1] = 0;
    for (int i = 2; i <= MAXN; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i, mu[i] = -1, g[i] = 1;
        for (int j = 1; j <= cnt; j++)
        {
            if (prime[j] * i > MAXN) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j]) mu[i * prime[j]] = -mu[i], g[i * prime[j]] = mu[i] - g[i];
            else
            {
                mu[i * prime[j]] = 0;
                g[i * prime[j]] = mu[i];
                break;
            }
        }
    }
    for (int i = 1; i <= MAXN; i++)
        Sum[i] = Sum[i - 1] + g[i];
}

int main()
{
    // freopen("YYnoGCD.in", "r", stdin);
    // freopen("YYnoGCD.out", "w", stdout);
    int T;
    scanf ("%d", &T);
    Get_fun();
    while (T--)
    {
        int n, m;
        scanf ("%d%d", &n, &m);
        if (n > m) swap(n, m);
        long long nxt = 0, ans = 0;
        for (int i = 1; i <= n; i = nxt + 1)
        {
            nxt = min(n / (n / i), m / (m / i));
            ans += ((long long)Sum[nxt] - Sum[i - 1]) * (n / i) * (m / i);
        }
        printf ("%lld\n", ans);
    }
}