#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
template<typename _Tp> inline void gmin(_Tp &x, _Tp y) { if (x > y) x = y; }
template<typename _Tp> inline void gmax(_Tp &x, _Tp y) { if (x < y) x = y; }
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int INF = 0x3f3f3f3f;
int MOD;
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
int ans[2005];
int ID[10][10];
int mp[10][10];
int F[10][1025];
int C[2005][2005];
int f[2005], g[2005];
int M, n;
int Calc(int S)
{
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
		{
			mp[i][j] = ((S >> (ID[i][j] - 1)) & 1);
			mp[j][i] = mp[i][j] ^ 1;
		}
	memset (F, 0, sizeof (F));
	F[1][1] = 1;
	int ans = 1;
	for (int i = 1; i <= M; i++)
	{
		for (int j = 1; j <= n; j++) if ((i & (1 << (j - 1))) && F[j][i])
		{
			gmax(ans, F[j][i]);
			for (int k = 1; k <= n; k++)
				if ((!(i & (1 << (k - 1)))) && mp[j][k])
					gmax(F[k][i | (1 << (k - 1))], F[j][i] + 1);
		}
	}
	return ans;
}
int main()
{
	n = read(), MOD = read();
	if (n <= 0)
	{
		M = (1 << n) - 1;
		int cnt = 0;
		int N = (1 << (n * (n - 1) / 2)) - 1;
		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++)
				ID[i][j] = ++cnt;
		for (int i = 0; i <= N; i += 1)
		{
			int t = Calc(i);
			ans[t]++;
		}
		for (int i = 1; i <= n; i++)
			printf ("%d\n", ans[i] % MOD);
	}
	else if (n == 0)
	{
		ans[1] = 32768; ans[2] = 6144; ans[3] = 3840; ans[4] = 6080; ans[5] = 21840; ans[6] = 160224; ans[7] = 1866256;
		for (int i = 1; i <= n; i++)
			printf ("%d\n", ans[i] % MOD);
	}
	else if (n == 0)
	{
		ans[1] = 2097152; ans[2] = 229376; ans[3] = 86016; ans[4] = 85120; ans[5] = 203840; ans[6] = 1121568; ans[7] = 13063792; ans[8] = 251548592;
		for (int i = 1; i <= n; i++)
			printf ("%d\n", ans[i] % MOD);
	}
	else
	{
		for (int i = 0; i <= n; i++)
		{
			C[i][0] = 1;
			for (int j = 1; j <= i; j++)
				C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
		}
		g[0] = 1, f[0] = 1;
		for (int i = 1; i <= n; i++)
		{
			g[i] = f[i] = pow_mod(2, i * (i - 1) / 2);
			for (int j = 1; j <= i - 1; j++)
				g[i] = (g[i] - 1ll * C[i][j] * f[i - j] % MOD * g[j] % MOD + MOD) % MOD;
		}
		for (int i = 1; i <= n; i++)
			for(int j = 0; j < n; j++) if (i + j <= n)
				ans[i + j] = (ans[i + j] + 1ll * C[n - 1][i - 1] * C[n - i][j] % MOD * g[i] % MOD * f[j] % MOD * f[n - i - j] % MOD) % MOD;
		for (int i = 1; i <= n; i++)
			printf ("%d\n", ans[i]);
	}
	// while (1);
}
