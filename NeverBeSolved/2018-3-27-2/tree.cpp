#pragma GCC optimize("O2")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 100005;
int t[MAXN], ID;
map<int, int> H;
struct edge
{
	int END, next;
}v[MAXN << 1];
int first[MAXN], p;
void Add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
struct Node
{
	Node *ch[2];
	int Sum;
	#define sum(_) ((_) ? (_)->Sum : 0)
	Node()
	{
		ch[0] = ch[1] = NULL;
		Sum = 0;
	}
	void Pushup()
	{
		Sum = sum(ch[0]) + sum(ch[1]);
	}
};
int N;
struct Chairman_Tree
{
	Node *root;
	Chairman_Tree()
	{
		root = NULL;
	}
	void Update(int x, int c, int l, int r, Node *rt)
	{
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
	inline void Update(int x, int c)
	{
		if (root == NULL) root = new Node();
		Update(x, c, 1, N, root);
	}
	int Query(int L, int R, int l, int r, Node *rt)
	{
		if (rt == NULL) return 0;
		if (L <= l && R >= r) 
			return rt->Sum;
		int mid = l + r >> 1;
		int ans = 0;
		if (L <= mid) ans += Query(L, R, l, mid, rt->ch[0]);
		if (R > mid) ans += Query(L, R, mid + 1, r, rt->ch[1]);
		return ans;
	}
	inline int Query(int l, int r)
	{
		return Query(l, r, 1, N, root);
	}
}rt[MAXN * 3];
#define lowbit(_) ((_) & (-_))
int n, Q;
void add(int x, int c, int z)
{
	rt[c].Update(x, z);
}
int Query(int l, int r, int c)
{	
	return rt[c].Query(l, r);
}
int dep[MAXN], fa[MAXN], size[MAXN], top[MAXN], id[MAXN], son[MAXN], Index;
void DFS1(int rt, int f)
{
	fa[rt] = f;
	size[rt] = 1;
	dep[rt] = dep[f] + 1;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == f) continue;
		DFS1(v[i].END, rt);
		size[rt] += size[v[i].END];
		if (size[v[i].END] > size[son[rt]]) son[rt] = v[i].END;
	}
}
void DFS2(int rt, int T)
{
	top[rt] = T;
	id[rt] = ++Index;
	add(id[rt], t[rt], 1);
	if (son[rt]) DFS2(son[rt], T);
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa[rt] || v[i].END == son[rt]) continue;
		DFS2(v[i].END, v[i].END);
	}
}
int Count(int x, int y, int z)
{
	int ans = 0;
	while (top[x] != top[y])
	{
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		ans += Query(id[top[x]], id[x], z);
		x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	ans += Query(id[x], id[y], z);
	return ans;
}
char op[10];
int main()
{
	memset (first, -1, sizeof(first));
 	n = read(), Q = read();
	N = n + Q;
	for (int i = 1; i <= n; i++)
		t[i] = read();
	for (int i = 1; i <= n; i++)
		if (H.count(t[i])) t[i] = H[t[i]];
		else H[t[i]] = ++ID, t[i] = ID;
	for (int i = 1; i <= n - 1; i++)
	{
		int a = read(), b = read();
		Add(a, b);
		Add(b, a);
	}
	DFS1(1, 0);
	DFS2(1, 0);
	int lastans = 0;
	while (Q--)
	{
		scanf ("%s", op);
		if (op[0] == 'Q')
		{
			int x = read() ^ lastans, y = read() ^ lastans, z = read() ^ lastans;
			if (H.count(z)) z = H[z];
			else H[z] = ++ID, z = ID;
			printf ("%d\n", lastans = Count(x, y, z));
		}
		else 
		{
			int x = read() ^ lastans, z = read() ^ lastans;
			if (H.count(z)) z = H[z];
			else H[z] = ++ID, z = ID;
			add(id[x], t[x], -1);
			add(id[x], t[x] = z, 1);
		}
	}
}