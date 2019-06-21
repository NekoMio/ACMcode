#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct data
{
    long long p, s;
    bool no;
    bool operator < (const data &a) const 
    {
        return s < a.s;
    }
}a[205], f[205];
long long m, k, n, cnt;
long long Get_day(long long mid)
{
    long long Last_Money = m - k * mid, Part_Now_day = 0, ret = 0;
    long long tmp;
    for (int i = 1; i <= n; i++)
    {
        if (Part_Now_day <= f[i].s)
        {
            tmp = f[i].s - Part_Now_day + 1;
            tmp = min(tmp, Last_Money / (f[i].p * mid));
            ret += tmp * mid;
            Last_Money -= f[i].p * mid * tmp;
            Part_Now_day += tmp;
        }
        if (Part_Now_day <= f[i].s)
        {
            tmp = min(mid, Last_Money / f[i].p);
            ret += tmp;
            Last_Money -= tmp * f[i].p;
            Part_Now_day++;
        }
    }
    return ret;
}
int main()
{
    scanf("%lld%lld%lld", &m, &k, &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &a[i].p, &a[i].s);
    for (int i = 1; i <= n; i++)
    {
        if (a[i].no) continue;
        for (int j = 1; j <= n; j++)
        {
            if (a[j].no) continue;
            if (a[i].p <= a[j].p && a[i].s >= a[j].s && i != j)
                a[j].no = 1;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if(!a[i].no)
            f[++cnt] = a[i];
    }
    sort(f + 1, f + cnt + 1);
    n = cnt;
    long long l = 1, r = m / (f[1].p + k), mid1, mid2, v1, v2, ans = 0;
    while (l <= r)
    {
        mid1 = l + (r - l) / 3, mid2 = r - (r - l) / 3;
        v1 = Get_day(mid1), v2 = Get_day(mid2);
        if (v1 < v2) ans = max(ans, v2), l = mid1 + 1;
        else if (v1 > v2) ans = max(ans, v1), r = mid2 - 1;
        else ans = max(ans, v1), l = mid1 + 1, r = mid2 - 1;
    }
    printf("%lld", ans);
}