#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
	int END, next;
}v[1000005];
int first[500005], p;
int f[500005][20];
int Dep[500005];
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
void dfs(int rt, int fa, int dep)
{
	f[rt][0] = fa;
	Dep[rt] = dep;
	for (int i = 1; i <= 19; i++)
		f[rt][i] = f[f[rt][i - 1]][i - 1];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END != fa)
			dfs(v[i].END, rt, dep + 1);
	}
}
int Get_Lca(int a, int b)
{
	if (Dep[a] < Dep[b])
		swap(a, b);
	int d = Dep[a] - Dep[b];
	for (int i = 19; i >= 0; i--)
		if (d & (1 << i))
			d -= (1 << i), a = f[a][i];
	if (a == b) return a;
	for (int i = 19; i >= 0; i--)
		if (f[a][i] != f[b][i])
			a = f[a][i], b = f[b][i];
	return f[a][0];
}
int DIS(int a, int b)
{
	int S = Get_Lca(a, b);
	return Dep[a] - Dep[S] + Dep[b] - Dep[S];
}
int main()
{
	int n, m;
	memset (first, -1, sizeof (first));
	scanf ("%d%d", &n, &m);
	int a, b;
	for (int i = 1; i < n; i++)
	{
		scanf ("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
	dfs(1, 0, 0);
	int c;
	for (int i = 1; i <= m; i++)
	{
		scanf ("%d%d%d", &a, &b, &c);
		int LCA1 = Get_Lca(a, b);
		int LCA2 = Get_Lca(a, c);
		int LCA3 = Get_Lca(c, b);
		if (LCA1 == LCA2)
		{
			int a1 = DIS(a, LCA3);
			int b1 = DIS(b, LCA3);
			int c1 = DIS(c, LCA3);
			printf ("%d %d\n", LCA3, a1 + b1 + c1);
		}
		else if (LCA1 == LCA3)
		{
			int a1 = DIS(a, LCA2);
			int b1 = DIS(b, LCA2);
			int c1 = DIS(c, LCA2);
			printf ("%d %d\n", LCA2, a1 + b1 + c1);
		}
		else if (LCA2 == LCA3)
		{
			int a1 = DIS(a, LCA1);
			int b1 = DIS(b, LCA1);
			int c1 = DIS(c, LCA1);
			printf ("%d %d\n", LCA1, a1 + b1 + c1);
		}
	}
}
