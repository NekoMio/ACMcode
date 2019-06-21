#include <bits/stdc++.h>
#define xx first
#define yy second
#define mp make_pair
#define pb push_back
#define mset(x, y) memset(x, y, sizeof x)
#define mcpy(x, y) memcpy(x, y, sizeof x)
using namespace std;

typedef long long LL;
typedef pair <int, int> pii;

inline int Read()
{
	int x = 0, f = 1, c = getchar();
	for (; !isdigit(c); c = getchar())
		if (c == '-')
			f = -1;
	for (;  isdigit(c); c = getchar())
		x = x * 10 + c - '0';
	return x * f;
}

const int MAXN = 2005;
const int mod = 1e9 + 7;

int n, S, T, dia, a, b, ans, g[MAXN], d[MAXN], f[MAXN][MAXN];
vector < int > adj[MAXN];

inline void Inc(int &x, int y) { x += y; if (x >= mod) x -= mod; }
inline void Dec(int &x, int y) { x -= y; if (x < 0) x += mod; }

inline void Dfs(int x, int c)
{
	d[x] = c ++;
	for (auto y : adj[x])
		if (y ^ g[x])
			g[y] = x, Dfs(y, c);
}

inline void Find()
{
	Dfs(1, 0);
	mset(g, 0);
	for (int i = 1; i <= n; i ++)
		if (d[i] > d[S])
			S = i;
	Dfs(S, 0);
	for (int i = 1; i <= n; i ++)
		if (d[i] > d[T])
			T = i;
	dia = d[a = T];
	for (int i = 1; i <= d[T] >> 1; i ++, a = g[a]);
	if (d[T] & 1)
		b = g[a];
}

inline void Dfs(int x, int g, int d, int l)
{
	for (auto y : adj[x])
		if (y ^ g)
			Dfs(y, x, d + 1, l);
	for (int i = d - l; i <= l - d; i ++)
	{
		f[x][i + 1002] = 1;
		for (auto y : adj[x])
			if (y ^ g)
				f[x][i + 1002] = 1LL * f[x][i + 1002] * (f[y][i + 1003] + f[y][i + 1001]) % mod;
	}
}

int main()
{
	freopen("n.in", "r", stdin);
    freopen("n.out", "w", stdout);
	n = Read();
	for (int i = 1, x, y; i < n; i ++)
		x = Read(), y = Read(), adj[x].pb(y), adj[y].pb(x);
	Find();
	if (dia & 1)
	{
		Dfs(a, b, 0, dia >> 1); Dfs(b, a, 0, dia + 1 >> 1);
		for (int i = -dia >> 1; i <= dia >> 1; i ++)
			Inc(ans, 1LL * f[a][i + 1002] * (f[b][i + 1003] + f[b][i + 1001]) % mod);
		mset(f, 0);
		Dfs(b, a, 0, dia >> 1); Dfs(a, b, 0, dia + 1 >> 1);
		for (int i = -dia >> 1; i <= dia >> 1; i ++)
			Inc(ans, 1LL * f[b][i + 1002] * (f[a][i + 1003] + f[a][i + 1001]) % mod);
		mset(f, 0);
		Dfs(a, b, 0, dia >> 1); Dfs(b, a, 0, dia >> 1);
		for (int i = -dia >> 1; i <= dia >> 1; i ++)
			Dec(ans, 2LL * f[a][i + 1002] * f[b][i + 1002] % mod);
		for (int i = -dia >> 1; i <= dia >> 1; i ++)
			Dec(ans, 1LL * f[a][i + 1002] * f[b][i + 1004] % mod);
		for (int i = -dia >> 1; i <= dia >> 1; i ++)
			Dec(ans, 1LL * f[b][i + 1002] * f[a][i + 1004] % mod);
		return printf("%d\n", ans), 0;
	}
	else
	{
		Dfs(a, 0, 0, dia >> 1);
		for (int i = -dia >> 1; i <= dia >> 1; i ++)
			Inc(ans, f[a][i + 1002]);
		return printf("%d\n", ans), 0;
	}
}
