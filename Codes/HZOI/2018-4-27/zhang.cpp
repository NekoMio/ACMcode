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
int MOD;
int pow_mod(long long a, int b)
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
int F[500005];
int Calc(int n, int m)
{
	return 1ll * pow_mod(n, m - 1) * pow_mod(m, n - 1) % MOD;
}
int C(int n, int m)
{
	return 1ll * F[n] * pow_mod(1ll * F[m] * F[n - m] % MOD, MOD - 2) % MOD;
}
int main()
{
	int n = read(), K = read();
	MOD = read();
	F[0] = 1;
	for (int i = 1; i <= n; i++) F[i] = 1ll * F[i - 1] * i % MOD;
	printf ("%lld\n", 1ll * Calc(K, n - K) * C(n - 1, K - 1) % MOD);
}
