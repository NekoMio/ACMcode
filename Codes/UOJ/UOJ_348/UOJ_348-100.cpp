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
int v[25], w[25];
int F[22][(1 << 21) + 1], g[22][(1 << 21) + 1], Inv[(1 << 21) + 1];
long long pow_mod(long long a, int b)
{
	long long ans = 1;
	if (a == 0 && b == 0) return 0;
	while (b)
	{
		if (b & 1) ans = ans * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return ans;
}
int Num(unsigned int x)
{
	unsigned int tmp = x
					 - ((x >> 1) & 033333333333)
					 - ((x >> 2) & 011111111111);
	tmp = (tmp + (tmp >> 3)) & 030707070707;
	return tmp % 63;
}
int n, m, p;
bool vis[25];
void DFS(int rt, int S)
{
	vis[rt] = 1;
	for (int i = 1; i <= n; i++)
		if ((S & (1 << (i - 1))) && (v[rt] & (1 << (i - 1))) && (!vis[i]))
			DFS(i, S);
}
bool OK(int S)
{
	memset (vis, 0, sizeof (vis));
	int h = 0;
	for (int i = 1; i <= n; i++)
		if (S & (1 << (i - 1))) { h = i; break; }
	DFS(h, S);
	for (int i = 1; i <= n; i++)
		if ((S & (1 << (i - 1))) && !vis[i])
			return 0;
	return 1;
}
int Judge(int S)
{
	bool ok = 1;
	int ans = 0;
	if (Num(S) == 1) return 0;
	for (int i = 1; i <= n; i += 1)
	{
		if (S & (1 << (i - 1)))
		{
			if (Num(S & v[i]) & 1)
			{
				ok = 0;
				// break;
			}
			ans += w[i];
		}
	}
	if (ok == 1 && OK(S)) return 0;
	else return ans;
}
void FMT(int *a, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < (1 << n); j++)
			if (j & (1 << i))
				a[j] = (a[j] + a[j ^ (1 << i)]) % MOD;
}
void IFMT(int *a, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < (1 << n); j++)
			if (j & (1 << i))
				a[j] = (a[j] - a[j ^ (1 << i)] + MOD) % MOD;
}
int main()
{
	// freopen ("1.out", "w", stdout);
	n = read(), m = read(), p = read();
	for (int i = 0; i < m; i += 1)
	{
		int a = read(), b = read();
		v[a] |= (1 << (b - 1));
		v[b] |= (1 << (a - 1));
	}
	for (int i = 1; i <= n; i += 1)
		w[i] = read();
	// fprintf (stderr, "-------");
	int N = (1 << n) - 1;
	for (int i = 0; i <= N; i++)
	{
		g[Num(i)][i] = pow_mod(Judge(i), p);
		for (int j = 1; j <= n; j++) if (i & (1 << (j - 1))) Inv[i] += w[j];
		Inv[i] = pow_mod(pow_mod(Inv[i], p), MOD - 2);
		// printf ("%d %d\n", Num(i), g[Num(i)][i]);
	}
	F[0][0] = 1;
	for (int i = 0; i <= n; i++) FMT(g[i], n);
	FMT(F[0], n);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < i; j++)
			for (int k = 0; k <= N; k++)
				F[i][k] = (F[i][k] + 1ll * F[j][k] * g[i - j][k] % MOD) % MOD;
		IFMT(F[i], n);
		for (int k = 0; k <= N; k++)
			F[i][k] = 1ll * F[i][k] * Inv[k] % MOD;
		if (i == n) break;
		FMT(F[i], n);
	}
	printf ("%d\n", F[n][N]);
}
