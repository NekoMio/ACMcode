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
const int N = 1e5 + 5;
struct edge
{
	int END, next;
}v[N << 1];
int first[N], p;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
int du[N];
double f[N], g[N];
double ans[N];
void dfs1(int rt, int fa)
{
	f[rt] += du[rt];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dfs1(v[i].END, rt);
		f[rt] += f[v[i].END];
	}
}
void dfs2(int rt, int fa)
{
	if (rt != 1) g[rt] = g[fa] + f[fa] - f[rt];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dfs2(v[i].END, rt);
	}
}
void dfs3(int rt, int fa, double Dep)
{
	ans[rt] = Dep;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dfs3(v[i].END, rt, Dep + g[v[i].END]);
	}
}
int main()
{
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	int n = read(), a, b;
	memset (first, -1, sizeof (first));
	for (int i = 1; i < n; i++)
	{
		a = read(), b = read();
		add(a, b);du[a]++;
		add(b, a);du[b]++;
	}
	dfs1(1, 0);
	dfs2(1, 0);
	dfs3(1, 0, 1);
	for (int i = 1; i <= n; i++)
		printf ("%.3lf\n", ans[i]);
//	while (1);
}
