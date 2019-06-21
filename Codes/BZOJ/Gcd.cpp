#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 10000000;
int mu[N + 5], prime[N + 5], g[N + 5];
long long sum[N + 5], cnt;
bool isnprime[N + 5];
void get_g()
{
    mu[1] = 1;
    for (int i = 2; i <= N; i++)
    {
        if (!isnprime[i])
        {
            prime[++cnt] = i;
            mu[i] = -1;
            g[i] = 1;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= N; j++)
        {
            isnprime[i * prime[j]] = 1;
            if (i % prime[j])
                mu[i * prime[j]] = -mu[i], g[i * prime[j]] = mu[i] - g[i];
            else
            {
                mu[i * prime[j]] = 0;
                g[i * prime[j]] = mu[i];
                break;
            }
        }
    }
    for (int i = 1; i <= N; i++)
    {
        sum[i] = sum[i - 1] + g[i];
    }
}
int main()
{
    freopen("YYnoGCD.in","r",stdin);
    freopen("YYnoGCD.out","w",stdout);
    get_g();
    int n, m;
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        if (n > m)
            swap(n, m);
        long long ans = 0, last;
        for (int i = 1; i <= n; i = last + 1)
        {
            last = min(n / (n / i), m / (m / i));
            ans += (long long)(sum[last] - sum[i - 1]) * (n / i) * (m / i);
        }
        printf("%lld\n", ans);
    }
}