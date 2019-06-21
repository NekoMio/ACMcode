#include <cstdio>
#include <cstring>
using namespace std;
int MOD = 1e9 + 7;
long long pow_mod(long long a, int b)
{
	long long ans = 1;
	while(b)
	{
		if(b & 1)
			ans = ans * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return ans;
}
long long f[1000005];
int main()
{
	int T;
	scanf("%d", &T);
	long long ans = 1;
	f[1] = 2;
	for (int i = 2; i <= 1000000; i++)
	{
		ans = (ans * (4 * i - 2) % MOD) * pow_mod(i + 1, MOD - 2) % MOD;
		f[i] = ans * (i + 1) % MOD;
	}
	while(T--)
	{
		int n;
		scanf("%d", &n);
		printf("%lld\n", f[n]);
	}
}