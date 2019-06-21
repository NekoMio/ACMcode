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
const int MOD = 1e9 + 7;
long long pow_mod(long long a, int b)
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
int a[305];
long long f[2][90005], F[10000005], Inv[10000005];
long long C(int n, int m)
{
	if (n < m) return 0;
	return F[n] * Inv[n - m] % MOD * Inv[m] % MOD;
}
int main()
{
	int n = read(), m = read(), K = read();
	for (int i = 1; i <= m; i++)
		a[i] = read();
	F[0] = 1;
	for (int i = 1; i <= n + K; i++) F[i] = F[i - 1] * i % MOD;
	Inv[n + K] = pow_mod(F[n + K], MOD - 2);
	for (int i = n + K - 1; i >= 0; i--) Inv[i] = Inv[i + 1] * (i + 1) % MOD;
	int Max = 0;
	f[0][Max] = 1;
	int now = 0;
	for (int i = 1; i <= m; i++)
	{
		now ^= 1;
		memset (f[now], 0, sizeof (f[now]));
		Max += a[i];
		Max = min(Max, K);
		for (int j = 0; j <= Max; j++)
		{
			(f[now ^ 1][j] += f[now ^ 1][j - 1]) %= MOD;
			(f[now][j] += (f[now ^ 1][j] - ((j - a[i] - 1 < 0) ? 0 : f[now ^ 1][j - a[i] - 1]) + MOD) % MOD) %= MOD;
		}
	}
	long long ans = 0;
	if (n == m) ans = f[now][K];
	else
	{
		for (int i = 0; i <= Max; i++)
		{
			ans = (ans + f[now][i] * C(K - i + n - m - 1, n - m - 1) % MOD) % MOD;
		}
	}
	printf ("%lld\n", ans);
}