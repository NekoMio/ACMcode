// #pragma GCC optimize("O")
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
const double eps = 1e-13;
const int INF = 0x3f3f3f3f;
const int MAXN = 1005;
struct Circle
{
    int x, y, r;
    bool Disable;
}a[MAXN], b[MAXN];
int n;
struct line
{
    double l, r;
}st[MAXN];
double p2(double x)
{
    return x*x;
}
bool cmp(const line &b, const line &c)
{
    return b.l == c.l ? b.r < c.r : b.l < c.l;
}
double F(double x)
{
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (fabs(x - a[i].x) < a[i].r)
        {
            double len = sqrt(p2(a[i].r) - p2(x - a[i].x));
            st[++cnt].l = 1.0 * a[i].y - len;
            st[cnt].r = 1.0 * a[i].y + len;
        }
    sort(st + 1, st + cnt + 1, cmp);
    double ans = 0;
    double last = -2000;
    for (int i = 1; i <= cnt; i++)
    {
        if (last < st[i].l)
        {
            ans += st[i].r - st[i].l;
            last = st[i].r;
        }
        else if (st[i].r > last)
        {
            ans += st[i].r - last;
            last = st[i].r;
        }
    }
    // ans += (r - l);
    return ans;
}
double Calc(double l, double r, double fl, double fr, double fm)
{
    return (r - l) / 6.0 * (fl + fr + 4 * fm);
}
double Simpson(double l, double r, double mid, double fl, double fr, double fm, double s)
{
    double m1 = (l + mid) / 2, m2 = (mid + r) / 2;
    double f1 = F(m1), f2 = F(m2);
    double s1 = Calc(l, mid, fl, fm, f1), s2 = Calc(mid, r, fm, fr, f2);
    // printf ("%.3lf %.3lf\n", s1, s2);
    if (fabs(s - s1 - s2) < eps) return s1 + s2;
    return Simpson(l, mid, m1, fl, fm, f1, s1) + Simpson(mid, r, m2, fm, fr, f2, s2);
}
bool in(int x, int y)
{
    return sqrt(p2(b[x].x - b[y].x) + p2(b[x].y - b[y].y)) < b[y].r - b[x].r;
}
int main()
{
    n = read();
    int l = INF, r = -INF;
    int num = 0;
    for (int i = 1; i <= n; i++)
    {
        b[i].x = read();
        b[i].y = read();
        b[i].r = read();
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (in(i, j))
                b[i].Disable = true;
    for (int i = 1; i <= n; i++)
        if (!b[i].Disable)
            a[++num] = b[i];
    n = num;
    for (int i = 1; i <= n; i++)
    {
        l = min(l, a[i].x - a[i].r);
        r = max(r, a[i].x + a[i].r);
    }
    double fl = F(l), fr = F(r), fm = F((1.0 * l + r) / 2);
    printf ("%.3lf\n", Simpson(l, r, (1.0 * l + r) / 2, fl, fr, fm, Calc(l, r, fl, fr, fm)));
}