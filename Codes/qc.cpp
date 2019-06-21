#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define LL long long
int n, m;
struct data
{
    int w, v;
} a[200005];
struct Data
{
    int l, r;
} Q[200005];
int Sumn[200005];
LL Sumv[200005];
LL check(int w)
{
    Sumn[0] = 0;
    Sumv[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        Sumn[i] = Sumn[i - 1] + (a[i].w > w);
        Sumv[i] = Sumv[i - 1] + (a[i].w > w ? a[i].v : 0);
    }
    LL Y = 0;
    for (int i = 1; i <= m; i++)
    {
        Y += (Sumn[Q[i].r] - Sumn[Q[i].l - 1]) * (Sumv[Q[i].r] - Sumv[Q[i].l - 1]);
    }
    return Y;
}
int main()
{
    freopen("qc.in", "r", stdin);
    freopen("qc.out", "w", stdout);
    LL S;
    scanf("%d%d%lld", &n, &m, &S);
    int Max = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &a[i].w, &a[i].v);
        Max = max(Max, a[i].w);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &Q[i].l, &Q[i].r);
    }
    LL l = 0, r = Max;
    LL ans = 0x3fffffffffffffffLL;
    while (l < r)
    {
        LL mid = l + r >> 1;
        LL t = check(mid);
        if (t < S)
        {
            ans = min(ans, abs(t - S));
            r = mid;
        }
        else
        {
            ans = min(ans, abs(t - S));
            l = mid + 1;
        }
    }
    printf("%lld", ans);

    //while (1);
}
