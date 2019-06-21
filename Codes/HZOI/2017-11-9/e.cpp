#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long f[2005][2005];
long long bin[2005];
int main()
{
//	freopen ("e.in", "r", stdin);
//	freopen ("e.out", "w", stdout);
	int n, p;
	scanf ("%d%d", &n, &p);
	bin[0] = 1; 
	for (int i = 1; i <= n; i++) bin[i] = (bin[i - 1] << 1) % p;
	f[0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			f[i][j] = (f[i][j - 1] * 2 + f[i - 1][j - 1]) % p;
		for (int j = 1; j <= n; j++)
			f[i][j] = f[i][j] * (n - j + 1) % p;
	}
	long long ans = 0;
	for (int i = 1; i <= n; i++)
		ans = (ans + f[i][n] * f[i - 1][n] % p + f[i][n] * f[i][n] % p) % p;
	printf ("%d", ans * 2 % p);
//	fclose(stdin), fclose(stdout);
	return 0;
}

