#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define sqr(_) ((_)*(_))
struct Point
{
	double x, y, z;
	Point() {}
	Point(double _x, double _y, double _z): x(_x), y(_y), z(_z) {}
	Point(const Point &_x): x(_x.x), y(_x.y), z(_x.z) {}
	Point operator - (const Point &_x) const
	{
		return Point(x - _x.x, y - _x.y, z - _x.z);
	}
};
struct Data
{
	Point x;
	double r;
	Data(){}
	Data(const Point &_x, double _r): x(_x), r(_r) {}
}C[55];
Point S, F, N;
Point Trans(const Point &x)
{
	double d = sqrt(x.x * x.x + x.y * x.y + x.z * x.z);
	return Point(x.x / d, x.y / d, x.z / d);
}
double Get_ans(double a, double b, double c)
{
	if (b * b - 4 * a * c < 0) return 1e70;
	double x1 = (-b + sqrt(sqr(b) - 4 * a * c)) / (2 * a);
	double x2 = (-b - sqrt(sqr(b) - 4 * a * c)) / (2 * a);
	if (x1 < 0 && x2 < 0) return 1e70;
	if (x1 < 0) return x2;
	if (x2 < 0) return x1;
	return min(x1, x2);
}
int n;
int Get_Point(const Point &S, const Point &F, Point &N, int Last)
{
	double k = 1e70, ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (i == Last) continue;
		double x = Get_ans(sqr(F.x) + sqr(F.y) + sqr(F.z), 2 * (F.x * (S.x - C[i].x.x) + F.y * (S.y - C[i].x.y) + F.z * (S.z - C[i].x.z)), sqr(S.x - C[i].x.x) + sqr(S.y - C[i].x.y) + sqr(S.z - C[i].x.z) - sqr(C[i].r));
		if (x < k)
			k = x, ans = i;
	}
	if (k > 1e60) return 0;
	N = Point(S.x + F.x * k, S.y + F.y * k, S.z + F.z * k);
	return ans;
}
void Get_Line(Point F, Point &s, Point &f, const Point &SS, const Point &FF)
{
	double k = -2 * (F.x * FF.x + F.y * FF.y + F.z * FF.z) / (sqr(FF.x) + sqr(FF.y) + sqr(FF.z));
	f = Point(k * FF.x + F.x, k * FF.y + F.y, k * FF.z + F.z);
	s = SS;
}
// struct
int main()
{
	scanf ("%d", &n);
	double x, y, z, r;
	for (int i = 1; i <= n; i++)
	{
		scanf ("%lf%lf%lf%lf", &x, &y, &z, &r);
		C[i] = Data(Point(x, y, z), r);
	}
	// Point S, E;
	scanf ("%lf%lf%lf%lf%lf%lf", &S.x, &S.y, &S.z, &F.x, &F.y, &F.z);
	F = Trans(F - S);
	int t = 0;
	int Last = 0;
	for (t = 1; t <= 10; t++)
	{
		int ID = Get_Point(S, F, N, Last);
		if (!ID) return 0;
		Get_Line(F, S, F, N, Trans(N - C[ID].x));
		Last = ID;
		printf ("%d ", ID);
	}
	if (t != 11) return 0;
	if (Get_Point(S, F, N, Last)) printf ("etc.\n");
	// while (1);
}