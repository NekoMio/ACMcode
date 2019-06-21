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
const int MOD = 998244353;
char mp[55][55];
bool vis[55][55];
int C[55][55];
int ans, n, m, all;
int st[5000], top;
int nxtx(int x)
{
	if (x == n) return 1;
	return x + 1;
}
int nxty(int y)
{
	if (y == m) return 1;
	return y + 1;
}
bool Test(int x, int y)
{
	return (nxtx(x) == 1 && y == 1) || (x == 1 && nxty(y) == 1);
}
void Calc_Ans()
{
	int nowx = 1, nowy = 1;
	for (int i = 1; i <= top; i++)
	{
		if (st[i] == 1) nowx = nxtx(nowx);
		else nowy = nxty(nowy);
		if (mp[nowx][nowy])
		{
			ans = (ans + i) % MOD;
			break;
		}
	}
}
void DFS(int x, int y, int d = 1)
{
	if (d == all && Test(x, y))
	{
		Calc_Ans();
		return;
	}
	vis[x][y] = 1;
	if (!vis[nxtx(x)][y])
	{
		st[++top] = 1;
		DFS(nxtx(x), y, d + 1);
		top--;
	}
	if (!vis[x][nxty(y)])
	{
		st[++top] = 2;
		DFS(x, nxty(y), d + 1);
		top--;
	}
	vis[x][y] = 0;
}
int F[55][55], G[55][55];
int t[55][55], lst[55][55];
int Calc(int n, int m)
{
	int g = __gcd(n, m);
	int d = n * m / g;
	for (int i = 1; i < g; i++)
		if (__gcd(n, i) == 1 && __gcd(g - i, m) == 1)
		{
			int x = g - i;
			memset (t, 0, sizeof (t));
			memset (lst, 0, sizeof (lst));
			for (int j = 0; j < d && all; j++)
			{
				// memset (t, 0, sizeof (t));
				for (int k = 0; k <= i; k++)
					for (int l = 0; l <= x; l++)
					{
						lst[k][l] = t[k][l];
						t[k][l] |= mp[(j * i + k) % n][(x * j + l) % m];
					}
				if (t[0][0]) break;
				memset (F, 0, sizeof (F));
				memset (G, 0, sizeof (G));
				F[0][0] = 1;
				for (int k = 0; k <= i; k++)
					for (int l = 0; l <= x; l++)
					{
						if (k < i && !t[k + 1][l]) F[k + 1][l] = (F[k + 1][l] + F[k][l]) % MOD;
						if (l < x && !t[k][l + 1]) F[k][l + 1] = (F[k][l + 1] + F[k][l]) % MOD;
					}
				G[i][x] = 1;
				for (int k = i; k >= 0; k--)
					for (int l = x; l >= 0; l--)
					{
						if (k > 0 && !lst[k - 1][l]) G[k - 1][l] = (G[k - 1][l] + G[k][l]) % MOD;
						if (l > 0 && !lst[k][l - 1]) G[k][l - 1] = (G[k][l - 1] + G[k][l]) % MOD;
					}
				// for (int k = 0; k <= i; k++)
				// 	for (int l = 0; l <= x; l++)
				// 		printf ("%d%c", G[k][l], " \n"[l == x]);
				for (int k = 1; k <= i; k++)
					for (int l = 0; l <= x; l++)
						if (mp[(j * i + k) % n][(x * j + l) % m])
							ans = (ans + 1ll * F[k - 1][l] * G[k][l] % MOD * (j * g + k + l) % MOD) % MOD;
				for (int k = 0; k <= i; k++)
					for (int l = 1; l <= x; l++)
						if (mp[(j * i + k) % n][(x * j + l) % m])
							ans = (ans + 1ll * F[k][l - 1] * G[k][l] % MOD * (j * g + k + l) % MOD) % MOD;
				// printf ("%d\n", ans);
			}
		}
	return ans;
}
int main()
{
	int T = read();
	for (int i = 0; i <= 50; i++)
	{
		C[i][0] = 1;
		for (int j = 1; j <= i; j++)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
	}
	while (T--)
	{
		n = read(), m = read();
		all = n * m;
		ans = 0;
		for (int i = 0; i < n; i++)
		{
			scanf ("%s", mp[i]);
			for (int j = 0; j < m; j++)
				mp[i][j] -= '0';
		}
		if (n * m <= 0)
		{
			DFS(1, 1);
			printf ("%d\n", ans);
		}
		else
		{
			printf ("%d\n", Calc(n, m));
		}
	}
}
