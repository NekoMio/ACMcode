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

const int MAXN = 305;
const int MAXM = 45155;

int n, mod, pw[MAXM], f[MAXN], g[MAXN][MAXN];

inline void Inc(int &x, int y) { x += y; if (x >= mod) x -= mod; }
inline void Dec(int &x, int y) { x -= y; if (x < 0) x += mod; }

int main()
{

	freopen("g.in", "r", stdin);
    freopen("g.out", "w", stdout);
	n = Read(), mod = Read();
	pw[0] = g[0][0] = 1;
	for (int i = 1; i <= n * (n + 1) >> 1; i ++)
		pw[i] = (pw[i - 1] << 1) % mod;
	for (int i = 0; i < n; i ++)
		for (int j = 0; j <= i; j ++)
			if (g[i][j])
			{
				Inc(g[i + 1][j + 1], g[i][j]);
				for (int k = i + 2; k <= n; k ++)
					Inc(g[k][j + 1], 1LL * g[i][j] * pw[(k - i - 2) * (k - i - 1) >> 1] % mod);
			}
	for (int i = 1; i <= n; i ++)
	{
		f[i] = pw[i * (i + 1) >> 1];
		for (int j = 1; j < i; j ++)
			Dec(f[i], 1LL * g[i][j] * f[j] % mod);
	}
	return printf("%d\n", f[n]), 0;
}
