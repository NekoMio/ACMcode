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
const int MOD = 998244353;
const int MAXN = 3e5 + 5;
struct Node
{
	Node *ch[2];
	int P, flag;
	int d;
	Node()
	{
		ch[0] = ch[1] = NULL;
		P = flag = 1;
	}
	void Pushup()
	{
		P = 0;
		if (ch[0] != NULL) P += ch[0]->P;
		if (ch[1] != NULL) P += ch[1]->P;
		P += d;
		P %= MOD;
	}
	void Pushflag(int x)
	{
		P = 1ll * P * x % MOD;
		flag = 1ll * flag * x % MOD;
		d = 1ll * d * x % MOD;
	}
	void Pushdown()
	{
		if (flag != 1)
		{
			if (ch[0]) ch[0]->Pushflag(flag);
			if (ch[1]) ch[1]->Pushflag(flag);
			flag = 1;
		}
	}
}*root[MAXN];
void Insert(Node *&rt, int x, int l, int r)
{
	if (rt == NULL) rt = new Node();
	if (l == r)
	{
		rt->d = 1;
		return;
	}
	int mid = l + r >> 1;
	if (x <= mid) Insert(rt->ch[0], x, l, mid);
	else Insert(rt->ch[1], x, mid + 1, r);
	rt->Pushup();
}
int Maxa, Maxb;
Node *Merge(Node *rt1, Node *rt2, int p)
{
	if (!rt1 && !rt2) return NULL;
	if (rt1 == NULL)
	{
		Maxb = (Maxb + rt2->P) % MOD;
		// rt2->Pushdown();
		rt2->Pushflag(((Maxa + p - 2ll * Maxa * p) % MOD + MOD) % MOD);
		// rt2->flag = 1ll * rt2->flag * ((Maxa + p - 2ll * Maxa * p) % MOD + MOD) % MOD;
		// rt2->Pushdown();
		return rt2;
	}
	if (rt2 == NULL)
	{
		Maxa = (Maxa + rt1->P) % MOD;
		// rt1->Pushdown();
		rt1->Pushflag(((Maxb + p - 2ll * Maxb * p) % MOD + MOD) % MOD);
		// rt1->flag = 1ll * rt1->flag * ((Maxb + p - 2ll * Maxb * p) % MOD + MOD) % MOD;
		// rt1->Pushdown();
		return rt1;
	}
	rt1->Pushdown(), rt2->Pushdown();
	rt1->ch[1] = Merge(rt1->ch[1], rt2->ch[1], p);
	rt1->ch[0] = Merge(rt1->ch[0], rt2->ch[0], p);
	rt1->Pushup();
	#ifdef Mine
	printf ("%d\n", rt1->P);
	#endif
	return rt1;
}
int Hash[MAXN], tot, s, ans;
void Clear(Node *rt, int l, int r)
{
	if (l == r)
	{
		s++;
		#ifdef Mine
		printf ("%d %d %d\n", s, Hash[l], rt->d);
		#endif
		ans = (ans + 1ll * s * Hash[l] % MOD * rt->d % MOD * rt->d % MOD) % MOD;
		return;
	}
	rt->Pushdown();
	int mid = l + r >> 1;
	if (rt->ch[0]) Clear(rt->ch[0], l, mid);
	if (rt->ch[1]) Clear(rt->ch[1], mid + 1, r);
}
int c[MAXN];
struct edge
{
	int END, next;
}v[MAXN];
int first[MAXN], p;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
int Sum[MAXN];
void DFS(int rt)
{
	// root[rt] = NULL;
	if (Sum[rt] == 0) return;
	if (Sum[rt] == 1)
	{
		DFS(v[first[rt]].END);
		root[rt] = root[v[first[rt]].END];
	}
	else
	{
		DFS(v[first[rt]].END);
		DFS(v[v[first[rt]].next].END);
		Maxa = Maxb = 0;
		root[rt] = Merge(root[v[first[rt]].END], root[v[v[first[rt]].next].END], 1ll * c[rt] * 796898467 % MOD);
	}
}
int main()
{
	// freopen ("1.in", "r", stdin);
	memset (first, -1, sizeof (first));
	int n = read();
	for (int i = 1; i <= n; i++)
	{
		int fa = read();
		if (i != 1)
			add(fa, i);
		Sum[fa]++;
	}
	for (int i = 1; i <= n; i++)
	{
		c[i] = read();
		if (first[i] == -1)
			Hash[++tot] = c[i];
	}
	sort(Hash + 1, Hash + tot + 1);
	int cnt = unique(Hash + 1, Hash + tot + 1) - Hash - 1;
	for (int i = 1; i <= n; i++)
		if (first[i] == -1)
		{
			c[i] = lower_bound(Hash + 1, Hash + cnt + 1, c[i]) - Hash;
			Insert(root[i], c[i], 1, cnt);
		}
	DFS(1);
	Clear(root[1], 1, cnt);
	printf ("%d\n", ans);
}
