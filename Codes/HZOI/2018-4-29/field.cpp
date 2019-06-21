#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cassert>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 100005;
struct data
{
	int l, r;
	bool operator < (const data &a) const 
	{
		return l == a.l ? r < a.r : l < a.l;
	}
}a[MAXN];
long long gcd(long long a, long long b)
{
	return b == 0 ? a : gcd(b, a % b);
}
struct Fc
{
	long long a, b;
	bool operator < (const Fc &c) const 
	{
		return 1ll * a * c.b < 1ll * b * c.a;
	}
	void Upd()
	{
		long long g = gcd(a, b);
		if (g != 0)
			a /= g, b /= g;
	}
	void print()
	{
		printf ("%lld/%lld\n", a, b);
	}
}Ans;
int n;
bool Judge(double mid)
{
	double S = 0;
	for (int i = 1; i <= n; i++)
	{
		if (S <= a[i].l)
		{
			if (a[i].l + mid > a[i].r) return 0;
			S = a[i].l + mid;
		}
		else
		{
			if (S + mid > a[i].r) return 0;
			S = S + mid;
		}
	}
	return 1;
}
int main()
{
	int T = read();
	while (T--)
	{
		n = read();
		for (int i = 1; i <= n; i++)
		{
			a[i].l = read(), a[i].r = read();
			// if (a[i].l >= a[i].r) printf ("%d\n", i);
			// assert(a[i].l < a[i].r);
		}
		sort(a + 1, a + n + 1);
		double l = 0, r = 1e9, ans;
		while (r - l > 1e-10)
		{
			double mid = (l + r) / 2;
			if (Judge(mid)) ans = mid, l = mid;
			else r = mid;
		}
		// printf ("%.5f\n", ans);
		for (int i = 1; i <= n; i++)
		{
			double z = i * ans;
			if (fabs(z - round(z)) <= 1e-5)
			{
				Ans.a = round(z), Ans.b = i;
				// break;
			}
		}
		Ans.Upd();
		Ans.print();
	}
}
