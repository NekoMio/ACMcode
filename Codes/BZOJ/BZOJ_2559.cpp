#include <cstdio>
#include <cstring>
#include <algorithm>

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

// #define int long long
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN = 200005;
int K;
struct edge
{
	int END, next, v;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b, int c)
{
	v[p].END = b;
	v[p].next = first[a];
	v[p].v = c;
	first[a] = p++;
}
int size[MAXN], Max[MAXN], sum, root;
bool vis[MAXN];
void Get_root(int rt, int fa)
{
	size[rt] = 1, Max[rt] = 0;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (!vis[v[i].END] && v[i].END != fa)
		{
			Get_root(v[i].END, rt);
			size[rt] += size[v[i].END];
			Max[rt] = max(Max[rt], size[v[i].END]);
		}
	}
	Max[rt] = max(Max[rt], sum - size[rt]);
	if (Max[rt] < Max[root]) root = rt;
}

int dis[MAXN], t[MAXN * 5], ans, d[MAXN];
void Calc(int rt, int fa)
{
	if (dis[rt] <= K) 
		ans = min(ans, d[rt] + t[K - dis[rt]]);
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END != fa && !vis[v[i].END])
		{
			d[v[i].END] = d[rt] + 1;
			dis[v[i].END] = dis[rt] + v[i].v;
			Calc(v[i].END, rt);
		}
	}
}
void Update(int rt, int fa, int flag)
{
	if (dis[rt] <= K)
	{
		if (flag) t[dis[rt]] = min(t[dis[rt]], d[rt]);
		else t[dis[rt]] = INF;
	}
	for (int i = first[rt]; i != -1; i = v[i].next)
		if (v[i].END != fa && !vis[v[i].END])
			Update(v[i].END, rt, flag);
}
void Solve(int rt)
{
	vis[rt] = 1, t[0] = 0;
	for (int i = first[rt]; i != -1; i = v[i].next)
		if (!vis[v[i].END])
		{
			d[v[i].END] = 1, dis[v[i].END] = v[i].v;
			Calc(v[i].END, 0);
			Update(v[i].END, 0, 1);
		}
	for (int i = first[rt]; i != -1; i = v[i].next)
		if (!vis[v[i].END])
			Update(v[i].END, 0, 0);
	for (int i = first[rt]; i != -1; i = v[i].next)
		if (!vis[v[i].END])
		{
			root = 0, sum = size[v[i].END];
			Get_root(v[i].END, 0);
			Solve(root);
		}
}

signed main()
{
	memset (first, -1, sizeof (first));
	int n = read();
	K = read();
	int a, b, c;
	for (int i = 0; i <= K; i++) t[i] = n;
	for (int i = 1; i < n; i++)
	{
		a = read() + 1, b = read() + 1, c = read();
		add(a, b, c);
		add(b, a, c);
	}
	ans = n;
	Max[0] = sum = n;
	Get_root(1, 0);
	Solve(root);
	if (ans == n) ans = -1;
	printf ("%d\n", ans);
}