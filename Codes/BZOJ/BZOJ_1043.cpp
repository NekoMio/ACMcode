#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const double Pi = acos(-1);
struct Circle
{
    double x, y, r;
}a[1005];
struct line
{
    double l, r;
    bool operator < (const line &b) const 
    {
        return l < b.l;
    }
}q[1005];
int n, t;
double dis(int a1, int a2)
{
    return sqrt((a[a1].x - a[a2].x) * (a[a1].x - a[a2].x) + (a[a1].y - a[a2].y) * (a[a1].y - a[a2].y));
}
bool In(int a1, int a2)
{
    if (a[a1].r >= a[a2].r + dis(a1, a2)) return 1;
    return 0;
}
void add(int a1, int a2)
{
    double d = dis(a1, a2);
    double st = atan2(a[a1].x - a[a2].x, a[a1].y - a[a2].y);
    double l = acos(((a[a1].r * a[a1].r - a[a2].r * a[a2].r + d * d) / (2 * d)) / a[a1].r);
    q[++t] = (line){st - l, st + l};
}
double Get(int x)
{
    for (int i = x + 1; i <= n; i++)
        if (In(i, x)) return 0;
    t = 0;
    for (int i = x + 1; i <= n; i++)
        if (!In(x, i) && a[x].r + a[i].r >= dis(x, i))
            add(x, i);
    for (int i = 1; i <= t; i++)
    {
        if (q[i].l < 0) q[i].l += 2 * Pi;
        if (q[i].r < 0) q[i].r += 2 * Pi;
        if (q[i].l > q[i].r)
        {
            q[++t] = (line){0, q[i].r};
            q[i].r = 2 * Pi;
        }
    }
    double tmp = 0, now = 0;
    sort(q + 1, q + t + 1);
    for (int i = 1; i <= t; i++)
        if (q[i].l > now)
        {
            tmp += q[i].l - now;
            now = q[i].r;
        }
        else now = max(now, q[i].r);
    tmp += 2 * Pi - now;
    return a[x].r * tmp;
}
int main()
{
    // freopen("disc.in", "r", stdin);
    // freopen("disc.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf%lf", &a[i].r, &a[i].x, &a[i].y);
    double ans = 0;
    for (int i = 1; i <= n; i++)
        ans += Get(i);
    printf("%.3lf", ans);
}