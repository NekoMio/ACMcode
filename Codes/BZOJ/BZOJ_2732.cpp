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
const int MAXN = 200005;
const double eps = 1e-15;
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
    double a, b, c, k;
    int id;
    line(){;}
    line(double _a, double _b, double _c, int _id)
    {
        id = _id;
        a = _a, b = _b, c = _c;
        k = atan2(-a, b);
    }
}l[MAXN], tmp[MAXN];
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
bool Judge(const line &a, const Point &x)
{
    return a.a * x.x + a.b * x.y + a.c < 0;
}
int cnt;
void addline(double a, double b, double c)
{
    if (a != 0) b /= fabs(a), c /= fabs(a), a /= fabs(a);
    cnt++;
    l[cnt] = line(a, b, c, cnt); 
}
int q[MAXN], h, t;
bool Judge(int mid)
{
    h = 1, t = 0;
    // q[1] = 1, q[2] = 2;
    int top = 0;
    tmp[++top] = l[1];
    for (int i = 2; i <= cnt; i++)
        if (l[i].k - l[i - 1].k >= eps)
            tmp[++top] = l[i];
    for (int i = 1; i <= top; i++)
    {
        if (tmp[i].id > 2 * mid) continue;
        while (t > h && Judge(tmp[i], Cross(tmp[q[t]], tmp[q[t - 1]]))) t--;
        while (t > h && Judge(tmp[i], Cross(tmp[q[h]], tmp[q[h + 1]]))) h++;
        q[++t] = i;
    }
    while (t > h && Judge(tmp[q[h]], Cross(tmp[q[t]], tmp[q[t - 1]]))) t--;
    while (t > h && Judge(tmp[q[t]], Cross(tmp[q[h]], tmp[q[h + 1]]))) h++;
    if (t - h >= 2) return 1;
    else return 0;
}
int main()
{
    // freopen ("bzoj_2732.in", "r", stdin);
    // freopen ("bzoj_2732.out", "w", stdout);
    int n = read();
    for (int i = 1; i <= n; i++)
    {
        double x = read(), y1 = read(), y2 = read();
        addline(1.0 * x * x, x, -y1);
        addline(-1.0 * x * x, -x, y2);
    }
    addline(-1, 0, 0);
    l[cnt].id = 0; 
    addline(0, 1, 0);
    l[cnt].id = 0;
    int L = 1, R = n;
    sort(l + 1, l + cnt + 1, cmp);
    // int t = 1;
    // for (int i = 2; i <= cnt; i++)
    //     if (l[i].k - l[i - 1].k >= eps)
    //         l[++t] = l[i];
    // cnt = t;
    int ans = 0;
    while (L <= R)
    {
        int mid = L + R >> 1;
        if (Judge(mid)) ans = mid, L = mid + 1;
        else R = mid - 1;
    }
    printf ("%d\n", ans);
}