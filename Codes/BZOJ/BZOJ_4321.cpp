#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 7777777;
long long f[1005];
int main()
{
	int n;
	scanf ("%d", &n);
	f[0] = 1, f[1] = 1, f[2] = 0, f[3] = 0;
	for (int i = 4; i <= n; i++)
		f[i] = ((f[i - 1] * (i + 1) % MOD - f[i - 2] * (i - 2) % MOD - f[i - 3] * (i - 5) % MOD + f[i - 4] * (i - 3) % MOD) % MOD + MOD) % MOD;
	printf ("%lld", f[n]);
}
