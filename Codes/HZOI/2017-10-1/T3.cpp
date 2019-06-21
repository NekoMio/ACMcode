#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int w[2][1045][15], m, n1, n2, n;
int f[1055][1055];
void dfs(int rt, int Dep, int S)
{
	memset(f[rt], 0, sizeof(f[rt]));
	if (Dep == n - 1)
	{
		for (int i = 0; i <= n - 2; i++)
			if(S & (1 << i)) f[rt][1] += w[1][rt][i];
			else f[rt][0] += w[0][rt][i];
		return;
	}
	int last = 1 << (n - Dep - 1);
	dfs(rt << 1, Dep + 1, S), dfs(rt << 1 | 1, Dep + 1, S);
	for (int i = 0; i <= last >> 1; i++)
		for (int j = 0; j <= last >> 1; j++)
			f[rt][i + j] = max(f[rt][i + j], f[rt << 1][i] + f[rt << 1 | 1][j]);
	dfs(rt << 1, Dep + 1, S | (1 << Dep)), dfs(rt << 1 | 1, Dep + 1, S | (1 << Dep));
	for (int i = 0; i <= last >> 1; i++)
		for (int j = 0; j <= last >> 1; j++)
			f[rt][i + j] = max(f[rt][i + j], f[rt << 1][i] + f[rt << 1 | 1][j]);
}
int main()
{
	scanf ("%d%d", &n, &m);
	n1 = (1 << (n - 1)) - 1, n2 = 1 << (n - 1);
	for (int i = n2; i <= 2 * n2 - 1; i++)
		for (int j = n - 2; j >= 0; j--)
			scanf("%d", &w[1][i][j]);
	for (int i = n2; i <= 2 * n2 - 1; i++)
		for (int j = n - 2; j >= 0; j--)
			scanf("%d", &w[0][i][j]);
	dfs(1, 0, 0);
	int ans = 0;
	for (int i = 0; i <= m; i++)
		ans = max(ans, f[1][i]);
	printf("%d", ans);
}