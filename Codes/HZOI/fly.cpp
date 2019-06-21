#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define LL long long
int c[(int)1e5 + 5], n;
LL a;
#define lowbit(_) ((_) & (-_))
void add(int x)
{
    for (int i = x; i <= a + 1; i += lowbit(i))
        c[i] += 1;
}
int Query(int x)
{
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += c[i];
    return ans;
}
int main()
{
    // freopen("fly.in", "r", stdin);
    // freopen("fly.in", "w", stdout);
    LL x, mod;
    scanf("%d%lld%lld%lld", &n, &x, &a, &mod);
    long long ans = 0;
    int i, s = x;
    for (i = 1; i <= n && x < mod; i++, x += a);
    int t = 0, m = 0, h = 0, cnt = 0, S = 0; x %= mod;
    for (; i <= n; i++, cnt++, x = (x + a) % mod)
    {
        if(x < a)
        {
            S = Query(x + 1);
            add(x + 1), t++, cnt = 0;
            m = S;
            if(x > s) m += (x - s) / a + 1;
        }
        else
        {
            m = S + t * cnt;
            if(x > s) m += (x - s) / a + 1;
        }
        ans += i - m - 1;
    }
    printf("%lld\n", ans);
    // while(1);
}