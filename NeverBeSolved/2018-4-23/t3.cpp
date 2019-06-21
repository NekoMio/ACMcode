#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
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
struct edge
{
	int a, b, c;
}d[100005];
int mp[45][45];
int a[45][45];
long long gauss(int n)
{
    int ans = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            a[i][j] = (a[i][j] + MOD) % MOD;
    for (int i = 1; i <= n; i++)
    {
        if (a[i][i] == 0)
		{
			for (int j = i + 1; j <= n; j++)
			{
				if (a[j][i])
				{
					for (int k = 1; k <= n + 1; k++)
						swap(a[i][k], a[j][k]);
					ans = (MOD - ans) % MOD;
					break;
				}
			}
		}
		int z = pow_mod(a[i][i], MOD - 2);
		for (int j = i + 1; j <= n; j++) if (a[j][i])
		{
			int t = 1ll * a[j][i] * z % MOD;
			for (int k = i; k <= n + 1; k++)
			{
				a[j][k] = (a[j][k] - 1ll * a[i][k] * t % MOD + MOD) % MOD;
			}
		}
        ans = 1ll * ans * a[i][i] % MOD;
    }
    return ans;
}
void add(int A, int B, int c)
{
	a[A][A] += c, a[B][B] += c;
	a[A][B] -= c, a[B][A] -= c;
}
int C[850][850], X[850];
void Gauss(int n)
{
	for (int i = 1; i <= n; i++)
	{
		if (C[i][i] == 0)
		{
			for (int j = i + 1; j <= n; j++)
			{
				if (C[j][i])
				{
					for (int k = 1; k <= n + 1; k++)
						swap(C[i][k], C[j][k]);
					break;
				}
			}
		}
		int z = pow_mod(C[i][i], MOD - 2);
		for (int j = i + 1; j <= n; j++) if (C[j][i])
		{
			int t = 1ll * C[j][i] * z % MOD;
			for (int k = i; k <= n + 1; k++)
			{
				C[j][k] = (C[j][k] - 1ll * C[i][k] * t % MOD + MOD) % MOD;
			}
		}
	}
	for (int i = n; i >= 1; i--)
	{
		for (int j = n; j >= i + 1; j--)
		{
			C[i][n + 1] = (C[i][n + 1] - 1ll * C[i][j] * X[j] % MOD + MOD) % MOD;
		}
		X[i] = 1ll * C[i][n + 1] * pow_mod(C[i][i], MOD - 2) % MOD;
	}
}
int id[45][45];
int f[45][45];
int main()
{
	int n = read(), m = read(), G = read(), B = read();
	for (int i = 1; i <= m; i++)
		d[i].a = read(), d[i].b = read(), d[i].c = read();
	int T = n * (n + 1) / 2;
	for (int t1 = 1; t1 <= n; t1++) for (int t2 = 1; t2 + t1 <= n + 1; t2++)
	{
		memset (a, 0, sizeof (a));
		for (int i = 1; i <= m; i++)
		{
			if (d[i].c == 1) add(d[i].a, d[i].b, 1);
			if (d[i].c == 2) add(d[i].a, d[i].b, t1);
			if (d[i].c == 3) add(d[i].a, d[i].b, t2);
		}
		f[t1][t2] = gauss(n - 1);
	}
	int tot = 0;
	for (int t1 = 1; t1 <= n; t1++) for (int t2 = 1; t2 + t1 <= n + 1; t2++)
	{
		tot++;
		int T1 = 1, cnt = 0;
		for (int j = 0; j < n; j++)
		{
			int T2 = 1;
			for (int k = 0; k + j < n; k++)
			{
				C[tot][++cnt] = 1ll * T1 * T2 % MOD;
				T2 = 1ll * T2 * t2 % MOD;
			}
			T1 = 1ll * T1 * t1 % MOD;
		}
		C[tot][++cnt] = f[t1][t2];
	}
	int cnt = 0;
	for (int j = 0; j < n; j++)
		for (int k = 0; k + j < n; k++)
			id[j][k] = ++cnt;
	Gauss(T);
	int ans = 0;
	for (int i = 0; i <= G; i++)
		for (int j = 0; j <= B; j++)
			ans = (ans + X[id[i][j]]) % MOD;
	printf ("%d\n", ans);
}
