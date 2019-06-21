#pragma GCC optimize("O3")
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n;
struct edge
{
	int END, next;
}v[500005 << 1];
int first[500005], p;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
int dep[500005],size[500005],son[500005],fa[500005],ID[500005],top[500005];
int Index;
void dfs1(int rt, int faa, int Dep)
{
	size[rt] = 1;
	dep[rt] = Dep;
	fa[rt] = faa;
	son[rt] = 0;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if(v[i].END == faa) continue;
		dfs1(v[i].END, rt, Dep + 1);
		size[rt] += size[v[i].END];
		if(size[v[i].END] > size[son[rt]])
			son[rt] = v[i].END;
	}
}
void dfs2(int rt, int t)
{
	top[rt] = t;
	ID[rt] = ++Index;
	if(son[rt]) dfs2(son[rt],t);
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if(v[i].END == fa[rt] || v[i].END == son[rt]) continue;
		dfs2(v[i].END, v[i].END);
	}
}
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
bool mark[500005 << 2], flag[500005 << 2];
void Pushdown(int rt)
{
	if(flag[rt])
	{
		flag[rt << 1] = flag[rt << 1 | 1] = flag[rt];
		mark[rt << 1] = mark[rt << 1 | 1] = 1;
		flag[rt] = 0;
	}
}
void Update(int L, int R, int l, int r, int rt)
{
	if(L <= l && R >= r)
	{
		mark[rt] = 1;
		flag[rt] = 1;
		return;
	}
	Pushdown(rt);
	int m = l + r >> 1;
	if(L <= m) Update(L,R,lch);
	if(R > m) Update(L,R,rch);
}
bool Query(int x, int l, int r, int rt)
{
	if(l == r)
		return mark[rt];
	int m = l + r >> 1;
	Pushdown(rt);
	if(x <= m) return Query(x, lch);
	else return Query(x, rch);
}
int Update(int a, int b)
{
	while(top[a] != top[b])
	{
		if(dep[top[a]] < dep[top[b]])
			swap(a, b);
		Update(ID[top[a]], ID[a], 1, n, 1);
		a = fa[top[a]];
	}
	if(dep[a] > dep[b])
		swap(a, b);
	Update(ID[a], ID[b], 1, n, 1);
	return a;
}
int main()
{
	memset(first,-1,sizeof(first));
	int m, s;
	scanf("%d%d%d",&n,&m,&s);
	int a,b;
	for (int i = 1; i <= n - 1; i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	dfs1(1,0,1);
	dfs2(1,0);
	int d;
	long long ans = 0;;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d", &d);
		if(!Query(ID[d], 1, n, 1))
		{
			int lca = Update(s, d);
			ans += (dep[s] + dep[d] - 2 * dep[lca]);
			s = d;
		}
	}
	printf("%lld\n",ans);
}