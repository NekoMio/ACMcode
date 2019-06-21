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
const int MAXN = 70005;
struct edge
{
	int END, next, v;
}e[MAXN << 1], v[MAXN << 1];
int gead[MAXN], p, first[MAXN], n;
void Add(int a, int b, int c)
{
	e[p].END = b;
	e[p].next = gead[a];
	e[p].v = c;
	gead[a] = p++;
}
void add(int a, int b, int c = 0)
{
	v[p].END = b;
	v[p].next = first[a];
	v[p].v = c;
	first[a] = p++;
}
struct Tree
{
	struct Node
	{
		Node *ch[2];
		long long Sum;
		int s;
		Node()
		{
			ch[0] = ch[1] = NULL;
			Sum = 0, s = 0;
		}
	}*root;
	Tree()
	{
		root = NULL;
	}
	void Update(int x, long long c, int l, int r, Node *rt)
	{
		rt->s++;
		rt->Sum += c;
		if (l == r) return;
		int mid = l + r >> 1;
		if (x <= mid)
		{
			if (rt->ch[0] == NULL) rt->ch[0] = new Node();
			Update(x, c, l, mid, rt->ch[0]);
		}
		else
		{
			if (rt->ch[1] == NULL) rt->ch[1] = new Node();
			Update(x, c, mid + 1, r, rt->ch[1]);
		}
	}
	void Update(Node *x, int l, int r, Node *rt)
	{
		if (rt->Sum == 0) rt->s++;
		rt->Sum += x->Sum;
		if (l == r) return;
		int mid = l + r >> 1;
		if (x->ch[0])
		{
			if (rt->ch[0] == NULL) rt->ch[0] = new Node();
			Update(x, l, mid, rt->ch[0]);
		}
		if (x->ch[1])
		{
			if (rt->ch[1] == NULL) rt->ch[1] = new Node();
			Update(x, mid + 1, r, rt->ch[1]);
		}
	}
	void Update(int x, long long c)
	{
		if (root == NULL) root = new Node();
		Update(x, c, 1, n, root);
	}
	void Update(Node *rt)
	{
		if (rt == NULL) return;
		if (root = NULL) root = new Node();
		Update(rt, 1, n, root);
	}
	long long Query(int L, int R, int l, int r, Node *rt)
	{
		if (rt == NULL) return 0;
		if (L <= l && R >= r) return rt->Sum;
		int mid = l + r >> 1;
		long long ans = 0;
		if (L <= mid) ans += Query(L, R, l, mid, rt->ch[0]);
		if (R > mid) ans += Query(L, R, mid + 1, r, rt->ch[1]);
		return ans;
	}
	long long Query(int L, int R)
	{
		return Query(L, R, 1, n, root);
	}
	int count(int L, int R, int l, int r, Node *rt)
	{
		if (rt == NULL) return 0;
		if (L <= l && R >= r) return rt->s;
		int mid = l + r >> 1;
		long long ans = 0;
		if (L <= mid) ans += count(L, R, l, mid, rt->ch[0]);
		if (R > mid) ans += count(L, R, mid + 1, r, rt->ch[1]);
		return ans;
	}
	int count(int L, int R)
	{
		return count(L, R, 1, n, root);
	}
}Trt[MAXN], TTrt[MAXN];
char op[10];
bool vis[MAXN];
int size[MAXN], Max[MAXN];
long long dis[MAXN];
int root, Sum;
void Get_root(int rt, int fa)
{
	size[rt] = 1;
	Max[rt] = 0;
	for (int i = gead[rt]; i != -1; i = e[i].next)
	{
		if (e[i].END == fa || vis[e[i].END]) continue;
		dis[e[i].END] = dis[rt] + e[i].v;
		Get_root(e[i].END, rt);
		size[rt] += size[e[i].END];
		Max[rt] = max(Max[rt], size[e[i].END]);
	}
	Max[rt] = max(Max[rt], Sum - size[rt]);
	if (Max[rt] < Max[root]) root = rt;
}
void DFS_ADD(int rt, long long dep, int fa, int x)
{
	Trt[x].Update(rt, dep);
	for (int i = gead[rt]; i != -1; i = e[i].next)
	{
		if (e[i].END == fa || vis[e[i].END]) continue;
		DFS_ADD(e[i].END, dep + e[i].v, rt, x);
	}
}
long long lenth(int x, int y);
void DFS_ADD1(int rt, int ss, int fa, int x)
{
	TTrt[x].Update(rt, lenth(ss, rt));
	for (int i = gead[rt]; i != -1; i = e[i].next)
	{
		if (e[i].END == fa || vis[e[i].END]) continue;
		DFS_ADD1(e[i].END, ss, rt, x);
	}
}
int f[MAXN];
long long len[MAXN][20];
int father[MAXN][20], Dep[MAXN];
long long lenth(int x, int y)
{
	if (Dep[x] < Dep[y]) swap(x, y);
	int d = Dep[x] - Dep[y];
	long long ans = 0;
	for (int i = 18; i >= 0; i--)
		if (d & (1 << i))
		{
			ans += len[x][i];
			x = father[x][i];
			d -= (1 << i);
		}
	if (x == y) return ans;
	for (int i = 18; i >= 0; i--)
		if (father[x][i] != father[y][i])
		{
			ans += len[x][i];
			ans += len[y][i];
			x = father[x][i];
			y = father[y][i];
		}
	return ans + len[x][0] + len[y][0];
}
void DFS(int rt, int fa, int dep)
{
	len[rt][0] = dep;
	father[rt][0] = fa;
	for (int i = 1; i <= 18; i++)
		father[rt][i] = father[father[rt][i - 1]][i - 1],
		len[rt][i] = len[rt][i - 1] + len[father[rt][i - 1]][i - 1];
	for (int i = gead[rt]; i != -1; i = e[i].next)
	{
		if (e[i].END == fa) continue;
		Dep[e[i].END] = Dep[rt] + 1;
		DFS(e[i].END, rt, e[i].v);
	}
}
void Build(int rt)
{
	vis[rt] = 1;
	DFS_ADD(rt, 0, 0, rt);
	for (int i = gead[rt]; i != -1; i = e[i].next)
	{
		if (vis[e[i].END]) continue;
		dis[e[i].END] = 0, Max[0] = Sum = size[e[i].END];
		root = 0;
		Get_root(e[i].END, 0);
		add(rt, root);
		f[root] = rt;
		DFS_ADD1(root, rt, 0, root);
		Build(root);
		// DFS_ADD(e[i].END, e[i].v, 0, rt);
	}
}
long long dis_tmp[MAXN], ans_tmp;
void DFS_tmp(int rt, int fa, int L, int R)
{
	if (L <= rt && R >= rt) ans_tmp += dis_tmp[rt];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dis_tmp[v[i].END] = dis_tmp[rt] + v[i].v;
		DFS_tmp(v[i].END, rt, L, R);
	}
}
int main()
{
	// freopen("tree_example_3.in", "r", stdin);
	// freopen("tree_example_3.out", "w", stdout);
	memset (gead, -1, sizeof (gead));
	memset (first, -1, sizeof (first));
	int m, type;
	n = read(), m = read(), type = read();
	if (n <= 5000)
	{
		for (int i = 1; i <= n - 1; i++)
		{
			int a = read(), b = read(), c = read();
			add(a, b, c);
			add(b, a, c);
		}
		long long lastans = 0;
		while (m--)
		{
			lastans *= type;
			scanf("%s", op);
			// int op = read();
			if (op[0] == 'm')
			{
				int x = read() ^ lastans, y = read() ^ lastans;
				v[(x - 1) << 1].v = y, v[(x - 1) << 1 | 1].v = y;
			}
			else
			{
				int L = read() ^ lastans, R = read() ^ lastans, x = read() ^ lastans;
				ans_tmp = 0, dis_tmp[x] = 0;
				DFS_tmp(x, 0, L, R);
				printf ("%lld\n", lastans = ans_tmp);
				lastans %= n;
			}
		}
	}
	else
	{
		for (int i = 1; i <= n - 1; i++)
		{
			int a = read(), b = read(), c = read();
			Add(a, b, c);
			Add(b, a, c);
		}
		DFS(1, 0, 0);
		root = 0, Sum = Max[0] = n;
		p = 0;
		Get_root(1, 0);
		Build(root);
		long long lastans = 0;
		while (m--)
		{
			lastans *= type;
			scanf ("%s", op);
			if (op[0] == 'm')
			{
				
			}
			else
			{
				int L = read() ^ lastans, R = read() ^ lastans, x = read() ^ lastans;
				long long ans = 0;
				int pre = 0;
				int z = x;
				while (x != 0)
				{
					ans += Trt[x].Query(L, R);
					ans -= TTrt[pre].Query(L, R);
					ans += lenth(z, x) * (Trt[x].count(L, R) - Trt[pre].count(L, R));
					pre = x;
					x = f[x];
				}
				printf ("%lld\n", lastans = ans);
				lastans %= n;
			}
		}
	}
}