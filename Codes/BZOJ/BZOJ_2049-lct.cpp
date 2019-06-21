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

const int MAXN = 10010;

struct Node
{
	Node *f, *ch[2];
	bool IsRoot, Mark;
	Node()
	{
		f = ch[0] = ch[1] = NULL;
		IsRoot = 1, Mark = 0;
	}
}*null, *Q[MAXN];
Node *NewNode()
{
	Node *o = new Node();
	o->f = o->ch[0] = o->ch[1] = null;
	return o;
}
bool son(Node *rt)
{
	return rt->f->ch[1] == rt;
}
inline void Pushflip(Node *rt)
{
	if (rt == null) return;
	rt->Mark ^= 1, swap(rt->ch[0], rt->ch[1]);
}
inline void Pushdown(Node *rt)
{
	if (rt->Mark)
	{
		Pushflip(rt->ch[0]);
		Pushflip(rt->ch[1]);
		rt->Mark = 0;
	}
}
inline void rotate(Node *rt)
{
	if (rt->IsRoot) return;
	Node *fa = rt->f, *Grand = fa->f;
	Pushdown(fa), Pushdown(rt);
	int k = son(rt), kk = son(fa);
	fa->ch[k] = rt->ch[k ^ 1];
	if (rt->ch[k ^ 1] != null) rt->ch[k ^ 1]->f = fa;
	rt->ch[k ^ 1] = fa, fa->f = rt, rt->f = Grand;
	if (!fa->IsRoot) Grand->ch[kk] = rt;
	else fa->IsRoot = 0, rt->IsRoot = 1; 
}
inline void Clear(Node *rt)
{
	if (!rt->IsRoot) Clear(rt->f);
	Pushdown(rt);
}

inline void Splay(Node *rt)
{
	for (Clear(rt); !rt->IsRoot; rotate(rt))
		if (!rt->f->IsRoot)
			rotate(son(rt) == son(rt->f) ? rt->f : rt);
}

inline void Access(Node *rt)
{
	for (Node *pre = null; rt != null; pre = rt, rt = rt->f)
	{
		Splay(rt);
		rt->ch[1]->IsRoot = 1;
		pre->IsRoot = 0;
		rt->ch[1] = pre;
	}
}

inline void MakeRoot(Node *rt)
{
	Access(rt);
	Splay(rt);
	Pushflip(rt);
}

inline void link(Node *a, Node *b)
{
	MakeRoot(a);
	a->f = b;
}

inline void cut(Node *a, Node *b)
{
	MakeRoot(a);
	Access(b);
	Splay(b);
	Pushdown(b);
	b->ch[0]->IsRoot = 1;
	b->ch[0]->f = null;
	b->ch[0] = null;
}

inline Node* find(Node *rt)
{
	if (rt->ch[0] != null) return find(rt->ch[0]);
	return rt;
}

inline bool Judge(Node *a, Node *b)
{
	while (a->f != null) a = a->f;
	while (b->f != null) b = b->f;
	return a == b;
}

int main()
{
	int n = read(), m = read();
	null = new Node();
	null->ch[0] = null->ch[1] = null->f = null, null->IsRoot = null->Mark = 0;
	for (int i = 1; i <= n; i++)
		Q[i] = NewNode();
	int a, b;
	char c[10];
	while (m--)
	{
		scanf ("%s", c);
		if (c[0] == 'C')
		{
			a = read(), b = read();
			link(Q[a], Q[b]);
		}
		else if (c[0] == 'Q')
		{
			a = read(), b = read();
			puts(Judge(Q[a], Q[b]) ? "Yes" : "No");
		}
		else
		{
			a = read(), b = read();
			cut(Q[a], Q[b]);
		}
	}
}
