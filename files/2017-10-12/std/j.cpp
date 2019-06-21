#include <bits/stdc++.h>
#define xx first
#define yy second
#define mp make_pair
#define pb push_back
#define mset(x, y) memset(x, y, sizeof x)
#define mcpy(x, y) memcpy(x, y, sizeof x)
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

inline int Read()
{
	int x = 0, f = 1, c = getchar();
	for (; !isdigit(c); c = getchar())
		if (c == '-')
			f = -1;
	for (; isdigit(c); c = getchar())
		x = x * 10 + c - '0';
	return x * f;
}

const int MAXN = 2005;
const int mod = 1e9 + 7;

int n, ans, st[MAXN << 1], f[MAXN][MAXN << 1];
pii a[MAXN];

int main()
{
	freopen("j.in", "r", stdin);
	freopen("j.out", "w", stdout);
	n = Read();
	for (int i = 0; i < n; i++)
		a[i].xx = Read(), a[i].yy = Read();
	sort(a, a + n);
	for (int i = 1, j = 0; i <= 4000; st[i++] = j)
		while (j < n && a[j].xx <= i)
			j++;
	for (int i = 4000; i; i--)
		f[n][i] = 1;
	for (int i = n - 1; ~i; i--)
		for (int j = 4000; j; j--)
		{
			f[i][j] = f[i + 1][j];
			if (a[i].xx <= j)
			{
				int p = a[i].yy, q = j;
				if (p > q)
					swap(p, q);
				f[i][j] = (f[i][j] + f[st[p]][q]) % mod;
			}
		}
	for (int i = 0; i < n; i++)
		ans = (ans + f[i + 1][a[i].yy]) % mod;
	return printf("%d\n", ans), 0;
}
