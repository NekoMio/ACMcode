#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 2000005;
int n;
double a[MAXN], pos[10];
#define _Size(_) ((_)?(_)->Size : 0)
#define _Sum(_) ((_)?(_)->Sum : 0)
struct Seg_Node
{
	Seg_Node *ch[2];
	double Sum, fval;
	int Size, fsize;
	bool flag;
	Seg_Node()
	{
		ch[0] = ch[1] = NULL;
		Sum = fval = 0;
		Size = fsize = 0;
		flag = 0;
	}
	void Pushup()
	{
		Sum = _Sum(ch[0]) + _Sum(ch[1]) + fval;
		Size = _Size(ch[0]) + _Size(ch[1]) + fsize;
	}
};
void Update(double x, int id, int l, int r, Seg_Node *rt)
{
	rt->Sum += x;
	rt->Size += 1;
	if (l == r)
	{
		rt->fsize = 1;
		rt->fval = x;
		return;
	}
	int mid = (l + r) >> 1;
	if (id <= mid)
	{
		if (rt->ch[0] == NULL) rt->ch[0] = new Seg_Node();
		Update(x, id, l, mid, rt->ch[0]);
	}
	else
	{
		if (rt->ch[1] == NULL) rt->ch[1] = new Seg_Node();
		Update(x, id, mid + 1, r, rt->ch[1]);
	}
}
// typedef pair<Seg_Node*, Seg_Node*> Seg_DNode;
void Seg_Split(Seg_Node *&rt1, Seg_Node *&rt2, int k, int l = 1, int r = n)
{
	if (!rt2) rt2 = new Seg_Node();
	rt2->ch[0] = rt2->ch[1] = NULL;
	if (k == 0)
	{
		rt2 = rt1;
		rt1 = NULL;
		return;
	}
	if (l == r) return;
	int mid = (l + r) >> 1;
	// if (rt == NULL) return Seg_DNode(NULL, NULL);
	if (_Size(rt1->ch[0]) >= k)
	{
		rt2->ch[1] = rt1->ch[1];
		rt1->ch[1] = NULL;
		if (_Size(rt1->ch[0]) != k)
			Seg_Split(rt1->ch[0], rt2->ch[0], k, l, mid);
	}
	else Seg_Split(rt1->ch[1], rt2->ch[1], k - _Size(rt1->ch[0]), mid + 1, r);
	rt1->Pushup();
	rt2->Pushup();
}
void Seg_Merge(Seg_Node *&rt1, Seg_Node *rt2, int l = 1, int r = n)
{
	if (!rt2) return;
	if (!rt1) return rt1 = rt2, void();
	int mid = (l + r) >> 1;
	Seg_Merge(rt1->ch[0], rt2->ch[0], l, mid);
	Seg_Merge(rt1->ch[1], rt2->ch[1], mid + 1, r);
	rt1->Pushup();
}
#define _R(_) ((_)?(_)->R : 0)
struct Node
{
	Node *ch[2];
	Seg_Node *root;
	int L, R, l, r, key;
	bool sor;
	double Sum;
	Node(Seg_Node *rt, int _l, int _r)
	{
		ch[0] = ch[1] = NULL;
		key = rand();
		root = rt;
		L = l = _l, R = r = _r;
		Sum = _Sum(root);
		sor = 0;
	}
	void Pushup()
	{
		Sum = 0;
		L = l, R = r;
		if (ch[0]) L = min(L, ch[0]->L), Sum += ch[0]->Sum;
		if (ch[1]) R = max(R, ch[1]->R), Sum += ch[1]->Sum;
		Sum += _Sum(root);
	}
}*root;
Node *Merge(Node *A, Node *B)
{
	if (!A) return B;
	if (!B) return A;
	if (A->key < B->key)
	{
		A->ch[1] = Merge(A->ch[1], B);
		A->Pushup();
		return A;
	}
	else
	{
		B->ch[0] = Merge(A, B->ch[0]);
		B->Pushup();
		return B;
	}
}
struct DNode
{
	Node *a, *b, *c;
	DNode(Node *_a, Node *_b, Node *_c)
	{
		a = _a, b = _b, c = _c;
	}
	DNode() {}
};
DNode Split(Node *rt, int k)
{
	DNode o;
	if (rt->l <= k && rt->r >= k)
	{
		o = DNode(rt->ch[0], rt, rt->ch[1]);
		rt->ch[0] = NULL;
		rt->ch[1] = NULL;
		rt->Pushup();
		return o;
	}
	if (_R(rt->ch[0]) >= k)
	{
		o = Split(rt->ch[0], k);
		rt->ch[0] = o.c;
		rt->Pushup();
		o.c = rt;
	}
	else
	{
		o = Split(rt->ch[1], k);
		rt->ch[1] = o.a;
		rt->Pushup();
		o.a = rt;
	}
	return o;
}
void DFS_Merge(Node *rt1, Node *rt2)
{
	if (rt2)
	{
		rt1->l = min(rt1->l, rt2->l);
		rt1->r = max(rt1->r, rt2->r);
		DFS_Merge(rt1, rt2->ch[0]);
		Seg_Merge(rt1->root, rt2->root);
		DFS_Merge(rt1, rt2->ch[1]);
	}
}
pair<double, int> Hash[MAXN];
int id[MAXN];
void Sort(int l, int r, int type)
{
	DNode x = Split(root, l);
	if (x.b->r >= r)
	{
		if (x.b->sor)
		{
			Seg_Node *x1 = NULL, *x2 = NULL, *x3 = NULL;
			Seg_Split(x.b->root, x2, l - x.b->l);
			x1 = x.b->root;
			Seg_Split(x2, x3, r - l + 1);
			Node *n1 = new Node(x1, x.b->l, l - 1),
				 *n2 = new Node(x2, l, r),
				 *n3 = new Node(x3, r + 1, x.b->r);
			n1->sor = n3->sor = x.b->sor;
			n2->sor = type;
			if (n1->r >= n1->l)
				x.a = Merge(x.a, n1);
			if (n2->r >= n2->l)
				x.a = Merge(x.a, n2);
			if (n3->r >= n3->l)
				x.a = Merge(x.a, n3);
			root = Merge(x.a, x.c);
		}
		else
		{
			Seg_Node *x1 = NULL, *x2 = NULL, *x3 = NULL;
			Seg_Split(x.b->root, x2, x.b->r - r);
			x1 = x.b->root;
			Seg_Split(x2, x3, r - l + 1);
			Node *n1 = new Node(x3, x.b->l, l - 1),
				 *n2 = new Node(x2, l, r),
				 *n3 = new Node(x1, r + 1, x.b->r);
			n1->sor = n3->sor = x.b->sor;
			n2->sor = type;
			if (n1->r >= n1->l)
				x.a = Merge(x.a, n1);
			if (n2->r >= n2->l)
				x.a = Merge(x.a, n2);
			if (n3->r >= n3->l)
				x.a = Merge(x.a, n3);
			root = Merge(x.a, x.c);
		}
		return;
	}
	else
	{
		DNode y = Split(x.c, r);
		Node *n2 = x.b, *n3 = y.b;
		if (x.b->l < l)
		{
			Seg_Node *x1 = NULL, *x2 = NULL;
			if (x.b->sor)
			{
				Seg_Split(x.b->root, x2, l - x.b->l);
				x1 = x.b->root;
			}
			else
			{
				Seg_Split(x.b->root, x1, x.b->r - l + 1);
				x2 = x.b->root;
			}
			Node *n1 = new Node(x1, x.b->l, l - 1);
			n2 = new Node(x2, l, x.b->r);
			n1->sor = x.b->sor;
			n2->sor = type;
			x.a = Merge(x.a, n1);
		}
		if (y.b->r > r)
		{
			Seg_Node *x1 = NULL, *x2 = NULL;
			if (y.b->sor)
			{
				Seg_Split(y.b->root, x2, r - y.b->l + 1);
				x1 = y.b->root;
			}
			else
			{
				Seg_Split(y.b->root, x1, y.b->r - r);
				x2 = y.b->root;
			}
			Node *n4 = new Node(x2, r + 1, y.b->r);
			n3 = new Node(x1, y.b->l, r);
			n4->sor = y.b->sor;
			n3->sor = type;
			y.c = Merge(n4, y.c);
		}
		Node *z = new Node(NULL, 0x3f3f3f, 0);
		DFS_Merge(z, Merge(n2, Merge(y.a, n3)));
		z->L = z->l, z->R = z->r, z->Sum = _Sum(z->root);
		z->sor = type;
		root = Merge(x.a, Merge(z, y.c));
	}
}
double Query(int l, int r)
{
	DNode x = Split(root, l);
	double ans = 0;
	if (x.b->r >= r)
	{
		if (x.b->sor)
		{
			Seg_Node *x2 = NULL, *x3 = NULL;
			Seg_Split(x.b->root, x2, l - x.b->l);
			Seg_Split(x2, x3, r - l + 1);
			ans = x2->Sum;
			Seg_Merge(x2, x3);
			Seg_Merge(x.b->root, x2);
			root = Merge(x.a, Merge(x.b, x.c));
		}
		else
		{
			Seg_Node *x2 = NULL, *x3 = NULL;
			Seg_Split(x.b->root, x2, x.b->r - r);
			Seg_Split(x2, x3, r - l + 1);
			ans = x2->Sum;
			Seg_Merge(x2, x3);
			Seg_Merge(x.b->root, x2);
			root = Merge(x.a, Merge(x.b, x.c));
		}
		return ans;
	}
	else
	{
		DNode y = Split(x.c, r);
		// Node *n2, *n3;
		if (x.b->l < l)
		{
			Seg_Node *x1 = NULL, *x2 = NULL;
			if (x.b->sor)
			{
				Seg_Split(x.b->root, x2, l - x.b->l);
				x1 = x.b->root;
			}
			else
			{
				Seg_Split(x.b->root, x1, x.b->r - l + 1);
				x2 = x.b->root;
			}
			// Node *n1 = new Node(x1, x.b->l, l - 1);
			// n2 = new Node(x2, l, x.b->r);
			// n1->sor = x.b->sor;
			// n2->sor = type;
			ans -= x1->Sum;
			Seg_Merge(x1, x2);
			x.b->root = x1;
			// x.a = Merge(x.a, n1);
		}
		if (y.b->r > r)
		{
			Seg_Node *x1 = NULL, *x2 = NULL;
			if (y.b->sor)
			{
				Seg_Split(y.b->root, x1, r - y.b->l + 1);
				x2 = y.b->root;
			}
			else
			{
				Seg_Split(y.b->root, x2, y.b->r - r);
				x1 = y.b->root;
			}
			ans -= x1->Sum;
			Seg_Merge(x1, x2);
			y.b->root = x1;
			// Node *n4 = new Node(x1, r + 1, y.b->r);
			// n3 = new Node(x2, y.b->l, r);
			// y.c = Merge(n4, y.c);
		}
		// Node *z = new Node(NULL, 0x3f3f3f, 0);
		// DFS_Merge(z, Merge(n2, Merge(y.a, n3)));
		// z->L = z->l, z->R = z->r, z->Sum = _Sum(z->root);
		// z->sor = type;
		ans += _Sum(y.a) + _Sum(y.b) + _Sum(x.b);
		root = Merge(x.a, Merge(x.b, Merge(y.a, Merge(y.b, y.c))));
		return ans;
	}
}
int main()
{
	// freopen ("zkb4.in", "r", stdin);
	// freopen ("zkb4.out", "w", stdout);
	// freopen ("1.in", "r", stdin);
	// freopen ("1.out", "w", stdout);
	n = read();
	int m = read();
	for (int i = 1; i <= n; i++)
		a[i] = log10(read());
	for (int i = 1; i <= 9; i++)
		pos[i] = log10(i);
	for (int i = 1; i <= n; i++)
		Hash[i] = pair<double, int>(a[i], i);
	sort(Hash + 1, Hash + n + 1);
	for (int i = 1; i <= n; i++)
		id[Hash[i].second] = i;
	for (int i = 1; i <= n; i++)
	{
		Seg_Node *x = new Seg_Node();
		Update(a[i], id[i], 1, n, x);
		Node *n = new Node(x, i, i);
		root = Merge(root, n);
	}
	while (m--)
	{
		int op = read();
		if (op == 1)
		{
			int l = read(), r = read(), type = read();
			Sort(l, r, type);
			// for (int i = 1; i <= n; i++)
			// 	printf ("%.0f ", pow(10, Query(i, i)));
			// printf ("\n");
		}
		else if (op == 2)
		{
			int l = read(), r = read();
			double x = Query(l, r);
			x -= floor(x);
			int ans = 0;
			for (int i = 1; i <= 9; i++)
				if (x >= pos[i])
					ans = i;
			printf ("%d\n", ans);
		}
		else
		{
			int c = read();
			double x = Query(c, c);
			printf ("%.0f\n", round(pow(10, x)));
		}
	}
}