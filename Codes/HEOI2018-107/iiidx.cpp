#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
#include <queue>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 500005;
struct Node
{
	Node *ch[2];
	int Min, lazy;
	Node()
	{
		Min = 0, lazy = 0;
		ch[0] = ch[1] = NULL;
	}
	void Pushup()
	{
		Min = min(ch[0]->Min, ch[1]->Min);
	}
	void Pushlazy(int c)
	{
		Min += c;
		lazy += c;
	}
	void Puhsdown()
	{
		if (lazy)
		{
			if (ch[0]) ch[0]->Pushlazy(lazy);
			if (ch[1]) ch[1]->Pushlazy(lazy);
			lazy = 0;
		}
	}
}*root;
void Build(Node *rt, int l, int r)
{
	if (l == r)
	{
		rt->Min = l;
		return;
	}
	int mid = (l + r) >> 1;
	rt->ch[0] = new Node(), rt->ch[1] = new Node();
	Build(rt->ch[0], l, mid);
	Build(rt->ch[1], mid + 1, r);
	rt->Pushup();
}
void Update(Node *rt, int L, int R, int c, int l, int r)
{
	if (L <= l && R >= r)
	{
		rt->Pushlazy(c);
		return;
	}
	int mid = (l + r) >> 1;
	rt->Puhsdown();
	if (L <= mid)
		Update(rt->ch[0], L, R, c, l, mid);
	if (R >= mid) 
		Update(rt->ch[1], L, R, c, mid + 1, r);
	rt->Pushup();
}
int Query(Node *rt, int x, int l, int r)
{
	if (l == r)
	{
		if (rt->Min >= x) 
			return l;
		else return l + 1;
	}
	int mid = (l + r) >> 1;
	rt->Puhsdown();
	if (rt->ch[1]->Min >= x)
		return Query(rt->ch[0], x, l, mid);
	return Query(rt->ch[1], x, mid + 1, r);
}
double k;
int d[MAXN], a[MAXN], ans[MAXN], cnt[MAXN], fa[MAXN];
struct edge
{
	int END, next;
}v[MAXN];
int first[MAXN], p;
void add(int a, int b)
{
	v[p].next = first[a];
	v[p].END = b;
	first[a] = p++;
}
int size[MAXN];
void DFS(int rt)
{
	if (rt != 0) size[rt] = 1;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		DFS(v[i].END);
		size[rt] += size[v[i].END];
	}
}
int cmp(const int &x, const int &y)
{
	return x > y;
}
int val[MAXN];
int main()
{
	// freopen ("iiidx.in", "r", stdin);
	// freopen ("iiidx.out", "w", stdout);
	memset (first, -1, sizeof (first));
	int n = read();
	scanf ("%lf\n", &k);
	for (int i = 1; i <= n; i++)
		d[i] = read();
	sort(d + 1, d + n + 1, cmp);
	for (int i = n - 1; i >= 0; i--)
		if (d[i] == d[i + 1])
			cnt[i] = cnt[i + 1] + 1;
	root = new Node();
	Build(root, 1, n);
	for (int i = n; i >= 1; i--)
		add(fa[i] = (int)floor(i / k + 1e-10), i);
	DFS(0);
	for (int i = 1; i <= n; i++)
	{
		if (fa[i] && fa[i] != fa[i - 1]) 
			Update(root, ans[fa[i]], n, size[fa[i]] - 1, 1, n);
		ans[i] = Query(root, size[i], 1, n); 
		ans[i] += cnt[ans[i]];
		cnt[ans[i]]++;
		ans[i] -= cnt[ans[i]] - 1;
		Update(root, ans[i], n, -size[i], 1, n);
	}
	for (int i = 1; i <= n; i++) printf ("%d ", d[ans[i]]);
	// while (1);
}
