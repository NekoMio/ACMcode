// #pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
template<typename _Tp> inline void gmin(_Tp &x, _Tp y) { if (x > y) x = y; }
template<typename _Tp> inline void gmax(_Tp &x, _Tp y) { if (x < y) x = y; }
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int cnta, cntb, cntc;
const int INF = 0x3f3f3f3f;
const int MAXN = 1e5 + 5;
struct Point
{
	long long x, y;
	Point(int _x = 0, int _y = 0): x(_x), y(_y) {}
	long long operator * (const Point &a) { return x * a.y - a.x * y; }
	Point operator - (const Point &a) { return Point(x - a.x, y - a.y); }
	Point operator + (const Point &a) { return Point(x + a.x, y + a.y); }
	double getk() { return atan2(y, x); }
}a[MAXN], b[MAXN], Cvxa[MAXN], Cvxb[MAXN], cp, c[MAXN * 2], Cvxc[MAXN * 2];
#define sqr(_) ((_) * (_))
long long dis(const Point &x, const Point &y)
{
	return sqr(x.x - y.x) + sqr(x.y - y.y);
}
bool cmp(Point x, Point y)
{
	long long s = (x - cp) * (y - cp);
	if (s == 0) return dis(x, cp) < dis(y, cp);
	return s > 0;
}
int Run_Cvx(Point *a, Point *Cvx, int n)
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
	cp = a[1];
	sort(a + 2, a + n + 1, cmp);
	Cvx[++top] = a[1];
	for (int i = 2; i <= n; i++)
	{
		while (top > 1 && (Cvx[top] - Cvx[top - 1]) * (a[i] - Cvx[top]) <= 0) top--;
		Cvx[++top] = a[i];
	}
	return top;
}
double TB[MAXN], TA[MAXN], TC[MAXN * 2];
template<typename _ForwardIterator, typename _Tp>
_ForwardIterator minelower_bound(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __val)
{
	int __len = __last - __first;
	while (__len > 0)
	{
		int __half = __len >> 1;
		_ForwardIterator __middle = __first;
		__middle += __half;
		if (*__middle < __val)
		{
			__first = __middle + 1;
			__len = __len - __half - 1;
		}
		else
			__len = __half;
	}
    return __first;
}
bool Test(Point a, Point *b, int len, double *T)
{
	int k = minelower_bound(T + 2, T + len + 1, (a - b[1]).getk()) - T;
	if (k == 2 || k == len + 1) return 0;
	else if ((b[k] - a) * (b[k - 1] - a) > 0) return 0;
	else return 1;
}
int Minkowsk(Point *a, Point *b, int lena, int lenb)
{
	int lenc = 0;
	for (int i = 1, j = 1; i <= lena || j <= lenb; )
	{
		c[++lenc] = a[i] + b[j];
		Point nxta = a[i + 1] - a[i];
		Point nxtb = b[j + 1] - b[j];
		if (i <= lena && (nxta * nxtb >= 0 || j == lenb + 1))
			i++;
		else j++;
	}
	return lenc;
}
int main()
{
	// freopen ("test/war1.in", "r", stdin);
	// freopen ("war.out", "w", stdout);
	int n = read(), m = read(), q = read();
	for (int i = 1; i <= n; i++)
		a[i].x = read(), a[i].y = read();
	for (int i = 1; i <= m; i++)
		b[i].x = -read(), b[i].y = -read();
	cnta = Run_Cvx(a, Cvxa, n);
	Cvxa[cnta + 1] = Cvxa[1], Cvxa[cnta + 2] = Cvxa[2];
	cntb = Run_Cvx(b, Cvxb, m);
	Cvxb[cntb + 1] = Cvxb[1], Cvxb[cntb + 2] = Cvxb[2];
	int tmp = Minkowsk(Cvxa, Cvxb, cnta, cntb);
	cntc = Run_Cvx(c, Cvxc, tmp);
	for (int i = 2; i <= cntc; i++)
		TC[i] = (Cvxc[i] - Cvxc[1]).getk();
	while (q--)
	{
		int dx = read(), dy = read();
		if (Test(Point(dx, dy), Cvxc, cntc, TC)) printf ("1\n");
		else printf ("0\n");
	}
}
