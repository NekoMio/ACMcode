#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline long long read()
{
	long long x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
long long mult(long long a, long long b, long long P)
{
	a %= P, b %= P;
	long long ans = 0;
	while (b)
	{
		if (b & 1) ans = (ans + a) % P;
		b >>= 1;
		a = (a + a) % P;
	}
	return ans;
}
long long pow_mod(long long a, long long b, long long P)
{
	long long ans = 1;
	while (b)
	{
		if (b & 1) ans = mult(ans, a, P);
		b >>= 1;
		a = mult(a, a, P);
	}
	return ans;
}
long long exgcd(long long a, long long b, long long &x, long long &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	long long ret = exgcd(b, a % b, x, y);
	long long tmp = x;
	x = y;
	y = tmp - a / b * y;
	return ret;
}
long long Inv(long long x, long long N)
{
	long long a, b;
	exgcd(x, N, a, b);
	return (a % N + N) % N;
}
int main()
{
	int T = read();
	while (T--)
	{
		long long c1 = read(), c2 = read(), e1 = read(), e2 = read(), N = read(), x, y;
		exgcd(e1, e2, x, y); 
		if (x < 0) x = -x, c1 = Inv(c1, N);
		if (y < 0) y = -y, c2 = Inv(c2, N);
		printf ("%lld\n", mult(pow_mod(c1, x, N), pow_mod(c2, y, N), N));
	}
}

