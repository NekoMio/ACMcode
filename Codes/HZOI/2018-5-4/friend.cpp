// #pragma GGC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <cassert>
#include <vector>
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
struct bitset
{
	unsigned int a[(151 / 32) + 1];
	int len;
	bitset() { memset (a, 0, sizeof (a)); len = (151 / 32);}
	void set() { memset (a, 0xff, sizeof (a)); }
	inline void set(int x, int b) { b == 1 ? a[x >> 5] |= (1u << x) : a[x >> 5] &= (~(1u << x)); }
	bool test(int x) { return a[x >> 5] >> x & 1; }
	int lowbit()
	{
		int ans = 0;
		for (register int i = 0; i <= len; i++)
			if (a[i] != 0)
			{
				ans = __builtin_ctz(a[i]) + (i << 5);
				break;
			}
		if (ans == 0) return 151;
		else return ans;
	}
};
int lowbit(bitset &A, bitset &B)
{
	int ans = 0;
	for (register int i = 0; i <= 4; i++)
		if ((A.a[i] & B.a[i]) != 0)
		{
			ans = __builtin_ctz((A.a[i] & B.a[i])) + (i << 5);
			break;
		}
	if (ans == 0) return 151;
	else return ans;
} 
const int INF = 0x3f3f3f3f;
const int MAXN = 300005;
struct data
{
	int a, b;
}a[MAXN];
bitset v[151], v2[151];
vector<int> vc;
int vv[151][151];
int T, S[151], n, m, q;
bitset vis;
void DFS1(int x)
{
	vis.set(x, 0);
	register int tmp = lowbit(vis, v[x]);
	while (tmp <= n)
	{
		DFS1(tmp);
		tmp = lowbit(vis, v[x]);
	}
	vc.push_back(x);
}
void DFS2(int x)
{
	S[T]++;
	vis.set(x, 0);
	register int tmp = lowbit(vis, v2[x]);
	while (tmp <= n)
	{
		DFS2(tmp);
		tmp = lowbit(vis, v2[x]);
	}
}
void Calc()
{
	vis.set();
	vis.set(0, 0);
	vc.clear();
	T = 0;
	register int tmp = vis.lowbit();
	while (tmp <= n)
	{
		DFS1(vis.lowbit());
		tmp = vis.lowbit();
	}
	vis.set();
	vis.set(0, 0);
	for (int i = n - 1; i >= 0; i--)
		if (vis.test(vc[i]))
		{
			++T;
			S[T] = 0;
			DFS2(vc[i]);
		}
}
int in[MAXN];
struct Query_data
{
	int l, r, id;
	bool operator < (const Query_data &b) const 
	{
		return in[l] == in[b.l] ? r < b.r : in[l] < in[b.l];
	}
}Q[50005];
void Add(int x)
{
	vv[a[x].a][a[x].b]++;
	if (vv[a[x].a][a[x].b] == 1)
	{
		v[a[x].a].set(a[x].b, 1);
		v2[a[x].b].set(a[x].a, 1);
	}
}
void Del(int x)
{
	vv[a[x].a][a[x].b]--;
	if (vv[a[x].a][a[x].b] == 0)
	{
		v[a[x].a].set(a[x].b, 0);
		v2[a[x].b].set(a[x].a, 0);
	}
}
int Ans[50005];
int main()
{
	// freopen("test/1.in", "r", stdin);
	n = read(), m = read(), q = read();
	// for (int i = 1; i <= n; i++)
	// 	vv[i].resize(n + 1);
	for (int i = 1; i <= m; i++)
		a[i].a = read(), a[i].b = read();
	int lastl = 1, lastr = 0;
	for (int i = 1; i <= q; i++)
		Q[i].l = read(), Q[i].r = read(), Q[i].id = i;
	int block = 3000;
	for (int i = 1; i <= m; i++)
		in[i] = (i - 1) / block + 1;
	sort(Q + 1, Q + q + 1);
	int l = 1, r = 1;
	Add(1);
	// for (int i = 1; i <= m; i++) Add(i);
	for (int i = 1; i <= q; i++)
	{
		while (l < Q[i].l) {Del(l); l++;}
		while (l > Q[i].l) {l--; Add(l);}
		while (r > Q[i].r) {Del(r); r--;}
		while (r < Q[i].r) {r++, Add(r);}
		Calc();
		int ans = 0;
		for (int j = 1; j <= T; j++)
			ans = ans + S[j] * (S[j] - 1) / 2;
		Ans[Q[i].id] = ans;
	}
	for (int i = 1; i <= q; i++)
		printf ("%d\n", Ans[i]);
}