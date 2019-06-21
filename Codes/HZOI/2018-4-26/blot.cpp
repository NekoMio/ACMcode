#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const double pi = acos(-1.);
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
#define sqr(_) ((_) * (_))
struct Point
{
	double x, y;
	Point(double _x = 0, double _y = 0): x(_x), y(_y) {}
	Point operator - (const Point &z)
	{
		return Point(x - z.x, y - z.y);
	}
	Point To_e()
	{
		double z = sqrt(sqr(x) + sqr(y));
		return Point(x / z, y / z);
	}
	double operator * (const Point &z)
	{
		return x * z.x + y * z.y;
	}
}S, a[35], c;
struct CirC
{
	Point x;
	double r;
	CirC() {}
	CirC(Point &z, double _r)
	{
		x = z, r = _r;
	}
}E;
struct line
{
	Point y;
	line() {}
	line(Point _y)
	{
		y = _y;
	}
};
// atan2(y, x)

double dis(const Point &x, const Point &y)
{
	return sqrt(sqr(x.x - y.x) + sqr(x.y - y.y));
}
void Calc(Point &x, Point s, double t1, double t)
{
	double k = atan2(x.y - s.y, x.x - s.x);
	if (k < 0) k += 2 * pi;
	double ad = (t / t1) - floor(t / t1);
	k += 2 * ad * pi;
	if (k > 2 * pi) k -= 2 * pi;
	double d = dis(x, s);
	x.x = cos(k) * d + s.x;
	x.y = sin(k) * d + s.y;
}
double Solve(double a, double b, double c)
{
	double z = sqr(b) - 4 * a * c;
	if (z < 0) return -1e70;
	double k = sqrt(z);
	if ((-b + k) / (2 * a) < 0 && (-b - k) / (2 * a) < 0) return -1e70;
	if ((-b + k) / (2 * a) < 0) return (-b - k) / (2 * a);
	if ((-b - k) / (2 * a) < 0) return (-b + k) / (2 * a);
	return min((-b + k) / (2 * a), (-b - k) / (2 * a));
}
int main()
{
	S.x = read(), S.y = read(), E.x.x = read(), E.x.y = read(), E.r = read();
	int n = read(), T1 = read(), T2 = read(), T = read();
	for (int i = 1; i <= n; i++)
		a[i].x = read(), a[i].y = read();
	for (int i = 1; i <= n; i++)
		c.x += a[i].x, c.y += a[i].y;
	c.x /= n, c.y /= n;
	Point zz = c;
	Calc(c, E.x, T1, T);
	for (int i = 1; i <= n; i++)
	{
		a[i].x += c.x - zz.x;
		a[i].y += c.y - zz.y;
		Calc(a[i], c, T2, T);
	}
	E.x = E.x - S;
	for (int i = 1; i <= n; i++)
		a[i] = a[i] - S;
	double cer = asin(E.r / dis(E.x, S));
	double f1 = 0, f2 = 0;
	int id1 = 0, id2 = 0;
	a[0] = E.x;
	for (int i = 1; i <= n; i++)
	{
		double t = Solve(sqr(a[i].x) + sqr(a[i].y), - 2 * a[i].x * E.x.x - 2 * a[i].y * E.x.y, sqr(E.x.x) + sqr(E.x.y) - sqr(E.r));
		if (t < 1 && t > -1e60) continue;
		double cc = acos(a[i].To_e() * E.x.To_e());
		if (cc > cer)
		{
			f2 = cer + 0.1;
			continue;
		}
		if (cc < -cer)
		{
			f1 = -cer - 0.1;
			continue;
		}
		if (cc > 0)
		{
			if (cc > f2)
			{
				f2 = cc;
				id2 = i;
			}
		}
		else
		{
			if (cc < f1)
			{
				f1 = cc;
				id1 = i;
			}
		}
	}
	double ans = 0;
	if (f2 < cer)
	{
		double zz = pi / 2 - cer;
		double t = Solve(sqr(a[id2].x) + sqr(a[id2].y), - 2 * a[id2].x * E.x.x - 2 * a[id2].y * E.x.y, sqr(E.x.x) + sqr(E.x.y) - sqr(E.r));
		Point tmp(a[id2].x * t - E.x.x,  a[id2].y * t - E.x.y);
		double cc = acos(tmp.To_e() * Point(-E.x.x, -E.x.y).To_e());
		ans += (zz - cc) * E.r;
	}
	if (f1 > -cer)
	{
		double zz = pi / 2 - cer;
		double t = Solve(sqr(a[id1].x) + sqr(a[id1].y), - 2 * a[id1].x * E.x.x - 2 * a[id1].y * E.x.y, sqr(E.x.x) + sqr(E.x.y) - sqr(E.r));
		Point tmp(a[id1].x * t - E.x.x,  a[id1].y * t - E.x.y);
		double cc = acos(tmp.To_e() * Point(-E.x.x, -E.x.y).To_e());
		ans += (zz - cc) * E.r;
	}
	printf ("%.2f", ans);
}
