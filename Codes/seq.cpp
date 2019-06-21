#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define LL long long
const LL P = 1e9 + 7;
LL F[100005];
void Init()
{
    F[0] = 1;
    for (int i = 1; i <= 100000; i++)
        F[i] = i * F[i - 1] % P;
}
LL pow_mod(LL a, int b)
{
    LL ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % P;
        b >>= 1;
        a = a * a % P;
    }
    return ans;
}
LL C(int n, int m)
{
    if (m > n || m < 0)
        return 0;
    return F[n] * pow_mod(F[m] * F[n - m] % P, P - 2) % P;
}
LL a[100005], Has[100005];
int Sum[100005], n;
#define lowbit(_) ((_) & (-_))

void add(int x, int c)
{
    for (int i = x; i <= n; i += lowbit(i))
        Sum[i] += c;
}
int Query(int x)
{
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += Sum[i];
    return ans;
}
int fron[100005], nxt[100005];
int main()
{
    Init();
    int K;
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        Has[i] = a[i];
    }
    sort(Has + 1, Has + n + 1);
    int tot = unique(Has + 1, Has + n + 1) - Has - 1;
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(Has + 1, Has + tot + 1, a[i]) - Has;
    for (int i = 1; i <= n; i++)
    {
        fron[i] = Query(a[i]);
        add(a[i], 1);
    }
    memset(Sum, 0, sizeof(Sum));
    for (int i = n; i >= 1; i--)
    {
        nxt[i] = Query(a[i] - 1);
        add(a[i], 1);
    }
    LL ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= K; j++)
        {
            ans = ans + ((Has[a[i]] * C(fron[i], j)) % P * C(nxt[i], K - j - 1)) % P;
        }
        ans = ans % P;
    }
    printf("%lld", ans);
}
