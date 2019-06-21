#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
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
const int INF = 0x3f3f3f3f;
const int MAXN = 150005;
map<int, vector<int> > mp;
map<int, int> cnt, id;
vector<int> mem;
int n, m, k;
int a[MAXN];
int Xor[MAXN];
struct data
{
	int l, r, w;
}b[MAXN];
vector<int> vc[MAXN];
vector<int> vcc[MAXN];
#define lowbit(_) ((_) & (-_))
int Sum[MAXN];
void Update(int x, int c)
{
	for (int i = x; i <= n; i += lowbit(i))
		Sum[i] += c;
}
int Query(int x)
{
	int ans = 0;
	for (int i = x; i >= 1; i -= lowbit(i))
		ans += Sum[i];
	return ans;
}
int ans[MAXN];
void Update(int l, int r, int x)
{
	ans[l] += x;
	ans[r + 1] -= x;
}
const int MOD = 1073741824;
int block;
void Work1()
{
	mp[0].push_back(0);
	for (int i = 1; i <= m; i++)
		Update(b[i].l, b[i].w);
	for (int i = 1; i <= n; i++)
	{
		int t = Xor[i] ^ k;
		if (cnt[t] >= block)
		{
			mp[Xor[i]].push_back(i);
			for (int j = 0; j < vc[i].size(); j++)
				Update(b[vc[i][j]].l, -b[vc[i][j]].w);
			continue;
		}
		if (mp.count(t))
		{
			vector<int> &now = mp[t];
			int nm = now.size();
			for (int j = 0; j < nm; j++)
				Update(now[j] + 1, i, Query(now[j] + 1));
		}
		mp[Xor[i]].push_back(i);
		for (int j = 0; j < vc[i].size(); j++)
			Update(b[vc[i][j]].l, -b[vc[i][j]].w);
	}
}
int t[MAXN], C[MAXN];
void Calc(int l, int r)
{
	int cur = 0;
	for (int i = 1; i <= n; i++)
	{
		C[i] = C[i - 1] + (Xor[i - 1] == l);
		if (Xor[i - 1] == l) cur += t[i];
		for (int j = 0; j < vc[i - 1].size(); j++)
			cur -= b[vc[i - 1][j]].w * (C[i - 1] - C[b[vc[i - 1][j]].l - 1]);
		if (Xor[i] == r) ans[i + 1] -= cur;
	}
	cur = 0;
	for (int i = n; i >= 1; i--)
	{
		C[i] = C[i + 1] + (Xor[i] == r);
		if (Xor[i] == r) cur += t[i];
		for (int j = 0; j < vcc[i + 1].size(); j++)
			cur -= b[vcc[i + 1][j]].w * (C[i + 1] - C[b[vcc[i + 1][j]].r + 1]);
		if (Xor[i - 1] == l) ans[i] += cur;
	}
}
void Work2()
{
	for (int i = 1; i <= m; i++)
		t[b[i].l] += b[i].w, t[b[i].r + 1] -= b[i].w;
	for (int i = 1; i <= n; i++)
		t[i] += t[i - 1];
	// for (auto x : mem)
	for (vector<int>::iterator x = mem.begin(); x != mem.end(); x++)
		if (cnt.count((*x) ^ k))
			Calc((*x), (*x) ^ k);
}
int main()
{
	// freopen ("HaventSolve/2018-5-4/xor4.in", "r", stdin);
	// freopen ("1.out", "w", stdout);
	n = read(), m = read(), k = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= m; i++)
	{
		b[i].l = read(), b[i].r = read(), b[i].w = read();
		vc[b[i].r].push_back(i);
		vcc[b[i].l].push_back(i);
	}
	block = pow(n, 0.6);
	// block = 10000;
	for (int i = 1; i <= n; i++)
	{
		Xor[i] = Xor[i - 1] ^ a[i];
		cnt[Xor[i]]++;
		if (cnt[Xor[i]] == block)
		{
			mem.push_back(Xor[i]);
			// printf ("x:%d\n", Xor[i]);
		}
	}
	Work2();
	// for (int i = 1; i <= n; i++)
	// 	printf ("%d\n", ans[i]);
	Work1();
	for (int i = 1; i <= n; i++)
		ans[i] += ans[i - 1];
	for (int i = 1; i <= n; i++)
		printf ("%d ", (ans[i] & 0x3fffffff));
	// printf ("\n");
	// while (1);
}
