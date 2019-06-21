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
const int MOD = 998244353;
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
int f[205][105];
int g[2][205];
int tmp[205], d[205], a[205];
signed main()
{
	// freopen ("faceless8.in", "r", stdin);
	// freopen ("faceless.out", "w", stdout);
	int n = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	int Q = read();
	for (int i = 1; i <= n; i++)
		f[i][a[i]] = 1;
	while (Q--)
	{
		int op = read();
		if (op == 0)
		{
			int id = read(), u = read(), v = read();
			int P = 1ll * u * pow_mod(v, MOD - 2) % MOD, q = (1 - P + MOD) % MOD;
			// printf ("%d %d\n", P, q);
			memset (tmp, 0, sizeof (tmp));
			for (int i = 1; i <= 100; i++)
			{
				tmp[i] = (tmp[i] + 1ll * f[id][i + 1] * P % MOD) % MOD;
				tmp[i] = (tmp[i] + 1ll * f[id][i] * q % MOD) % MOD;
			}
			tmp[0] = (1ll * f[id][1] * P % MOD + f[id][0]) % MOD;
			for (int i = 0; i <= 100; i++)
				f[id][i] = tmp[i];
		}
		else
		{
			int k = read();
			for (int i = 1; i <= k; i++)
				d[i] = read();
			memset(g, 0, sizeof (g));
			g[0][0] = 1;
			int t = 0;
			for (int j = 1; j <= k; j++)
			{
				t ^= 1;
				for (int l = 1; l <= k; l++)
				{
					g[t][l] = 1ll * f[d[j]][0] * g[t ^ 1][l] % MOD;
					g[t][l] = (g[t][l] + 1ll * ((1 - f[d[j]][0] + MOD) % MOD) * g[t ^ 1][l - 1] % MOD) % MOD;
				}
				g[t][0] = 1ll * f[d[j]][0] * g[t ^ 1][0] % MOD;
				// printf ("%d %d\n", g[t][1], f[d[j]][0]);
			}
			// for (int j = 1; j <= k; j++)
				// printf ("%d ", g[t][j]);
			// printf ("\n");
			for (int i = 1; i <= k; i++)
			{
				memset (tmp, 0, sizeof (tmp));
				int inv = pow_mod(f[d[i]][0], MOD - 2);
				int ans = tmp[0] = 1ll * g[t][0] * inv % MOD;
				if (f[d[i]][0] == 0)
				{
					ans = tmp[0] = g[t][1];
					for (int j = 1; j <= k - 1; j++)
					{
						tmp[j] = g[t][j + 1];
						ans = (ans + 1ll * tmp[j] * pow_mod(j + 1, MOD - 2) % MOD) % MOD;
					}
					printf ("%d ", ans);
					continue;
				}
				for (int j = 1; j <= k - 1; j++)
				{
					tmp[j] = 1ll * (g[t][j] - 1ll * (1 - f[d[i]][0] + MOD) * tmp[j - 1] % MOD + MOD) * inv % MOD;
					ans = (ans + 1ll * tmp[j] * pow_mod(j + 1, MOD - 2) % MOD) % MOD;
				}
				printf ("%lld ", 1ll * ans * (1 - f[d[i]][0] + MOD) % MOD);
			}
			printf ("\n");
		}
	}
	for (int i = 1; i <= n; i++)
	{
		int ans = 0;
		for (int j = 1; j <= 100; j++)
			ans = (ans + 1ll * f[i][j] * j % MOD) % MOD;
		printf ("%d ", ans);
	}
	printf ("\n");
}

