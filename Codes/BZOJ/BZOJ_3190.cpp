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
const int MAXN = 10005;
struct Point
{
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    Point operator + (const Point &a) const
    {
        return Point(x + a.x, y + a.y);
    }
    Point operator - (const Point &a) const
    {
        return Point(x - a.x, y - a.y);
    }
    double operator * (const Point &b) const
    {
        return x * b.y - b.x * y;
    }
};
struct line
{
    double a, b, c;
    int id;
    line(){;}
    line(double _a, double _b, double _c, int _id)
    {
        id = _id;
        a = _a, b = _b, c = _c;
    }
}l[MAXN], r[MAXN];
Point Cross(const line &a, const line &b)
{
    double x = (a.b * b.c - a.c * b.b) / (a.a * b.b - b.a * a.b);
    double y = (a.a * b.c - a.c * b.a) / (a.b * b.a - b.b * a.a);
    return Point(x, y);
}
bool cmp(const line &a, const line &b)
{
    if (a.a == b.a) return a.c > b.c;
    return a.a > b.a;
}
bool Judge(const line &a, const Point &x)
{
    return a.a * x.x + a.b * x.y + a.c < 0;
}
int c[MAXN];
int q[MAXN], h, t;
bool cmp2(const int &a, const int &b)
{
    return l[a].id < l[b].id;
}
int main()
{
    // freopen ("race1.in", "r", stdin);
    // freopen ("race1.out", "w", stdout);
    int n = read();
    for (int i = 1; i <= n; i++)
        c[i] = read();
    for (int i = 1; i <= n; i++)
        l[i] = line(-read(), 1, -c[i], i);
    sort(l + 1, l + n + 1, cmp);
    n++;
    l[0] = line(1, 0, 0, n);
    int cnt = n;
    // for (int i = 2; i <= n; i++)
    //     if (l[i].k - l[cnt].k >= eps)
    //         l[++cnt] = l[i];
    h = 1, t = 2;
    q[1] = 0, q[2] = 1;
    for (int i = 2; i < n; i++)
    {
        while (t > h && Judge(l[i], Cross(l[q[t]], l[q[t - 1]]))) t--;
        while (t > h && Judge(l[i], Cross(l[q[h]], l[q[h + 1]]))) h++;
        q[++t] = i;
    }
    while (t > h && Judge(l[q[h]], Cross(l[q[t]], l[q[t - 1]]))) t--;
    while (t > h && Judge(l[q[t]], Cross(l[q[h]], l[q[h + 1]]))) h++;
    sort(q + h, q + t + 1, cmp2);
    printf ("%d\n", t - h);
    for (int i = h; i < t - 1; i++)
        printf ("%d ", l[q[i]].id);
    printf ("%d", l[q[t - 1]].id);
    // while (1);
}