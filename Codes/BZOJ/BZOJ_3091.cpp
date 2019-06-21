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
const int MAXN = 50005;
struct Node
{
	Node *ch[2], *f;
	long long s, Sum, lSum, RSum, val, v;
	bool rev;
	long long Add;
	void Pushup()
	{
		s = ch[0]->s + ch[1]->s + 1;
		Sum = ch[0]->Sum + ch[1]->Sum + v;
		lSum = ch[0]->lSum + v * (ch[0]->s + 1) + ch[1]->Sum * (ch[0]->s + 1) + ch[1]->lSum;
		RSum = ch[1]->RSum + v * (ch[1]->s + 1) + ch[0]->Sum * (ch[1]->s + 1) + ch[0]->RSum;
		val = ch[0]->val + ch[1]->val + ch[0]->lSum * (ch[1]->s + 1) + ch[1]->RSum * (ch[0]->s + 1) + v * (ch[0]->s + 1) * (ch[1]->s + 1);
	}
}*Q[MAXN], *null;
Node *NewNode(int x)
{
	Node *o = new Node();
	o->ch[0] = o->ch[1] = o->f = null;
	o->s = 1, o->Sum = x, o->v = x, o->lSum = x, o->RSum = x;
	o->val = x, o->rev = 0;
	return o;
}
void Pushflip(Node *rt)
{
	if (rt == null) return;
	swap(rt->ch[0], rt->ch[1]);
	swap(rt->lSum, rt->RSum);
	rt->rev ^= 1;
}
void Pushadd(Node *rt, long long x)
{
	if (rt == null) return;
	rt->v += x;
	rt->Sum += x * rt->s;
	rt->lSum += x * rt->s * (rt->s + 1) / 2;
	rt->RSum += x * rt->s * (rt->s + 1) / 2;
	rt->val += x * rt->s * (rt->s + 1) * (rt->s + 2) / 6;
	rt->Add += x;
}
void Pushdown(Node *rt)
{
	if (rt->rev)
	{
		Pushflip(rt->ch[0]);
		Pushflip(rt->ch[1]);
		rt->rev = 0;
	}
	if (rt->Add)
	{
		Pushadd(rt->ch[0], rt->Add);
		Pushadd(rt->ch[1], rt->Add);
		rt->Add = 0;
	}
}
inline int son(Node *rt)
{
	return rt->f->ch[1] == rt;
}
inline bool IsRoot(Node *rt)
{
	return rt->f->ch[0] != rt && rt->f->ch[1] != rt;
}
inline void rotate(Node *rt)
{
	if (IsRoot(rt)) return;
	Node *fa = rt->f, *Grand = fa->f;
	int tmp = IsRoot(fa);
	Pushdown(fa), Pushdown(rt);
	int k = son(rt), kk = son(fa);
	fa->ch[k] = rt->ch[k ^ 1];
	if (rt->ch[k ^ 1] != null) rt->ch[k ^ 1]->f = fa;
	rt->ch[k ^ 1] = fa, fa->f = rt, rt->f = Grand;
	if (!tmp) Grand->ch[kk] = rt;
	fa->Pushup(), rt->Pushup();
}
void Clear(Node *rt)
{
	if (!IsRoot(rt)) Clear(rt->f);
	Pushdown(rt);
}
void Splay(Node *rt)
{
	for (Clear(rt); !IsRoot(rt); rotate(rt))
		if (!IsRoot(rt->f))
			rotate(son(rt) == son(rt->f) ? rt->f : rt);
}
void Access(Node *rt)
{
	for (Node *pre = null; rt != null; pre = rt, rt = rt->f)
	{
		Splay(rt);
		rt->ch[1] = pre;
		rt->Pushup();
	}
}
void MakeRoot(Node *rt)
{
	Access(rt);
	Splay(rt);
	Pushflip(rt);
}
void Link(Node *a, Node *b)
{
	MakeRoot(a);
	a->f = b;
}
void Cut(Node *a, Node *b)
{
	MakeRoot(a);
	Access(b);
	Splay(b);
	Pushdown(b);
	b->ch[0]->f = null;
	b->ch[0] = null;
}
Node *find(Node *rt)
{
	if (rt->ch[0] != null) return find(rt->ch[0]);
	return rt;
}
Node *find_fa(Node *rt)
{
	if (rt->f != null) return find_fa(rt->f);
	return rt;
}
long long gcd(long long a, long long b)
{
	return b == 0 ? a : gcd(b, a % b);
}
int main()
{
	// freopen ("1.out", "w", stdout);
	null = new Node();
	null->ch[0] = null->ch[1] = null->f = null;
	null->s = null->Sum = null->lSum = null->RSum = null->val = null->v = 0;
	int n = read(), m = read();
	for (int i = 1; i <= n; i++) Q[i] = NewNode(read());
	for (int i = 1; i < n; i++)
	{
		int a = read(), b = read();
		Link(Q[a], Q[b]);
	}
	while (m--)
	{
		int op = read();
		if (op == 1)
		{
			int a = read(), b = read();
			MakeRoot(Q[a]); Access(Q[b]);
			if (find_fa(Q[a]) == find_fa(Q[b]))
				Cut(Q[a], Q[b]);
		}
		else if (op == 2)
		{
			int a = read(), b = read();
			MakeRoot(Q[a]); Access(Q[b]);
			if (find_fa(Q[a]) != find_fa(Q[b]))
				Link(Q[a], Q[b]);
		}
		else if (op == 3)
		{
			int a = read(), b = read();
			int x = read();
			MakeRoot(Q[a]); Access(Q[b]);
			if (find_fa(Q[a]) == find_fa(Q[b]))
			{
				Splay(Q[b]);
				Pushadd(Q[b], x);
			}
		}
		else
		{
			int a = read(), b = read();
			MakeRoot(Q[a]); Access(Q[b]);
			if (find_fa(Q[a]) == find_fa(Q[b]))
			{
				Splay(Q[b]);
				long long x = Q[b]->val;
				long long y = Q[b]->s * (Q[b]->s + 1) / 2;
				long long g = gcd(x, y);
				printf ("%lld/%lld\n", x / g, y / g);
			}
			else printf ("-1\n");
		}
	}
}