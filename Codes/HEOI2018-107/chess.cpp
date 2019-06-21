#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int INF = 0x3f3f3f3f;
int a[15][15], b[15][15], n, m;
int vis[15][15];
unsigned int base = 31;
map<unsigned int, int> F[105];
unsigned int Get_Hash()
{
	unsigned int ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			ans = ans * base + (vis[i][j] != 0 ? 3 : 5);
	return ans;
}
bool Judge(int x, int y)
{
	for (int i = 1; i < x; i++)
		if (!vis[i][y])
			return 0;
	for (int i = 1; i < y; i++)
		if (!vis[x][i])
			return 0;
	return 1;
}
int Solve(int dep, int T)
{
	if (dep == T)
		return 0;
	unsigned int x = Get_Hash();
	if (F[dep].count(x)) return F[dep][x];
	int Max = -INF;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			if (!vis[i][j] && Judge(i, j))
			{
				vis[i][j] = (dep & 1) + 1;
//				OK[i + 1][j] = OK[i][j + 1] = 1;
				if (dep & 1)
					Max = max(Max, b[i][j] - Solve(dep + 1, T));
				else
					Max = max(Max, a[i][j] - Solve(dep + 1, T));
//				OK[i + 1][j] = OK[i][j + 1] = 0;
				vis[i][j] = 0;
			}
	}
	F[dep][x] = Max;
	return Max;
}
int main()
{
	// freopen ("chess.in", "r", stdin);
	// freopen ("chess.out", "w", stdout);
	n = read(), m = read();
	if (n == 10 && m == 1)
	{
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				a[i][j] = read();
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				b[i][j] = read();
		int Suma = 0, Sumb = 0;
		for (int i = 1; i <= n; i++)
			if (i & 1) Suma += a[i][1];
			else Sumb += b[i][1];
		printf ("%d\n", Suma - Sumb);
	}
	else
	{
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				a[i][j] = read();
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				b[i][j] = read();
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
		vis[1][1] = 1;
		printf ("%d\n", a[1][1] - Solve(1, n * m));
	}
	// fclose(stdin), fclose(stdout);
}
