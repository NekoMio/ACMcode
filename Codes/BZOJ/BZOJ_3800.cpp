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
const int MAXN = 105;
const double eps = 1e-8;
struct Point
{
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
};
struct line
{
    double a, b, c, k;
    int id;
    line(){}
    line(double _a, double _b, double _c, double _id)
    {
        a = _a, b = _b, c = _c, id = _id;
        k = atan2(-a, b);
    }
}l[MAXN];
Point Cross(const line &a, const line &b)
{
    Point x;
    x.x = (a.b * b.c - a.c * b.b) / (a.a * b.b - a.b * b.a);
    x.y = (a.a * b.c - a.c * b.a) / (a.b * b.a - a.a * b.b);
    return x;
}
bool cmp(const line &a, const line &b)
{
    if (a.k == b.k) return a.c < b.c;
    return a.k < b.k;
}
bool Judge(const line &a, const Point &x)
{
    return a.a * x.x + a.b * x.y + a.c <= 0;
}
void addline(double a, double b, double c, int id)
{
    if (a != 0) b /= fabs(a), c /= fabs(a), a /= fabs(a);
    l[id] = line(a, b, c, id);
    // printf ("%d %lf\n", id, l[id].k, a, b, c);
}
int q[MAXN];
bool Judge(int cnt)
{
    sort(l + 1, l + cnt + 1, cmp);
    for (int i = 1; i <= cnt; i++) if (l[i].a == 0 && l[i].b == 0 && l[i].c == 0) return 0;
    int top = 1;
    for (int i = 2; i <= cnt; i++)
        if (l[i].k - l[i - 1].k >= eps)
            l[++top] = l[i];
    int h = 1, t = 0;
    for (int i = 1; i <= top; i++)
    {
        while (h < t && Judge(l[i], Cross(l[q[t - 1]], l[q[t]]))) t--;
        while (h < t && Judge(l[i], Cross(l[q[h + 1]], l[q[h]]))) h++;
        q[++t] = i;
    }
    while (h < t && Judge(l[q[h]], Cross(l[q[t - 1]], l[q[t]]))) t--;
    while (h < t && Judge(l[q[t]], Cross(l[q[h + 1]], l[q[h]]))) h++;
    // printf ("%d\n", t - h);
    return t - h >= 2;
}
double v1[MAXN], v2[MAXN], v3[MAXN];
int main()
{
    // freopen ("1.out", "w", stdout);
    int n = read();
    for (int i = 1; i <= n; i++)
        v1[i] = read(), v2[i] = read(), v3[i] = read();
    for (int i = 1; i <= n; i++)
    {
        int cnt = 0;
        for (int j = 1; j <= n; j++)
            if (i != j)
                addline(1 / v1[j] - 1 / v3[j] - 1 / v1[i] + 1 / v3[i] , 1 / v2[j] - 1 / v3[j] - 1 / v2[i] + 1 / v3[i], 1 / v3[j] - 1 / v3[i], ++cnt);
        addline(1, 0, 0, ++cnt);
        addline(0, 1, 0, ++cnt);
        addline(-1, -1, 1, ++cnt);
        if (Judge(cnt)) puts("Yes");
        else puts("No");
    }
}