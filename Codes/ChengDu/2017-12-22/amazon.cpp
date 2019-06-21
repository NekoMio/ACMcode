#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

const int MAXN = 100005;

struct data
{
	int a, b, c;
	bool operator < (const data &x) const
	{
		return b == x.b ? c < x.c : b < x.b;
	}
}a[MAXN];
#define lowbit(_) ((_) & (-_))
int Max[MAXN], n;
void add(int a, int c)
{
	for (int i = a; i <= n; i += lowbit(i))
		Max[i] = max(Max[i], c);
}
int Query(int a)
{
	int ans = 0;
	for (int i = a; i >= 1; i -= lowbit(i))
		ans = max(ans, Max[i]);
	return ans;
}

struct Node
{
	Node *ch[2];
	int s, v, key;
	int Mark;
	#define size(_) ((_) ? (_)->s : 0)
	Node(int x)
	{
		ch[0] = ch[1] = NULL;
		s = 1, v = x, key = rand();
		Mark = 0;
	}
	void Pushup()
	{
		s = size(ch[0]) + size(ch[1]) + 1;
	}
	void Pushdown()
	{
		if (Mark)
		{
			if (ch[0]) ch[0]->Mark += Mark, ch[0]->v += Mark;
			if (ch[1]) ch[1]->Mark += Mark, ch[1]->v += Mark;
			Mark = 0;
		}
	}
}*root;
Node *Merge(Node *A, Node *B)
{
	if (!A) return B;
	if (!B) return A;
	if (A->key < B->key)
	{
		A->Pushdown();
		A->ch[1] = Merge(A->ch[1], B);
		A->Pushup();
		return A;
	}
	else
	{
		B->Pushdown();
		B->ch[0] = Merge(A, B->ch[0]);
		B->Pushup();
		return B;
	}
}
typedef pair<Node*, Node*> DNode;
DNode Split(Node *rt, int k)
{
	if (!rt) return DNode(NULL, NULL);
	DNode o;
	rt->Pushdown();
	if (size(rt->ch[0]) >= k)
	{
		o = Split(rt->ch[0], k);
		rt->ch[0] = o.second;
		rt->Pushup();
		o.second = rt;
	}
	else
	{
		o = Split(rt->ch[1], k - size(rt->ch[0]) - 1);
		rt->ch[1] = o.first;
		rt->Pushup();
		o.first = rt;
	}
	return o;
}
int Rank(Node *rt, int x)
{
	if (!rt) return 0;
	rt->Pushdown();
	return rt->v >= x ? Rank(rt->ch[0], x) : Rank(rt->ch[1], x) + size(rt->ch[0]) + 1;
}
void Insert(int x)
{
	int k = Rank(root, x);
	DNode y = Split(root, k);
	Node *n = new Node(x);
	root = Merge(y.first, Merge(n, y.second));
}
void Update(int x)
{
	int k = Rank(root, x);
	DNode y = Split(root, k);
	if (y.second)
	{
		y.second->v++;
		y.second->Mark++;
	}
	root = Merge(y.first, y.second);
}
int cnt;
void DFS(Node *rt)
{
	if (rt)
	{
		rt->Pushdown();
		DFS(rt->ch[0]);
		a[++cnt].b = rt->v;
		DFS(rt->ch[1]);
	}
}

int main()
{
	n = read();
	if (n <= 3000)
	{
		for (int i = 1; i <= n; i++)
			a[i].a = read();
		for (int i = 1; i <= n; i++)
			a[i].c = read();
		for (int i = 1; i <= n; i++)
		{
			a[i].b = a[i].a;
			for (int j = i + 1; j <= n; j++)
				if (a[i].b >= a[j].a) 
					a[i].b++;
		}
	}
	else
	{
		bool flag = 0;
		for (int i = 1; i <= n; i++)
		{
			a[i].a = read();
			if (a[i].a != i) flag = 1;
		}
		for (int i = 1; i <= n; i++)
			a[i].c = read();
		if (!flag)
		{
			for (int i = 1; i <= n; i++)
				a[i].b = a[i].a;
		}
		else
		{
			for (int i = 1; i <= n; i++)
			{
				Update(a[i].a);
				Insert(a[i].a);
			}
			DFS(root);
		}
	}
	sort(a + 1, a + n + 1);
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		int t = Query(a[i].c) + 1;
		ans = max(ans, t);
		add(a[i].c, t);
	}
	printf ("%d\n", ans);
}