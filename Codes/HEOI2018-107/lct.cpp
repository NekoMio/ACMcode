#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline void gmax(long long &a, long long b) { if (a < b) a = b; }
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const long long INF = 0x3f3f3f3f3f3f3f3fll;
const long long inf = 0xC0C0C0C0C0C0C0C0ll;
const int MAXN = 3e5 + 5;
struct edge
{
	int END, next, v;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b, int c)
{
	v[p].END = b;
	v[p].v = c;
	v[p].next = first[a];
	first[a] = p++;
}
int size[MAXN], K;
long long MID;
struct data
{
	int x;
	long long val;
	data(int a = 0, long long b = 0) : x(a), val(b) {}
	void Change(data a, data b, int op, int d)
	{
		if (a.val == inf || b.val == inf) return;
		data t(a.x + b.x + op, a.val + b.val - op * MID + d);
		if (t.x <= 0) return;
		if (t.val > val || (t.val == val && t.x < x)) *this = t;
	}
}f[MAXN][3], tmp[3];
void DP(int rt, int fa)
{
	// size[rt] = 1;
	f[rt][0].x = f[rt][2].x = 0, f[rt][1] = 0;
	f[rt][0].val = 0, f[rt][1].val = f[rt][2].val = inf;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		DP(v[i].END, rt);
		// tmp[0].x = tmp[1].x = tmp[2].x = 0;
		// tmp[0].val = 0, tmp[1].val = tmp[2].val = inf;
		f[rt][2].Change(f[rt][2], f[v[i].END][2], 0, 0);
		f[rt][2].Change(f[rt][1], f[v[i].END][1], -1, v[i].v);
		f[rt][1].Change(f[rt][1], f[v[i].END][2], 0, 0);
		f[rt][1].Change(f[rt][0], f[v[i].END][1], 0, v[i].v);
		f[rt][0].Change(f[rt][0], f[v[i].END][2], 0, 0);
		// size[rt] += size[v[i].END];
	}
	f[rt][1].Change(f[rt][0], data(0, 0), 1, 0);
	f[rt][2].Change(f[rt][1], data(0, 0), 0, 0);
	f[rt][2].Change(f[rt][0], data(0, 0), 0, 0);
}
bool Solve(long long mid)
{
    MID = mid;
	DP(1, 0);
	return f[1][2].x <= K;
}
int main()
{
	// freopen ("lct2.in", "r", stdin);
    // freopen ("lct.out", "w", stdout);
	memset (first, -1, sizeof (first));
	int n = read(); K = read() + 1;
	for (int i = 1; i < n; i++)
	{
		int a = read(), b = read(), c = read();
		add(a, b, c);
		add(b, a, c);
	}
	// memset (f, 0xC0, sizeof (f));
	long long l = -1e12, r = 1e12, ans = 0;
	while (l <= r)
	{
		long long mid = (l + r) >> 1;
		if (Solve(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	MID = ans;
	DP(1, 0);
	printf ("%lld\n", f[1][2].val + 1ll * MID * K);
}
