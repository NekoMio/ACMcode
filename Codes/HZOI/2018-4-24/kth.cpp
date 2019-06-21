#pragma GCC optimize("O2")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 100005;
struct Seg_Node
{
	Seg_Node *ch[2];
	int tag;
	Seg_Node()
	{
		ch[0] = ch[1] = NULL;
	}
	void *operator new (size_t);
}*SC, *Smempool;
void *Seg_Node::operator new(size_t)
{
    if (SC == Smempool)
    {
        SC = new Seg_Node[1 << 15];
        Smempool = SC + (1 << 15);
    }
    return SC++;
}
void Update(Seg_Node *&rt, int l, int r, int L, int R, int c)
{
	if (rt == NULL) rt = new Seg_Node();
	if (L <= l && R >= r)
	{
		rt->tag += c;
		return;
	}
	int mid = l + r >> 1;
	if (L <= mid) Update(rt->ch[0], l, mid, L, R, c);
	if (R > mid) Update(rt->ch[1], mid + 1, r, L, R, c);
}
int Query(Seg_Node *rt, int l, int r, int x)
{
	if (rt == NULL) return 0;
	if (l == r) return rt->tag;
	int mid = l + r >> 1;
	if (x <= mid) return Query(rt->ch[0], l, mid, x) + rt->tag;
	else return Query(rt->ch[1], mid + 1, r, x) + rt->tag;
}
void Merge(Seg_Node *&rt1, Seg_Node *rt2)
{
	if (!rt2) return;
	if (!rt1) return rt1 = rt2, void();
	rt1->tag += rt2->tag;
	Merge(rt1->ch[0], rt2->ch[0]);
	Merge(rt1->ch[1], rt2->ch[1]);
}
struct Node
{
	Node *ch[2];
	Seg_Node *root;
	Node()
	{
		ch[0] = ch[1] = NULL;
		root = NULL;
	}
	void *operator new (size_t);
}*root[MAXN], *null, *C, *mempool;
void *Node::operator new(size_t)
{
    if (C == mempool)
    {
        C = new Node[1 << 15];
        mempool = C + (1 << 15);
    }
    return C++;
}
Node *NewNode()
{
	Node *o = new Node();
	o->ch[0] = o->ch[1] = null;
	return o;
}
int n, w;
vector<int> vc[MAXN];
void Insert(Node *&rt1, Node *rt2, int l, int r, int x, int pos)
{
	rt1 = NewNode();
	if (pos + w <= vc[x].size() - 1) Update(rt1->root, 1, n, vc[x][pos], vc[x][pos + w] - 1, 1);
	else Update(rt1->root, 1, n, vc[x][pos], n, 1);
	if (pos + w <= vc[x].size() - 1)
	{
		// Update(rt1->root, 1, n, vc[x][pos + w], vc[x][pos + w], -w);
		if (pos + w + 1 <= vc[x].size() - 1)
			Update(rt1->root, 1, n, vc[x][pos + w], vc[x][pos + w + 1] - 1, -w);
		else
			Update(rt1->root, 1, n, vc[x][pos + w], n, -w);
	}
	if (rt2 != null)
	{
		rt1->ch[0] = rt2->ch[0], rt1->ch[1] = rt2->ch[1];
		Merge(rt1->root, rt2->root);
	}
	if (l == r) return;
	int mid = l + r >> 1;
	if (x <= mid) Insert(rt1->ch[0], rt2->ch[0], l, mid, x, pos);
	else Insert(rt1->ch[1], rt2->ch[1], mid + 1, r, x, pos);
}
int Query(Node *rt1, Node *rt2, int l, int r, int k, int R)
{
	if (l == r) return l;
	int mid = l + r >> 1;
	int t = Query(rt1->ch[0]->root, 1, n, R) - Query(rt2->ch[0]->root, 1, n, R);
	if (t >= k)
		return Query(rt1->ch[0], rt2->ch[0], l, mid, k, R);
	else
		return Query(rt1->ch[1], rt2->ch[1], mid + 1, r, k - t, R);
}
int a[MAXN], P[MAXN];
int main()
{
	// freopen ("kth6.in", "r", stdin);
	// freopen ("1.out", "w", stdout);
	null = new Node();
	null->ch[0] = null->ch[1] = null;
	root[0] = null;
	n = read(), w = read();
	int q = read(), type = read();
	for (int i = 1; i <= n; i++)
	{
		a[i] = read();
		vc[a[i]].push_back(i);
		P[i] = vc[a[i]].size() - 1;
	}
	for (int i = 1; i <= n; i++)
		Insert(root[i], root[i - 1], 0, n, a[i], P[i]);
	int lastans = 0;
	while (q--)
	{
		lastans = lastans * type;
		int l = read() ^ lastans, r = read() ^ lastans, k = read() ^ lastans;
		printf ("%d\n", lastans = Query(root[r], root[l - 1], 0, n, k, r));
	}
}
