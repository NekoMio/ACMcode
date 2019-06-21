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

int MOD;

long long pow_mod(long long a, int b)
{
	long long ans = 1;
	while(b)
	{
		if (b & 1)
			ans = ans * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return ans;
}

int main()
{
	freopen("theory.in", "r", stdin);
	freopen("theory.out", "w", stdout);
	int x = read(), m = read();
	MOD = read();
	if (MOD < 1000)
	{
		for (int i = 1; i; i++)
		{
			int k = pow_mod(i, i);
			if (((long long)k * k % MOD + (long long)pow_mod(i, m)) % MOD == x)
			{
				printf ("%d\n", i);
				break;
			}
		}
	}
	else if (m == 0)
	{
		x = (x - 1 + MOD) % MOD;
		int t = (MOD - 1) / 2;
		for (int i = t; i >= 1; i--)
		{
			int k = pow_mod(i, i);
			if ((long long)k * k % MOD == x)
			{
				printf ("%d\n", i);
				break;
			}
		}
	}
	else
	{
		for (int i = 1; i; i++)
		{
			int k = pow_mod(i, i);
			if (((long long)k * k % MOD + (long long)pow_mod(i, m)) % MOD == x)
			{
				printf ("%d\n", i);
				break;
			}
		}
	}
	// while (1);
}
