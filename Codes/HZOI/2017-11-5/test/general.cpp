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
const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;
struct edge
{
	int END, next;
}v[N << 1];
int first[N], p;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
int f[N][2];
int n, k, t, ans;
void dfs(int rt, int fa)
{
	f[rt][1] = INF;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dfs(v[i].END, rt);
	}
	if (f[rt][0] + f[rt][1] <= k) f[rt][0] = -INF;
	if (f[rt][0] == k) f[rt][1] = 0, /*printf ("%d ", rt), */ ans++, f[rt][0] = -INF;
	f[fa][0] = max(f[fa][0], f[rt][0] + 1);
	f[fa][1] = min(f[fa][1], f[rt][1] + 1);
}
int main()
{
	freopen("general.in", "r", stdin);
	freopen("general.out", "w", stdout);
	n = read(), k = read(), t = read();
	memset (first, -1, sizeof (first));
	int a, b;
	for (int i = 1; i < n; i++)
	{
		a = read(), b = read();
		add(a, b);
		add(b, a);
	}
	dfs(1, 0);
	if (f[1][0] >= 0) ans++;
	printf ("%d\n", ans);
}
