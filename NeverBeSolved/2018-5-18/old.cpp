#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1e5 + 5;
struct Node
{
	Node *ch[2];
	int s;
	Node()
	{
		s = 0;
	}
}*root[MAXN], *null, *rootCol[MAXN];
Node *NewNode()
{
	Node *o = new Node();
	o->ch[0] = o->ch[1] = null;
	return o;
}
void Copy(Node *&rt1, Node *rt2)
{
	if (rt2 == null) rt1 = null;
	else rt1 = NewNode(), *rt1 = *rt2;
}
void Insert(Node *&rt1, Node *rt2, int x, int l, int r)
{
	Copy(rt1, rt2);
	if (rt1 == null) rt1 = NewNode();
	rt1->s++;
	if (l == r) return;
	int mid = l + r >> 1;
	if (x <= mid) Insert(rt1->ch[0], rt2->ch[0], x, l, mid);
	else Insert(rt1->ch[1], rt2->ch[1], x, mid + 1, r);
}
int Query(Node *rt1, Node *rt2, int L, int R, int l, int r)
{
	if (L <= l && R >= r)
		return rt1->s - rt2->s;
	int mid = l + r >> 1;
	int ans = 0;
	if (L <= mid) ans += Query(rt1->ch[0], rt2->ch[0], L, R, l, mid);
	if (R > mid) ans += Query(rt1->ch[1], rt2->ch[1], L, R, mid + 1, r);
	return ans;
}
unsigned int SA, SB, SC;
unsigned int rng61()
{
	SA ^= SA << 16;
	SA ^= SA >> 5;
	SA ^= SA << 1;
	unsigned int t = SA;
	SA = SB;
	SB = SC;
	SC ^= t ^ SA;
	return SC;
}
int n;
struct edge
{
	int END, next;
}v[200005];
int first[MAXN], p;
void add(int a, int b)
{
	// printf ("%d %d\n", a, b);
	v[p].END = b, v[p].next = first[a], first[a] = p++;
	// v[p].END = a, v[p].next = first[b], first[b] = p++;
}
int a[MAXN];
void gen()
{
	int P;
	scanf("%d%d%u%u%u", &n, &P, &SA, &SB, &SC);
	for (int i = 2; i <= P; i++)
		add(i - 1, i);
	for (int i = P + 1; i <= n; i++)
		add(rng61() % (i - 1) + 1, i);
	for (int i = 1; i <= n; i++)
		a[i] = rng61() % n + 1;
}
int f[MAXN][20], dep[MAXN];
int pre[MAXN];
void DFS(int rt, int fa)
{
	Insert(root[rt], root[fa], pre[a[rt]], 0, n);
	Insert(rootCol[rt], rootCol[fa], a[rt], 1, n);
	int bk = pre[a[rt]];
	pre[a[rt]] = rt;
	f[rt][0] = fa;
	for (int i = 1; i <= 19; i++) f[rt][i] = f[f[rt][i - 1]][i - 1];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dep[v[i].END] = dep[rt] + 1;
		DFS(v[i].END, rt);
		// pre[a[rt]] = rt;
	}
	pre[a[rt]] = bk;
}
int lca(int x, int y)
{
	if (dep[x] < dep[y]) swap(x, y);
	int d = dep[x] - dep[y];
	for (int i = 19; i >= 0; i--)
		if (d & (1 << i))
		{
			d -= (1 << i);
			x = f[x][i];
		}
	if (x == y) return x;
	for (int i = 19; i >= 0; i--)
		if (f[x][i] != f[y][i])
			x = f[x][i], y = f[y][i];
	return f[x][0];
}
int vis[MAXN], CO;
int Query(int x, int y)
{
	CO++;
	int l = lca(x, y);
	if (dep[x] - dep[l] > dep[y] - dep[l]) swap(x, y);
	int ans = Query(root[y], root[f[l][0]], 0, f[l][0], 0, n);
	while (x != l)
	{
		if (Query(rootCol[y], rootCol[f[l][0]], a[x], a[x], 1, n) == 0)
		{
			if (vis[a[x]] != CO)
			{
				vis[a[x]] = CO;
				ans++;
			}
		}
		x = f[x][0];
	}
	return ans;
}
int main()
{
	null = new Node();
	null->ch[0] = null->ch[1] = null;
	root[0] = null;
	rootCol[0] = null;
	int T = read();
	while (T--)
	{
		memset (pre, 0, sizeof (pre));
		memset (first, -1, sizeof (first)), p = 0;
		gen();
		int m = read();
		DFS(1, 0);
		while (m--)
		{
			int op = read();
			int x = read(), y = read();
			if (op == 1)
			{
				printf ("%d\n", Query(x, y));
			}
			else printf ("0\n");
		}
	}
}
