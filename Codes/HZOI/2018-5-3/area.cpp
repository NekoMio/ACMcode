#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
template<typename _Tp> inline void gmin(_Tp &a, _Tp b) { if (a > b) a = b; }
template<typename _Tp> inline void gmax(_Tp &a, _Tp b) { if (a < b) a = b; }
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int INF = 0x3f3f3f3f;
const int MAXN = 1e5 + 5;
struct Point
{
	long long x, y, k;
	Point(long long _x = 0, long long _y = 0): x(_x), y(_y) {}
	bool operator < (const Point &a) const { return k > a.k; }
	void read() {x = ::read(), y = ::read(); k = atan2(y, x);}
	void print() {fprintf (stderr, "%lld %lld\n", x, y); }
	Point operator - (const Point &a) { return Point(x - a.x, y - a.y); }
	Point operator - (const Point &a) const { return Point(x - a.x, y - a.y); }
	long long operator * (const Point &a) { return x * a.y - y * a.x; }
	long long operator * (const Point &a) const { return x * a.y - y * a.x; }
}a[MAXN], Cvx[MAXN];
#define sqr(_) ((_) * (_))
long long dis(const Point &x, const Point &y)
{
	return sqr(x.x - y.x) + sqr(x.y - y.y);
}
bool cmp(Point x, Point y)
{
	long long s = (x - a[1]) * (y - a[1]);
	if (s == 0) return dis(x, a[1]) < dis(y, a[1]);
	return s > 0;
}
int Run_Cvx(int n)
{
	int top = 0;
	int k = 1;
	for (int i = 1; i <= n; i++)
	{
		if (a[i].x < a[k].x) k = i;
		else if (a[i].x == a[k].x && a[i].y < a[k].y)
			k = i;
	}
	swap(a[1], a[k]);
	// a[1].print();
	sort(a + 2, a + n + 1, cmp);
	Cvx[++top] = a[1];
	for (int i = 2; i <= n; i++)
	{
		while (top > 1 && (Cvx[top] - Cvx[top - 1]) * (a[i] - Cvx[top]) <= 0) top--;
		Cvx[++top] = a[i];
	}
	return top;
}
long long area(const Point &x1, const Point &x2, const Point &x3)
{
	return abs((x2 - x1) * (x3 - x1));
}
#define nxt(_) ((_) == n ? 1 : (_) + 1)
long long Calc(int n)
{
	if (n <= 3)
	{
		if (n < 3) return 0;
		else return area(Cvx[1], Cvx[2], Cvx[3]);
	}
	Cvx[n + 1] = Cvx[1];
	long long ans = 0;
	int j = 3, k = j, l = 1;
	for (int i = 1; i <= n; i++)
	{
		while (area(Cvx[i], Cvx[i + 1], Cvx[j]) <= area(Cvx[i], Cvx[i + 1], Cvx[j + 1]))
		{
			if (j == k) k = nxt(k);
			j = nxt(j); 
		}
		while (area(Cvx[i], Cvx[j], Cvx[k]) <= area(Cvx[i], Cvx[j], Cvx[k + 1]) && nxt(k) != i)
			k = nxt(k);
		while (area(Cvx[i], Cvx[j], Cvx[l]) <= area(Cvx[i], Cvx[j], Cvx[l + 1]) && nxt(l) != j)
			l = nxt(l);
		ans = max(ans, area(Cvx[i], Cvx[j], Cvx[l]) + area(Cvx[i], Cvx[j], Cvx[k]));
		if (l == i) l = nxt(l);
	}
	return ans;
}
int main()
{
	// freopen ("area.in", "r", stdin);
	// freopen ("area.out", "w", stdout);
	int n = read();
	for (int i = 1; i <= n; i++)
		a[i].read();
	int cnt = Run_Cvx(n);
	// fprintf (stderr, "%d\n", cnt);
	// for (int i = 1; i <= cnt; i++)
		// Cvx[i].print();
	long long t = Calc(cnt);
	printf ("%lld.%c\n", t >> 1, t & 1 ? '5' : '0');
}

