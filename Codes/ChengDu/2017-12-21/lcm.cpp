#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

long long gcd(long long a, long long b)
{
	return b == 0 ? a : gcd(b, a % b);
}

int Calc(long long a, long long b)
{
	int m = b - a;
	long long Max = 0x3f3f3f3f3f3f3f3fll, ans = 0;
	for (int i = 1; i <= m; i++)
	{
		long long d = (a + i) * (b + i) / gcd(a + i, b + i);
		if (d < Max) 
			Max = d, ans = i;
	}
	return ans;
}

int main()
{
	freopen("lcm.in", "r", stdin);
	freopen("lcm.out", "w", stdout);
	long long a = read(), b = read();
	if (a == b) return printf ("1\n"), 0;
	if (a > b) swap(a, b);
	if (a * 2 < b)
	{
		int t = b - a;
		int ans = 0x3f3f3f3f;
		for (int i = 1; i * i <= t; i++)
			if (t % i == 0)
			{
				if (i > a) ans = min(ans, int(i - a));
				if (t / i > a) ans = min(ans, int(t / i - a));
			}
		printf ("%d\n", ans);
	}
	else
	{
		if (b > a * 2 - a / 2)
		{
			printf ("%d\n", int(a - 2 * (a * 2 - b)));
		}
		else
		{
			printf ("%d\n", Calc(a, b));
		}                                      
	}
}