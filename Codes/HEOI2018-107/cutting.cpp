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
const int MAXN = 100005;
// NULL -> null important
struct data
{
	int l, r;
	long long ans;
	data(int _l = 0, int _r = 0, long long _ans = 0):l(_l), r(_r), ans(_ans) {}
	data operator + (const data &a) 
	{
		return data((l ? l : a.l), (a.r ? a.r : r), ans + a.ans + (r && a.l ? 1ll * a.l * (a.l - r) : 0));
	}
}z;
struct Node
{
	Node *ch[2];
	data x;
	Node()
	{
		ch[0] = ch[1] = NULL;
	}
	// #define X(_) ((_) ? (_)->x : z)
	void Pushup()
	{
		x = ch[0]->x + ch[1]->x;
	}
}*root[MAXN << 1], *null;
Node *NewNode()
{
	Node *o = new Node();
	o->ch[0] = o->ch[1] = null;
	return o;
}
void insert(Node *&rt, int l, int r, int c)
{
	rt = NewNode();
	rt->x = data(c, c, 0);
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (c <= mid) insert(rt->ch[0], l, mid, c);
	else insert(rt->ch[1], mid + 1, r, c);
}
Node *Merge(Node *A, Node *B)
{
	if (A == null || B == null)
		return A != null ? A : B;
	Node *rt = NewNode();
	rt->ch[0] = Merge(A->ch[0], B->ch[0]);
	rt->ch[1] = Merge(A->ch[1], B->ch[1]);
	rt->Pushup();
	return rt;
}
data Query(Node *rt, int l, int r, int L, int R)
{
	if (L <= l && R >= r) return rt->x;
	int mid = (l + r) >> 1;
	if (R <= mid) return Query(rt->ch[0], l, mid, L, R);
	if (mid < L) return Query(rt->ch[1], mid + 1, r, L, R);
	return Query(rt->ch[0], l, mid, L, R) + Query(rt->ch[1], mid + 1, r, L, R);
}
int QL(Node *rt, int l, int r, int L)
{
	if (L <= l) return rt->x.l;
	int mid = (l + r) >> 1, t;
	if (L <= mid && (t = QL(rt->ch[0], l, mid, L)))
		return t;
	else return QL(rt->ch[1], mid + 1, r, L);
}
int QR(Node *rt, int l, int r, int R)
{
	if (R >= r) return rt->x.r;
	int mid = (l + r) >> 1, t;
	if (R > mid && (t = QR(rt->ch[1], mid + 1, r, R)))
		return t;
	else return QR(rt->ch[0], l, mid, R);
}

int cnt, last, n, Q;
int a[MAXN << 1][10], f[20][MAXN << 1], *fa = f[0], pos[MAXN << 1];
int Max[MAXN << 1], buc[MAXN << 1], rk[MAXN << 1];
void extend(int c)
{
	int p = last, np = last = ++cnt;
	Max[np] = Max[p] + 1;
	pos[Max[np]] = np;
	insert(root[np], 1, n, Max[np]);
	while (p && !a[p][c]) a[p][c] = np, p = fa[p];
	if (!p) fa[np] = 1;
	else
	{
		int q = a[p][c];
		if (Max[q] == Max[p] + 1) fa[np] = q;
		else
		{
			int nq = ++cnt;
			Max[nq] = Max[p] + 1;
			memcpy(a[nq], a[q], sizeof (a[nq]));
			fa[nq] = fa[q];
			fa[np] = fa[q] = nq;
			while (a[p][c] == q) a[p][c] = nq, p = fa[p];
		}
	}
}
long long Calc(int l, int r)
{
	int m = r - l + 1;
	int k = pos[r];
	for (int i = 18; i >= 0; i--)
		if (Max[f[i][k]] >= m)
			k = f[i][k];
	long long ans = 0;
	Node *rt = root[k];
	if (rt->x.r - rt->x.l < m)
		ans += 1ll * (m - (rt->x.r - rt->x.l) - 1) * (n - rt->x.r + rt->x.l - m);
	int L = max(rt->x.l, QR(rt, 1, n, rt->x.r - m + 1));
	int R = min(rt->x.r, QR(rt, 1, n, rt->x.l + m - 1));
	if (L && R && L < R)
	{
		data t = Query(rt, 1, n, L, R);
		ans += t.ans - 1ll * (t.r - t.l) * (rt->x.r - m + 1);
	}
	if (R == rt->x.r)
		ans += 1ll * (rt->x.l - (R - m + 1)) * (m - 2) - 1ll * (rt->x.l - (R - m + 1)) * (rt->x.l - (R - m + 1) - 1) / 2;
	else
		ans += 1ll * (rt->x.l - (R - m + 1)) * max(QL(rt, 1, n, R + 1) - (rt->x.r - m + 1), 0);
	return ans;
}
char s[MAXN];
int main()
{
	// freopen ("cutting.in", "r", stdin);
	// freopen ("cutting.out", "w", stdout);
	null = new Node();
	null->ch[0] = null->ch[1] = null;
	null->x = data(0, 0, 0);
	for (int i = 0; i < MAXN << 1; i++) root[i] = null;
	n = read(), Q = read();
	scanf ("%s", s + 1);
	last = ++cnt;
	for (int i = 1; i <= n; i++)
		extend(s[i] - '0');
	for (int j = 1; j <= 18; j++)
		for (int i = 1; i <= cnt; i++)
			f[j][i] = f[j - 1][f[j - 1][i]];
	for (int i = 1; i <= cnt; i++)
		buc[Max[i]]++;
	for (int i = 1; i <= n; i++) buc[i] += buc[i - 1];
	for (int i = 1; i <= cnt; i++)
		rk[buc[Max[i]]--] = i;
	for (int i = cnt; i > 1; i--)
	{
		int z = rk[i];
		root[fa[z]] = Merge(root[fa[z]], root[z]);
	}
	while (Q--)
	{
		int l = read(), r = read();
		printf ("%lld\n", 1ll * (n - 1) * (n - 2) / 2 - Calc(l, r));
	}
}

