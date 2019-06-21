#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int MOD = 998244353;
const int MAXN = 100005;
long long bin[MAXN];
long long f[MAXN], Inv[MAXN];

long long C(int n, int m)
{
	if (n < m) return 0;
	return f[n] * Inv[m] % MOD * Inv[n - m] % MOD;
}

long long pow_mod(long long a, int b)
{
	long long ans = 1;
	while(b)
	{
		if (b & 1) ans = ans * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return ans;
}

int main()
{
	freopen("diyiti.in", "r", stdin);
	freopen("diyiti.out", "w", stdout);
	int n, k, b;
	scanf ("%d%d%d", &n, &b, &k);
	bin[0] = 1;
	for (int i = 1; i <= n; i++) bin[i] = bin[i - 1] * b % MOD;
	f[0] = 1;
	for (int i = 1; i <= n; i++) f[i] = f[i - 1] * i % MOD;
	Inv[n] = pow_mod(f[n], MOD - 2);
	for (int i = n - 1; i >= 0; i--) Inv[i] = Inv[i + 1] * (i + 1) % MOD;
	long long Ans = 0;
	for (int i = 1; i <= n; i++)
		Ans = (Ans + C(i, k) * bin[i] % MOD) % MOD;
	printf ("%lld\n", Ans);
}