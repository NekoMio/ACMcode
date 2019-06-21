#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;
inline long long read()
{
	long long x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MOD = 1e9 + 7;
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
int C[3005][3005];
int B[3005];
int Calc(long long n, int x)
{
	if (x == 0) return n % MOD;
	int ans = 0;
	for (int i = 1; i <= x + 1; i++)
	{
		ans = (ans + 1ll * C[x + 1][i] * B[x - i + 1] % MOD * pow_mod((n + 1) % MOD, i) % MOD) % MOD;
	}
	assert(ans != 0);
	return 1ll * ans * pow_mod(x + 1, MOD - 2) % MOD;
}
int main()
{
	freopen ("jzpkil.in", "r", stdin);
	freopen ("jzpkil.out", "w", stdout);
	for (int i = 0; i <= 3001; i++)
	{
		C[i][0] = 1;
		for (int j = 1; j <= i; j++)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
	}
	B[0] = 1;
	for (int i = 1; i <= 3000; i++)
	{
		for (int j = 0; j <= i - 1; j++)
			B[i] = (B[i] + 1ll * C[i + 1][j] * B[j] % MOD) % MOD;
		// assert(B[i] != 0);
		B[i] = (MOD - 1ll * B[i] * pow_mod(i + 1, MOD - 2) % MOD + MOD) % MOD;
	}
	int t = read();
	while (t--)
	{
		long long n = read();
		int x = read(), y = read();
		if (x == y)
		{
			printf ("%lld\n", 1ll * pow_mod(n % MOD, x) * Calc(n, x) % MOD);
		}
	}
}
