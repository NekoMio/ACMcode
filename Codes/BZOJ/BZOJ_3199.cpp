#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 610;
const double eps = 1e-10;
struct edge
{
    int END, next;
}v[MAXN * MAXN * 2];
int first[MAXN], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
struct Point
{
    double x, y;
    Point(double _x = 0, double _y = 0): x(_x), y(_y) {}
}a[MAXN], S, E;
struct line
{
    double a, b, c, k;
    int id;
    line(double _a = 0, double _b = 0, double _c = 0, int _id = 0)
    {
        a = _a, b = _b, c = _c;
        id = _id;
        k = atan2(-a, b);
    }
}l[MAXN];
Point Cross(const line &a, const line &b)
{
    double x = (a.b * b.c - a.c * b.b) / (a.a * b.b - b.a * a.b);
    double y = (a.a * b.c - a.c * b.a) / (a.b * b.a - b.b * a.a);
    return Point(x, y);
}
bool cmp(const line &a, const line &b)
{
    if (a.k == b.k) return a.c < b.c;
    return a.k < b.k;
}
double Calc(const line &a, const Point &x)
{
    return a.a * x.x + a.b * x.y + a.c;
}
int cnt;
void addline(double a, double b, double c, int id)
{
    if (a != 1 && a != 0) b /= fabs(a), c /= fabs(a), a /= fabs(a);
    l[++cnt] = line(a, b, c, id);
}
bool Judge(const line &a, const Point &x)
{
    return Calc(a, x) <= 0;
}
int q[MAXN];
void AddEdge(int x)
{
    sort(l + 1, l + cnt + 1, cmp);
    int num = 1;
    for (int i = 2; i <= cnt; i++)
        if (l[i].k - l[i - 1].k >= eps)
            l[++num] = l[i];
    int h = 1, t = 0;
    for (int i = 1; i <= num; i++)
    {
        while (h < t && Judge(l[i], Cross(l[q[t]], l[q[t - 1]]))) t--;
        while (h < t && Judge(l[i], Cross(l[q[h]], l[q[h + 1]]))) h++;
        q[++t] = i;
    }
    while (h < t && Judge(l[q[h]], Cross(l[q[t]], l[q[t - 1]]))) t--;
    while (h < t && Judge(l[q[t]], Cross(l[q[h]], l[q[h + 1]]))) h++;
    if (t - h < 2) return;
    for (int i = h; i <= t; i++)
    {
        add(l[q[i]].id, x);
        add(x, l[q[i]].id);
    }
}
double len(Point &x, Point &y)
{
    return sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y));
}

bool vis[MAXN];
int dis[MAXN], n;
int Spfa(int x)
{
    memset (dis, 0x3f, sizeof (dis));
    vis[x] = 1;
    dis[x] = 0;
    queue<int> Q;
    Q.push(x);
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        vis[k] = 0;
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].END] > dis[k] + 1)
            {
                dis[v[i].END] = dis[k] + 1;
                if (!vis[v[i].END])
                {
                    vis[v[i].END] = 1;
                    Q.push(v[i].END);
                } 
            }
        }
    }
    return dis[n + 1];
}
int main()
{
    // freopen ("escape2.in", "r", stdin);
    // freopen ("1.out", "w", stdout);
    int t = read();
    // printf ("%d\n", t);
    while (t--)
    {
        n = read();
        memset (first, -1, sizeof (first)); p = 0;
        E.x = read(), E.y = read(), S.x = read(), S.y = read();
        if (n == 0) {printf ("0\n"); continue;}
        for (int i = 1; i <= n; i++)
            a[i].x = read(), a[i].y = read();
        for (int i = 1; i <= n; i++)
        {
            cnt = 0;
            addline(1, 0, 0, n + 1);
            addline(0, 1, 0, n + 1);
            addline(-1, 0, E.x, n + 1);
            addline(0, -1, E.y, n + 1);
            for (int j = 1; j <= n; j++)
            {
                if (i == j) continue;
                if (a[i].x == a[j].x)
                {
                    line c = line(0, 1, - (a[i].y + a[j].y) / 2);
                    if (Calc(c, a[i]) < 0)
                        addline(0, -1, (a[i].y + a[j].y) / 2, j);
                    else
                        addline(0, 1, - (a[i].y + a[j].y) / 2, j);
                }
                else if (a[i].y == a[j].y)
                {
                    line c = line(1, 0, - (a[i].x + a[j].x) / 2);
                    if (Calc(c, a[i]) < 0)
                        addline(-1, 0, (a[i].x + a[j].x) / 2, j);
                    else
                        addline(1, 0, - (a[i].x + a[j].x) / 2, j);
                }
                else
                {
                    // line(1.0,(b[1]-a[1])/(b[0]-a[0]),-c[0]-(b[1]-a[1])/(b[0]-a[0])*c[1],id);
                    line c = line(1, (a[j].y - a[i].y) / (a[j].x - a[i].x), - ((a[i].x + a[j].x) / 2) - (a[j].y - a[i].y) / (a[j].x - a[i].x) * ((a[i].y + a[j].y) / 2));
                    if (Calc(c, a[i]) < 0)
                        addline(-1, -(a[j].y - a[i].y) / (a[j].x - a[i].x), ((a[i].x + a[j].x) / 2) + (a[j].y - a[i].y) / (a[j].x - a[i].x) * ((a[i].y + a[j].y) / 2), j);
                    else
                        addline(1, (a[j].y - a[i].y) / (a[j].x - a[i].x), - ((a[i].x + a[j].x) / 2) - (a[j].y - a[i].y) / (a[j].x - a[i].x) * ((a[i].y + a[j].y) / 2), j);
                }
            }
            AddEdge(i);
        }
        int s = 0;
        double min = 1e60;
        for (int i = 1; i <= n; i++)
            if (len(a[i], S) < min)
                s = i, min = len(a[i], S);
        printf ("%d\n", Spfa(s));
    }
}
