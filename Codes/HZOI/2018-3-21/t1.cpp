// #pragma GCC optimize("O2")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 255;
struct Point
{
    double x, y;
    int id;
    Point(double _x = 0, double _y = 0): x(_x), y(_y) {}
    double operator * (const Point &a)
    {
        return x * a.y - y * a.x;
    }
    Point operator - (const Point &a)
    {
        return Point(x - a.x, y - a.y);
    }
    Point operator - (const Point &a) const
    {
        return Point(x - a.x, y - a.y);
    }
}a[MAXN];
struct line
{
    Point a, b;
    double k;
    line() {}
    line(Point _a, Point _b): a(_a), b(_b)
    {
        k = atan2(_b.y - _a.y, _b.x - _a.x);
    }
}l[MAXN * MAXN];
bool cmp(const line &a, const line &b)
{
    return a.k < b.k;
}
int DP[MAXN][MAXN];
int Max[MAXN];
int main()
{
    // freopen ("1.out", "w", stdout);
    int n = read();
    for (int i = 1; i <= n; i++)
    {
        a[i].x = read(), a[i].y = read();
        a[i].id = i;
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) if (i != j)
            l[++cnt] = line(a[i], a[j]);
    sort(l + 1, l + cnt + 1, cmp);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        memset (DP, 0x80, sizeof (DP));
        DP[0][i] = 1;
        memset (Max, 0x80, sizeof (Max));
        Max[i] = 1;
        for (int j = 1; j <= cnt; j++)
        {
            if (l[j].b.id != i)
            {
                DP[l[j].a.id][l[j].b.id] = max(DP[l[j].a.id][l[j].b.id], Max[l[j].a.id] + 1);
                Max[l[j].b.id] = max(Max[l[j].b.id], DP[l[j].a.id][l[j].b.id]);
            }
            else ans = max(ans, Max[l[j].a.id]);
        }
    }
    printf ("%d\n", ans);
}