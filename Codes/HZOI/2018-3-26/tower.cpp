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
const int MAXN = 50005;
const double eps = 1e-12;
struct Point
{
	double x, y;
	Point(double _x = 0, double _y = 0): x(_x), y(_y) {}
	Point operator - (const Point &b)
	{
		return Point(x - b.x, y - b.y);
	}
}a[MAXN];
struct line
{
    double a, b, c, k;
    line(){;}
    line(double _a, double _b, double _c)
    {
        a = _a, b = _b, c = _c;
        k = atan2(-a, b);
    }
}l[MAXN * 3];
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
    return a.a * x.x + a.b * x.y + a.c <= 0;
}
int cnt, n;
void addline(double a, double b, double c)
{
    if (a != 0) b /= fabs(a), c /= fabs(a), a /= fabs(a);
    l[++cnt] = line(a, b, c); 
}
int ID(int x)
{
	if (x > n) return x - n;
	return x;
}
int q[MAXN * 10];
double MinX, MaxX, MinY, MaxY;
bool Judge(int x)
{
	// printf ("%d\n", x);
	cnt = 0;
	addline(1, 0, -MinX);
	addline(0, 1, -MinY);
	addline(-1, 0, MaxX);
	addline(0, -1, MaxY);
	for (int i = 1; i <= n; i++)
	{
		int now = ID(i), nxt = ID(i + 1);
		line C;
		if (a[nxt].x == a[now].x) C = line(1, 0, -a[now].x);
		else if (a[nxt].y == a[now].y) C = line(0, 1, -a[now].y);
		else C = line(a[nxt].y - a[now].y, -(a[nxt].x - a[now].x), a[now].y * (a[nxt].x - a[now].x) - a[now].x * (a[nxt].y - a[now].y));
		if (Judge(C, a[ID(i + 2)])) addline(-C.a, -C.b, -C.c);
		else addline(C.a, C.b, C.c);
	}
	for (int i = 1; i <= n; i++)
	{
		int now = ID(i + x - 1), nxt = ID(i);
		line C;
		if (a[nxt].x == a[now].x) C = line(1, 0, -a[now].x);
		else if (a[nxt].y == a[now].y) C = line(0, 1, -a[now].y);
		else C = line(a[nxt].y - a[now].y, -(a[nxt].x - a[now].x), a[now].y * (a[nxt].x - a[now].x) - a[now].x * (a[nxt].y - a[now].y));
		if (Judge(C, a[ID(i + 1)])) addline(-C.a, -C.b, -C.c);
		else addline(C.a, C.b, C.c);
	}
	int top = 1;
	sort(l + 1, l + cnt + 1, cmp);
	for (int i = 2; i <= cnt; i++)
        if (l[i].k - l[i - 1].k >= eps)
            l[++top] = l[i];
	int h = 1, t = 0;
    for (int i = 1; i <= top; i++)
    {
        while (t > h && Judge(l[i], Cross(l[q[t]], l[q[t - 1]]))) t--;
        while (t > h && Judge(l[i], Cross(l[q[h]], l[q[h + 1]]))) h++;
        q[++t] = i;
    }
    while (t > h && Judge(l[q[h]], Cross(l[q[t]], l[q[t - 1]]))) t--;
    while (t > h && Judge(l[q[t]], Cross(l[q[h]], l[q[h + 1]]))) h++;
    if (t - h >= 2) return 0;
    else return 1;
}
int main()
{
	// freopen("3.out", "w", stdout);
	n = read();
	for (int i = 1; i <= n; i++)
	{
		a[i].x = read(), a[i].y = read();
		MinX = min(MinX, a[i].x);
		MinY = min(MinY, a[i].y);
		MaxX = max(MaxX, a[i].x);
		MaxY = max(MaxY, a[i].y);
	}
	int l = 3, r = n, ans = 0;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (Judge(mid)) l = mid + 1;
		else ans = mid, r = mid - 1;
	}
	printf ("%d\n", n - ans);
	// while (1);
}