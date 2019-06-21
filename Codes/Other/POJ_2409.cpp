#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

long long pow_mod(long long a, int b)
{
	long long ans = 1;
	while (b)
	{
		if (b & 1) ans = ans * a ;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

int main()
{
	int c, s;
	while ((c = read()) && (s = read()))
	{
		long long ans = 0;
		for (int i = 0; i < s; i++)
			ans += pow_mod(c, gcd(s, i));
		if (s & 1)
			ans += s * pow_mod(c, s / 2 + 1);
		else 
			ans += s / 2 * (pow_mod(c, s / 2) + pow_mod(c, s / 2 + 1));
		ans = ans / 2 / s;
		printf ("%lld\n", ans);
	}
}