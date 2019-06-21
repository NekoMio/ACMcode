#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
struct point
{
    double x, y;
    double Max, Min;
    bool operator < (const point a) const
    {
        return x == a.x ? y < a.y : x < a.x;
    }
}a[6005];
int k, m;
int fa[6005];
int find(int x)
{
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}
double dis(point a, point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
bool Judge(double mid)
{
    for (int i = 1; i <= k; i++)
    {
        fa[i] = i;
        a[i].Max = a[i].y + mid, a[i].Min = a[i].y - mid;
        if (a[i].Max >= m - mid && a[i].Min <= mid) return 0;
    }
    for (int i = 1; i <= k; i++)
    {
        for (int j = i + 1; j <= k; j++)
        {
            if (a[j].x - a[i].x > 2 * mid) break;
            if (dis(a[i], a[j]) <= 2 * mid && find(i) != find(j))
            {
                int J = find(j), I = find(i);
                if (a[J].Max < a[I].Max) a[J].Max = a[I].Max;
                if (a[J].Min > a[I].Min) a[J].Min = a[I].Min;
                fa[I] = J;
                if (a[J].Max >= m - mid && a[J].Min <= mid) return 0;
            }
        }
    }
    return 1;
}
int main()
{
    int n;
    scanf ("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; i++)
        scanf ("%lf%lf", &a[i].x, &a[i].y);
    sort(a + 1, a + k + 1);
    double l = 0, r = m / 2 + 1, mid;
    while (l + 1e-7 < r)
    {
        mid = (l + r) / 2;
        if (Judge(mid))
            l = mid;
        else
            r = mid;
    }
    printf ("%.9lf", l);
}
