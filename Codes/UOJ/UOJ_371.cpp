#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct Point
{
    double x, y;
    Point(double _x = 0, double _y = 0): x(_x), y(_y) {}
    Point operator - (const Point &a)
    {
        return Point(x - a.x, y - a.y);
    }
    double operator * (const Point &a)
    {
        return x * a.x + y * a.y;
    }
    double operator ^ (const Point &a)
    {
        return x * a.y - y * a.x;
    }
}a[1005];
int du[1005];
struct edge
{
    int S, END, next, id;
}v[2005];
int first[1005], p;
void add(int c, int b, int id)
{
    v[p].S = c;
    v[p].END = b;
    v[p].next = first[c];
    v[p].id = id;
    first[c] = p++;
}
double dis(const Point &x, const Point &y)
{
    return sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y));
}
struct line
{
    Point a, b, c;
    double k;
    line() {}
    line(Point x, Point y) 
    {
        a = x, b = y;
        c = a - b;
        k = atan2(b.y - a.y, b.x - a.x);
    }
}l[1005];
double dis(Point &x, line &y)
{
    if ((y.c * (y.a - x)) * (y.c * (y.b - x)) <= 0)
        return abs((y.a - x) ^ (y.b - x)) / dis(y.a, y.b);
    return min(dis(y.a, x), dis(y.b, x));
}
bool f[1005][1005];
int n, stx, sty;
bool Judge(double mid)
{
    memset (f, 0, sizeof (f));
    queue<pair<int, int> > Q;
    for (int i = first[stx]; i != -1; i = v[i].next)
        f[sty][v[i].id] = 1, Q.push(pair<int, int>(sty, v[i].id));
    for (int i = first[sty]; i != -1; i = v[i].next)
        f[stx][v[i].id] = 1, Q.push(pair<int, int>(stx, v[i].id));
    while (!Q.empty())
    {
        pair<int, int> k = Q.front(); Q.pop();
        int x = k.first, y = k.second;
        for (int i = first[x]; i != -1; i = v[i].next)
        {
            if (!f[v[i].END][y] && dis(a[v[i].END], l[y]) <= mid)
            {
                f[v[i].END][y] = 1;
                Q.push(pair<int, int>(v[i].END, y));
            }
            if (!f[v[(y - 1) << 1].S][v[i].id] && dis(a[v[(y - 1) << 1].S], l[v[i].id]) <= mid)
            {
                f[v[(y - 1) << 1].S][v[i].id] = 1;
                Q.push(pair<int, int>(v[(y - 1) << 1].S, v[i].id));
            }
            if (!f[v[(y - 1) << 1].END][v[i].id] && dis(a[v[(y - 1) << 1].END], l[v[i].id]) <= mid)
            {
                f[v[(y - 1) << 1].END][v[i].id] = 1;
                Q.push(pair<int, int>(v[(y - 1) << 1].END, v[i].id));
            }
        }
    }
    for (int i = 1; i <= n; i++) if (du[i] == 1)
        for (int j = 1; j <= n; j++) if (du[j] == 1)
            if (f[i][v[first[j]].id] && dis(a[i], a[j]) <= mid)
                return 1;
    return 0;
}
int main()
{
    memset (first, -1, sizeof (first));
    n = read(), stx = read(), sty = read();
    for (int i = 1; i <= n; i++)
        a[i].x = read(), a[i].y = read();
    for (int i = 1; i < n; i++)
    {
        int b = read(), c = read();
        du[b]++, du[c]++;
        add(b, c, i);
        add(c, b, i);
        l[i] = line(a[b], a[c]);
    }
    double l = dis(a[stx], a[sty]), r = 1e6;
    while (abs(r - l) >= 1e-8)
    {
        double mid = (l + r) / 2;
        if (Judge(mid)) r = mid;
        else l = mid;
    }
    printf ("%.10f", l);
    // while (1);
}