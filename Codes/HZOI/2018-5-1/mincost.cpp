#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 300005;
const int MAXM = 500005;
int n, m, k;
int a[MAXN], b[MAXN];
struct data
{
	int S, E, a, b, id;
	bool operator > (const data &c) const 
	{
		return a < c.a;
	}
	bool operator < (const data &c) const 
	{
		return b == c.b ? id > c.id : b > c.b;
	}
}v[MAXM];
set<data> st;
struct Node
{
	Node *ch[2], *f;
	int s, Sum, XSum, id, rid;
	bool flip;
	Node()
	{
		ch[0] = ch[1] = NULL;
		s = Sum = XSum = flip = 0;
		id = rid = 0;
	}
}*Q[MAXN + MAXM], *null;
Node *NewNode()
{
	Node *o = new Node();
	o->ch[0] = o->ch[1] = o->f = null;
	return o;
}
void Pushflip(Node *rt)
{
	if (rt == null) return;
	rt->flip ^= 1;
	swap(rt->ch[0], rt->ch[1]);
}
void Pushdown(Node *rt)
{
	if (rt->flip)
	{
		Pushflip(rt->ch[0]);
		Pushflip(rt->ch[1]);
		rt->flip = 0;
	}
}
void Pushup(Node *rt)
{
	rt->Sum = rt->ch[0]->Sum + rt->ch[1]->Sum + rt->s + rt->XSum;
	rt->id = v[rt->ch[0]->id].b > v[rt->ch[1]->id].b ? rt->ch[0]->id : rt->ch[1]->id;
	rt->id = v[rt->id].b > v[rt->rid].b ? rt->id : rt->rid;
}
inline int son(Node *rt)
{
	return rt->f->ch[1] == rt;
}
inline bool IsRoot(Node *rt)
{
	return rt->f->ch[0] != rt && rt->f->ch[1] != rt;
}
void rotate(Node *rt)
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
	Pushup(fa), Pushup(rt); 
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
		rt->XSum += rt->ch[1]->Sum;
		rt->XSum -= pre->Sum;
		rt->ch[1] = pre;
		Pushup(rt);
	}
}
void MakeRoot(Node *rt)
{
	Access(rt);
	Splay(rt);
	Pushflip(rt);
}
void link(Node *a, Node *b)
{
	MakeRoot(a);
	Access(b);
	Splay(b);
	a->f = b;
	b->XSum += a->Sum;
	Pushup(b);
}
void cut(Node *a, Node *b)
{
	MakeRoot(a);
	Access(b);
	Splay(b);
	Pushdown(b);
	b->ch[0]->f = null;
	b->ch[0] = null;
}
Node *find_fa(Node *rt)
{
	if (rt->f != null) return find_fa(rt->f);
	return rt;
}
int Query(Node *a, Node *b)
{
	MakeRoot(a);
	Access(b);
	Splay(b);
	return b->id;
}
int Size(Node *rt)
{
	MakeRoot(rt);
	return rt->Sum;
}
int globle;
vector<data> vc;
int POP()
{
	int ans = 0x7fffffff;
	vc.clear();
	for (auto x : st)
	{
		globle -= (Size(Q[x.id]) >= k);
		cut(Q[x.S], Q[x.id]);
		cut(Q[x.E], Q[x.id]);
		globle += (Size(Q[x.S]) >= k);
		globle += (Size(Q[x.E]) >= k);
		if (globle == 0)
		{
			globle -= (Size(Q[x.S]) >= k);
			globle -= (Size(Q[x.E]) >= k);
			link(Q[x.S], Q[x.id]);
			link(Q[x.E], Q[x.id]);
			globle += (Size(Q[x.id]) >= k);
			ans = x.b;
			break;
		}
		else vc.push_back(x);
	}
	for (auto x : vc)
		st.erase(x);
	return ans;
}
int main()
{
	// freopen ("mincost_A1.in", "r", stdin);
	null = new Node();
	null->f = null->ch[0] = null->ch[1] = null;
	n = read(), m = read(), k = read() - 1;
	for (int i = 1; i <= n; i++)
		a[i] = read(), b[i] = read(), Q[i] = NewNode();
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read();
		v[i].S = x, v[i].E = y;
		v[i].a = max(a[x], a[y]);
		v[i].b = max(b[x], b[y]);
	}
	sort(v + 1, v + m + 1, greater<data>());
	for (int i = 1; i <= m; i++)
	{
		v[i].id = i + n;
		Q[i + n] = NewNode();
		Q[i + n]->s = Q[i + n]->Sum = 1;
		Q[i + n]->id = Q[i + n]->rid = i;
	}
	long long ans = 0x7ffffffffff;
	for (int i = 1; i <= m; i++)
	{
		if (find_fa(Q[v[i].S]) != find_fa(Q[v[i].E]))
		{
			st.insert(v[i]);
			globle -= (Size(Q[v[i].S]) >= k);
			globle -= (Size(Q[v[i].E]) >= k);
			link(Q[v[i].id], Q[v[i].E]);
			link(Q[v[i].id], Q[v[i].S]);
			globle += (Size(Q[v[i].S]) >= k);
		}
		else
		{
			int t = Query(Q[v[i].S], Q[v[i].E]);
			if (v[t].b > v[i].b)
			{
				st.erase(v[t]);
				st.insert(v[i]);
				cut(Q[v[t].id], Q[v[t].S]);
				cut(Q[v[t].id], Q[v[t].E]);
				link(Q[v[i].id], Q[v[i].S]);
				link(Q[v[i].id], Q[v[i].E]);
			}
		}
		if (globle > 0)
			ans = min(ans, 1ll * v[i].a + POP());
	}
	if (ans == 0x7ffffffffff) return printf ("no solution\n"), 0;
	printf ("%lld\n", ans);
}
