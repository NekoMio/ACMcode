#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1e9 + 7;
struct data
{
    int x, y;
    bool operator < (const data &a) const 
    {
	 	 return x == a.x ? y < a.y : x < a.x;
	}
	data(int x1 = 0, int y1 = 0)
	{
         x = x1, y = y1;
 	}
}a[5005];
long long pow_mod(long long a, long long b)
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
long long f[5005];
long long F[200005], Inv[200005];
long long C(int n, int m)
{
	if (n < m) return 0;
	return (F[n] * Inv[m] % MOD) * Inv[n - m] % MOD;
}
int main()
{

	int n, m, k;
	scanf ("%d%d%d", &n, &m, &k);
	F[0] = 1;
	for (int i = 1; i <= 200000; i++)
		F[i] = F[i - 1] * i % MOD;
	Inv[200000] = pow_mod(F[200000], MOD - 2);
	for (int i = 200000 - 1; i >= 0; i--)
		Inv[i] = Inv[i + 1] * (i + 1) % MOD; 
	for (int i = 1; i <= k; i++) scanf ("%d%d", &a[i].x, &a[i].y);
	k++;
	a[k].x = n, a[k].y = m;
	sort(a + 1, a + k + 1);
	for (int i = 1; i <= k; i++)
	{
		f[i] = C(a[i].x + a[i].y, a[i].x);
		for (int j = 1; j < i; j++)
			f[i] = (f[i] - f[j] * C(a[i].x - a[j].x + a[i].y - a[j].y, a[i].x - a[j].x) % MOD + MOD) % MOD;
	}
	printf ("%lld", f[k]);
}
