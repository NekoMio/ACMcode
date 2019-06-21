#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define INF 0x3f3f3f3f
const int N = 100005;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
struct edge
{
	int next, END, v;
}v[N << 1];
int first[N], p;
void add(int a, int b, int c)
{
	v[p].END = b;
	v[p].next = first[a];
	v[p].v = c;
	first[a] = p++;
}
int val[N], ans[N];
struct data
{
	int S, E, v, id;
	bool operator < (const data &d) const
	{
		return v < d.v;
	}
}e[N];
bool flag[N];
int n, m, s;
int father[N];
int find(int x)
{
	if (father[x] != x) father[x] = find(father[x]);
	return father[x];
}
int dep[N], top[N], son[N], size[N], fa[N], id[N], Index, pre[N];
void dfs1(int rt, int f, int Dep)
{
	dep[rt] = Dep;
	fa[rt] = f;
	size[rt] = 1;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == f) continue;
		dfs1(v[i].END, rt, Dep + 1);
		val[v[i].END] = v[i].v;
		size[rt] += size[v[i].END];
		if (size[v[i].END] > size[son[rt]]) son[rt] = v[i].END;
	}
}
void dfs2(int rt, int T)
{
	top[rt] = T;
	id[rt] = ++Index;
	pre[Index] = rt;
	if (son[rt]) dfs2(son[rt], T);
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa[rt] || v[i].END == son[rt]) continue;
		dfs2(v[i].END, v[i].END);
	}
}
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
struct Seg_Tree1
{
	int Max[N << 2];
	void Pushup(int rt)
	{
		Max[rt] = max(Max[rt << 1], Max[rt << 1 | 1]);
	}
	void Buildtree(int l, int r, int rt)
	{
		if (l == r)
		{
			Max[rt] = val[pre[l]];
			return;
		}
		int m = l + r >> 1;
		Buildtree(lch);
		Buildtree(rch);
		Pushup(rt);
	}
	int Query(int L, int R, int l, int r, int rt)
	{
		if (L <= l && R >= r)
			return Max[rt];
		int m = l + r >> 1; 
		int ans = 0;
		if (L <= m) ans = max(ans, Query(L, R, lch));
		if (R > m) ans = max(ans, Query(L, R, rch));
		return ans;
	}
}root;
struct Seg_Tree2
{
	int Min[N << 2], lazy[N << 2];
	void Buildtree(int l, int r, int rt)
	{
		Min[rt] = INF, lazy[rt] = INF;
		if (l == r) return;
		int m = l + r >> 1;
		Buildtree(lch);
		Buildtree(rch);
	}
	void Pushdown(int rt)
	{
		if (lazy[rt] != INF)
		{
			lazy[rt << 1] = min(lazy[rt << 1], lazy[rt]);
			lazy[rt << 1 | 1] = min(lazy[rt << 1 | 1], lazy[rt]);
			Min[rt << 1] = min(Min[rt << 1], lazy[rt]);
			Min[rt << 1 | 1] = min(Min[rt << 1 | 1], lazy[rt]);
			lazy[rt] = INF;
		}
	}
	void Update(int L, int R, int c, int l, int r, int rt)
	{
		if (L <= l && R >= r)
		{
			Min[rt] = min(Min[rt], c);
			lazy[rt] = min(lazy[rt], c);
			return;
		}
		int m = l + r >> 1;
		Pushdown(rt);
		if (L <= m) Update(L, R, c, lch);
		if (R > m) Update(L, R, c, rch);
	}
	int Query(int x, int l, int r, int rt)
	{
		if (l == r)
			return Min[rt];
		int m = l + r >> 1;
		Pushdown(rt);
		if (x <= m) return Query(x, lch);
		else return Query(x, rch);
	}
}rt;
void Update(int x, int y, int c)
{
	while(top[x] != top[y])
	{
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		rt.Update(id[top[x]], id[x], c, 1, n, 1);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	if(x != y) rt.Update(id[x] + 1, id[y], c, 1, n, 1);
}
int Query(int x, int y)
{
	int ans = 0;
	while (top[x] != top[y])
	{
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		ans = max(ans, root.Query(id[top[x]], id[x], 1, n, 1));
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	if(x != y) ans = max(ans, root.Query(id[x] + 1, id[y], 1, n, 1));
	return ans;
}
int main()
{
//	freopen("weight.in", "r", stdin);
//	freopen("weight.out", "w", stdout);
	n = read(), m = read(), s = read();
	int a, b, c;
	memset (first, -1, sizeof (first));
	for (int i = 1; i <= m; i++)
	{
		a = read(), b = read(), c = read();
		e[i].S = a, e[i].E = b, e[i].v = c, e[i].id = i;
	}
	sort(e + 1, e + m + 1);
	for (int i = 1; i <= n; i++) father[i] = i;
	int t1 = 0;
	for (int i = 1; i <= m; i++)
	{
		if (find(e[i].S) != find(e[i].E))
		{
			father[find(e[i].S)] = find(e[i].E);
			t1++;
			flag[i] = 1;
			add(e[i].S, e[i].E, e[i].v);
			add(e[i].E, e[i].S, e[i].v);
			if (t1 == n - 1) break;
		}
	}
	dfs1(1, 0, 0);
	dfs2(1, 0);
	root.Buildtree(1, n, 1);
	rt.Buildtree(1, n, 1);
	for (int i = 1; i <= m; i++)
		if (!flag[i])
			Update(e[i].S, e[i].E, e[i].v);
	for (int i = 1; i <= m; i++)
	{
		if (find(e[i].S) != find(1))
		{
//			printf ("0 ");
		}
		else
		{
			if (flag[i])
			{
				a = e[i].S, b = e[i].E;
				if (a == fa[b]) swap(a, b);
				ans[e[i].id] = rt.Query(id[a], 1, n, 1);
				ans[e[i].id] = (ans[e[i].id] == INF ? -1: ans[e[i].id] - 1);
//				printf ("%d ", ans == INF ? -1: ans - 1);
			}
			else
			{
				ans[e[i].id] = Query(e[i].S, e[i].E) - 1;
//				printf ("%d ", Query(e[i].S, e[i].E) - 1);
			}
		}
	}
	for (int i = 1; i <= m; i++)
		printf ("%d ", ans[i]);
}
