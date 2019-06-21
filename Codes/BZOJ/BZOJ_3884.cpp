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
long long pow_mod(long long a, int b, int MOD)
{
	long long ans = 1;
	while (b)
	{
		if (b & 1) ans = ans * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return ans;
}
int phi(int x)
{
	int ans = x;
	for (int i = 2; i * i <= x; i++)
	{
		if (x % i == 0)
		{
			while (x % i == 0) x /= i;
			ans = ans - ans / i;
		}
	}
	if (x != 1) ans = ans - ans / x;
	return ans;
}
int Calc(int P)
{
	if (P == 1) return 0;
	int x = phi(P);
	return (int)pow_mod(2, Calc(x) + x, P);
}
int main()
{
	int T = read();
	while (T--)
	{
		int p = read();
		printf ("%d\n", Calc(p));
	}
}