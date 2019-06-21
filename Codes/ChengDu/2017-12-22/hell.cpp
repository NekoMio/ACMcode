#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1e5;
const int MOD = 1e9 + 7;
int f[MAXN + 5], Inv[MAXN + 5];

int pow_mod(long long a, int b)
{
	long long ans = 1;
	while (b)
	{
		if (b & 1) ans = ans * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return (int)ans;
}

int main()
{
	freopen("hell.in", "r", stdin);
	freopen("hell.out", "w", stdout);
	int a, b;
	f[0] = 1;
	for (int i = 1; i <= MAXN; i++) f[i] = 1ll * f[i - 1] * i % MOD;
	Inv[MAXN] = pow_mod(f[MAXN], MOD - 2);
	for (int i = MAXN - 1; i >= 0; i--) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % MOD;
	scanf ("%d%d", &a, &b);
	long long ans = 0;
	for (int i = 0; i <= b && i <= a; i++)
		ans = (ans + 1ll * (1ll * f[a] * Inv[i] % MOD) * Inv[a - i] % MOD) % MOD;
	printf ("%d\n", (int)ans);
}