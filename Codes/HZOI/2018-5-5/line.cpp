// #pragma GCC optimize("O2")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;
template<typename _Tp> inline void gmin(_Tp &x, _Tp y) { if (x > y) x = y; }
template<typename _Tp> inline void gmax(_Tp &x, _Tp y) { if (x < y) x = y; }
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int INF = 0x3f3f3f3f;
const int MAXN = 5e5 + 5;
struct Node
{
	Node *ch[2];
	long long Sum;
	int s;
	Node()
	{
		ch[0] = ch[1] = NULL;
		Sum = 0;
		s = 0;
	}
}*root[MAXN], *null;
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
int a[MAXN];
const int N = 1e6 + 5e5;
void Insert(Node *&rt1, Node *rt2, int x, int l = 1, int r = N)
{
	Copy(rt1, rt2);
	if (rt1 == null) rt1 = NewNode();
	rt1->Sum += x;
	rt1->s++;
	if (l == r) return;
	int mid = l + r >> 1;
	if (x <= mid) Insert(rt1->ch[0], rt2->ch[0], x, l, mid);
	else Insert(rt1->ch[1], rt2->ch[1], x, mid + 1, r);
}
int Query_Num(Node *rt1, Node *rt2, int L, int R, int l = 1, int r = N)
{
	if (L <= l && R >= r)
		return rt2->s - rt1->s;
	int mid = l + r >> 1;
	int ans = 0;
	if (L <= mid) ans += Query_Num(rt1->ch[0], rt2->ch[0], L, R, l, mid);
	if (R > mid) ans += Query_Num(rt1->ch[1], rt2->ch[1], L, R, mid + 1, r);
	return ans;
}
long long Query(Node *rt1, Node *rt2, int L, int R, int l = 1, int r = N)
{
	if (L > R) return 0;
	if (L <= l && R >= r)
		return rt2->Sum - rt1->Sum;
	int mid = l + r >> 1;
	long long ans = 0;
	if (L <= mid) ans += Query(rt1->ch[0], rt2->ch[0], L, R, l, mid);
	if (R > mid) ans += Query(rt1->ch[1], rt2->ch[1], L, R, mid + 1, r);
	return ans;
}
long long Num(int L, int R)
{
	L--;
	return (1ll * R * (R + 1) / 2) - (1ll * L * (L + 1) / 2);
}
int ans;
void Query_mid(Node *rt1, Node *rt2, int L, int R, int l = 1, int r = N, int f = 0)
{
	if (l == r) return;
	int z = rt2->ch[1]->s - rt1->ch[1]->s + f;
	int mid = l + r >> 1;
	if (z <= R - mid)
	{
		ans = mid;
		Query_mid(rt1->ch[1], rt2->ch[1], L, R, mid + 1, r, f);
	}
	else Query_mid(rt1->ch[0], rt2->ch[0], L, R, l, mid, z);
}
long long Query(int L, int R, int k)
{
	int RR = k + R - L;
	ans = 0;
	Query_mid(root[L - 1], root[R], k, k + R - L);
	ans++;
	// assert(ans > 1);
	return Query(root[L - 1], root[R], ans, N) - Num(ans, RR) + Num(k, ans - 1) - Query(root[L - 1], root[R], 1, ans - 1);
}
int main()
{
	// freopen ("test/3.in", "r", stdin);
	// freopen ("3.out", "w", stdout);
	null = new Node();
	null->ch[0] = null->ch[1] = null;
	root[0] = null;
	int n = read(), m = read();
	for (int i = 1; i <= n; i++)
	{
		a[i] = read();
		Insert(root[i], root[i - 1], a[i]);
	}
	while (m--)
	{
		int l = read(), r = read(), k = read();
		printf ("%lld\n", Query(l, r, k));
	}
}

