#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const double eps = 1e-10;
const int MAXN = 1e5 + 5;
struct Point
{
    double x, y;
    Point(double _x = 0, double _y = 0): x(_x), y(_y) {}
    double operator * (const Point &a)
    {
        return x * a.y - y * a.x;
    }
    Point operator - (const Point &a)
    {
        return Point(x - a.x, y - a.y);
    }
}a[MAXN], p[MAXN];
struct line
{
    double a, b, c, k;
    int id;
    line(double _a = 0, double _b = 0, double _c = 0, int _id = 0)
    {
        a = _a, b = _b, c = _c;
        k = atan2(-a, b);
        id = _id;
    }
}l[MAXN * 2];
void addline(double a, double b, double c, int id)
{
    if (a != 1 && a != 0) b /= fabs(a), c /= fabs(a), a /= fabs(a);
    l[id] = line(a, b, c, id);
}
Point Cross(const line &a, const line &b)
{
    double x = (a.b * b.c - a.c * b.b) / (a.a * b.b - a.b * b.a);
    double y = (a.a * b.c - a.c * b.a) / (a.b * b.a - a.a * b.b);
    return Point(x, y);
}
bool cmp(const line &a, const line &b)
{
    if (a.k == b.k) return a.c < b.c;
    return a.k < b.k;
}
bool Judge(const line &a, const Point &b)
{
    return a.a * b.x + a.b * b.y + a.c < 0;
}
int q[MAXN * 2];
int h, t;
bool Judge(Point x)
{
    for (int i = h; i <= t; i++)
        if (Judge(l[q[i]], x))
            return 0;
    return 1;
}
int cnt;
double area(Point *x, int n)
{
    double ans = 0;
    for (int i = 2; i <= n - 1; i++)
        ans += (x[i] - x[1]) * (x[i + 1] - x[1]);
    return ans;
}
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
        a[i].x = read(), a[i].y = read();
    for (int i = 2; i < n; i++)
        addline(a[i].y - a[i + 1].y - a[1].y + a[2].y, a[i + 1].x - a[i].x - a[2].x + a[1].x, a[i].x * a[i + 1].y - a[i + 1].x * a[i].y + a[2].x * a[1].y - a[1].x * a[2].y, ++cnt);
    addline(a[n].y - a[1].y - a[1].y + a[2].y, a[1].x - a[n].x - a[2].x + a[1].x, a[n].x * a[1].y - a[1].x * a[n].y + a[2].x * a[1].y - a[1].x * a[2].y, ++cnt);
    for (int i = 1; i <= n; i++)
    {
        int nx1 = i + 1, nx2 = i + 2;
        if (nx1 > n) nx1 = nx1 % n;
        if (nx2 > n) nx2 = nx2 % n;
        if (a[i].x == a[nx1].x)
        {
            line c = line(1, 0, -a[i].x);
            if (Judge(c, a[nx2])) addline(-1, 0, a[i].x, ++cnt);
            else addline(1, 0, a[i].x, ++cnt);
        }
        else if (a[i].y == a[nx1].y)
        {
            line c = line(0, 1, -a[i].y);
            if (Judge(c, a[nx2])) addline(0, -1, a[i].y, ++cnt);
            else addline(0, 1, a[i].y, ++cnt);
        }
        else
        {
            line c = line((a[i].y - a[nx1].y) / (a[i].x - a[nx1].x), -1, -a[i].x * (a[i].y - a[nx1].y) / (a[i].x - a[nx1].x) + a[i].y);
            if (Judge(c, a[nx2])) addline(-(a[i].y - a[nx1].y) / (a[i].x - a[nx1].x), 1, a[i].x * (a[i].y - a[nx1].y) / (a[i].x - a[nx1].x) - a[i].y, ++cnt);
            else addline((a[i].y - a[nx1].y) / (a[i].x - a[nx1].x), -1, -a[i].x * (a[i].y - a[nx1].y) / (a[i].x - a[nx1].x) + a[i].y, ++cnt);
        }
    }
    h = 1, t = 0;
    sort(l + 1, l + cnt + 1, cmp);
    int num = 1;
    for (int i = 2; i <= cnt; i++)
        if (l[i].k - l[i - 1].k >= eps)
            l[++num] = l[i];
    for (int i = 1; i <= num; i++)
    {
        while (h < t && Judge(l[i], Cross(l[q[t]], l[q[t - 1]]))) t--;
        while (h < t && Judge(l[i], Cross(l[q[h]], l[q[h + 1]]))) h++;
        q[++t] = i;
    }
    int e = 0;
    while (h < t && Judge(l[q[h]], Cross(l[q[t]], l[q[t - 1]]))) t--;
    while (h < t && Judge(l[q[t]], Cross(l[q[h]], l[q[h + 1]]))) h++;
    for (int i = h; i < t; i++)
        p[++e] = Cross(l[q[i]], l[q[i + 1]]);
    p[++e] = Cross(l[q[t]], l[q[h]]);
    printf ("%.4f\n", area(p, e) / area(a, n));
}