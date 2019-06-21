#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MOD = 1000000007;
long long pow_mod(long long a, int b)
{
	long long ans = 1;
	while (b)
	{
		if (b & 1)
			ans = ans * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return ans;
}
long long F[100005];
long long C(int a, int b)
{
	if (b > a)
		return 0;
	return F[a] * pow_mod(F[b] * F[a - b] % MOD, MOD - 2) % MOD;
}
long long Catalan(int n)
{
	return C(2 * n, n) * pow_mod(n + 1, MOD - 2) % MOD;
}
long long f[1005];
int main()
{
	int n, type;
	scanf("%d%d", &n, &type);
	F[0] = 1;
	for (int i = 1; i <= n; ++i)
	{
		F[i] = F[i - 1] * i % MOD;
	}
	if (type == 0)
	{
		long long ans = 0;
		for (int i = 0; i <= n; i += 2)
		{
			ans = (ans + (C(n, i) * C(i, i / 2) % MOD) * C(n - i, (n - i) / 2) % MOD) % MOD;
		}
		printf("%lld\n", ans);
	}
	else if (type == 1)
	{
		printf("%lld\n", Catalan(n / 2));
	}
	else if (type == 2)
	{
		f[0] = 1;
		for (int i = 2; i <= n; i += 2)
		{
			for (int j = 2; j <= i; j += 2)
			{
				f[i] = (f[i] + f[i - j] * Catalan(j / 2 - 1) * 4 % MOD) % MOD;
			}
		}
		printf("%lld\n", f[n]);
	}
	else
	{
		long long ans = 0;
		for (int i = 0; i <= n; i += 2)
		{
			ans = (ans + (C(n, i) * Catalan(i / 2) % MOD) * Catalan((n - i) / 2) % MOD) % MOD;
		}
		printf("%lld\n", ans);
	}
	//while (1);
}