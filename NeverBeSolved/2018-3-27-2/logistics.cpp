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
const int MAXN = 205;
struct edge
{
	int END, next;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
int fa[MAXN];
int dis[MAXN][MAXN];
void dfs(int rt, int f)
{
	fa[rt] = f;
	// for (int i = 1; i <= 18; i++) f[rt][i] = f[f[rt][i - 1]][i - 1];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == f) continue;
		dfs(v[i].END, rt);
	}
}
void DFS(int rt, int f, int s)
{
	dis[s][rt] = dis[s][f] + 1;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == f) continue;
		DFS(v[i].END, rt, s);
	}
}
int D[MAXN];
int f[MAXN][MAXN];
int n, k;
int DP(int rt, int c)
{
	if (f[rt][c] != -1) return f[rt][c];
	f[rt][c] = 0;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa[rt]) continue;
		int tmp = 0x3f3f3f3f;
		for (int j = 1; j <= n; j++)
			if (dis[v[i].END][j] <= dis[v[i].END][c] && dis[rt][c] <= dis[rt][j])
				tmp = min(tmp, DP(v[i].END, j) + (j != c ? k : 0));
		f[rt][c] = f[rt][c] + tmp;
	}
	f[rt][c] += D[dis[rt][c]];
	return f[rt][c];
}
int main()
{
	n = read(), k = read();
	for (int i = 1; i <= n - 1; i++)
		D[i] = read();
	memset (first, -1, sizeof (first));
	for (int i = 1; i <= n - 1; i++)
	{
		int a = read(), b = read();
		add(a, b);
		add(b, a);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++)
	{
		DFS(i, 0, i);
		for (int j = 1; j <= n; j++)
			dis[i][j]--;
	}
	memset (f, -1, sizeof(f));
	int ans = 0x3f3f3f3f;
	for (int i = 1; i <= n; i++)
		ans = min(ans, DP(1, i) + k);
	printf ("%d\n", ans);
}