#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <ctime>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 4005;
const int MAXM = 2e5 + 5;
const int INF = 0x3f3f3f3f;
const double eps = 1e-6;
struct data
{
	int a, b, v;
}b[MAXM];
int a[MAXN], W[MAXN];
int n, m;
struct Dinic_data
{
	struct edge
	{
		int END, next;
		int cap;
	}v[MAXM * 10];
	int first[MAXN], p;
	void add(int a, int b, int c)
	{
		v[p].END = b, v[p].next = first[a], v[p].cap = c, first[a] = p++;
		v[p].END = a, v[p].next = first[b], v[p].cap = 0, first[b] = p++;
	}
	int dis[MAXN], Q[MAXN];
	bool BFS(int S, int T)
	{
		memset (dis, -1, sizeof (dis));
		dis[S] = 0;
		int h = 1, t = 0;
		Q[++t] = S;
		while (h <= t)
		{
			int k = Q[h++];
			for (int i = first[k]; i != -1; i = v[i].next)
			{
				if (dis[v[i].END] == -1 && v[i].cap > 0)
				{
					dis[v[i].END] = dis[k] + 1;
					if (v[i].END == T) return 1;
					Q[++t] = v[i].END;
				}
			}
		}
		return 0;
	}
	int DFS(int S, int T, int a)
	{
		if (S == T || a == 0) return a;
		int flow = 0, f;
		for (int i = first[S]; i != -1; i = v[i].next)
		{
			if (dis[v[i].END] == dis[S] + 1 && (f = DFS(v[i].END, T, min(a, v[i].cap))) > 0)
			{
				v[i].cap -= f;
				v[i ^ 1].cap += f;
				flow += f;
				a -= f;
				if (a == 0) break;
			}
		}
		if (flow == 0) dis[S] = -1;
		return flow;
	}
	int Dinic(int S, int T)
	{
		int ans = 0;
		while (BFS(S, T))
			ans += DFS(S, T, INF);
		return ans;
	}
	bool Judge(int x)
	{
		memset (first, -1, sizeof (first)), p = 0;
		int S = 0, T = n + 1;
		int ans = 0;
		for (int i = 1; i <= m; i++)
		{
			add(b[i].a, b[i].b, b[i].v);
			add(b[i].b, b[i].a, b[i].v);
			ans += 2 * b[i].v;
		}
		for (int i = 1; i <= n; i++)
			add(i, T, 2 * x * a[i]), add(S, i, W[i]);
		
		return ans - Dinic(S, T) > 0;
	}
}D;
int main()
{
	// freopen ("1.in", "r", stdin);
	// freopen ("1.out", "w", stdout);
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1; i <= m; i++)
	{
		b[i].a = read(), b[i].b = read(), b[i].v = read();
		W[b[i].a] += b[i].v, W[b[i].b] += b[i].v;
	}
	int l = 0, ans = 0, r = 10000;
	while (l <= r)
	{
		int mid = (l + r) / 2;
		if (D.Judge(mid)) ans = mid, l = mid + 1;
		else r = mid - 1;
		// printf ("%.3f\n", (double)clock() / CLOCKS_PER_SEC);
	}
	// if (C.Judge(1.0 * ans + 1 - 1e-19)) ans++;
	printf ("%d\n", ans);
	// printf ("%.3f\n", (double)clock() / CLOCKS_PER_SEC);
	while (1);
}
