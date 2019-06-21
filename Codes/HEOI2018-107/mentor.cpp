#pragma GCC diagnostic error "-std=c++11"
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <vector>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 205;
const int INF = 0x3f3f3f3f;
int b[MAXN], a[MAXN][MAXN][15], cnt[MAXN][MAXN], r[MAXN];
int s[MAXN], ans[MAXN], now[MAXN], Num[MAXN], C, m, n, Min[MAXN];
struct Graph
{
	struct edge
	{
		int END, cap, rev;
		edge(int _a, int _b, int _c): END(_a), cap(_b), rev(_c) {;}
	};
	vector<edge> G[MAXN * 2];
	void add(int a, int b, int f)
	{
		G[a].push_back(edge(b, f, (int)G[b].size()));
		G[b].push_back(edge(a, 0, (int)G[a].size() - 1));
	}
	int q[MAXN * 2], dis[MAXN * 2];
	bool BFS(int S, int E)
	{
		memset (dis, -1, sizeof (dis));
		int h = 1, t = 0;
		q[++t] = S;
		dis[S] = 0;
		while (h <= t)
		{
			int k = q[h++];
			for (auto x : G[k])
			{
				if (dis[x.END] == -1 && x.cap)
				{
					dis[x.END] = dis[k] + 1;
					q[++t] = x.END;
					if (E == x.END) return 1;
				}
			}
		}
		return 0;
	}
	int DFS(int S, int E, int a)
	{
		if (S == E || a == 0) return a;
		int flow = 0, f;
		for (auto &x : G[S])
		{
			if (dis[x.END] == dis[S] + 1 && (f = DFS(x.END, E, min(a, x.cap))) > 0)
			{
				x.cap -= f;
				G[x.END][x.rev].cap += f;
				flow += f;
				a -= f;
				if (!a) break;
			}
		}
		if (!flow) dis[S] = -1;
		return flow;
	}
	int Dinic(int S, int E)
	{
		int ans = 0;
		while (BFS(S, E))
			ans += DFS(S, E, 1);
		return ans;
	}
	void clear()
	{
		for (int i = 0; i <= n + m + 1; i++)
			G[i].clear();
	}
	void erase(int a, int b)
	{
		G[a].pop_back();
		G[b].pop_back();
	}
}G[MAXN * 2];
int S, E;
bool OK(int mid, int x)
{
	Graph Now = G[mid - 1];
	Now.add(S, x, 1);
	for (int i = 1; i <= s[x]; i++)
		for (int k = 1; k <= cnt[x][i]; k++)
			Now.add(x, a[x][i][k] + n, 1);
	return Now.BFS(S, E);
}
int main()
{
	// freopen ("mentor.in", "r", stdin);
	// freopen ("mentor4.in", "r", stdin);
	// freopen ("mentor.out", "w", stdout);
	int T = read(); C = read();
	while (T--)
	{
		memset (cnt, 0, sizeof (cnt));
		n = read(), m = read();
		for (int i = 1; i <= m; i++)
			b[i] = read();
		for (int i = 0; i <= n; i++) G[i].clear();
		for (int i = 1; i <= n; i++) ans[i] = m + 1;
		S = 0, E = n + m + 1;
		for (int i = 1; i <= m; i++) G[0].add(i + n, E, b[i]);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
			{
				int t = read();
				if (t != 0)
					a[i][t][++cnt[i][t]] = j;
			}
		for (int i = 1; i <= n; i++)
			s[i] = read();
		for (int i = 1; i <= n; i++) r[i] = i;
		for (int i = 1; i <= n; i++)
		{
			G[i] = G[i - 1];
			G[i].add(S, i, 1);
			for (int j = 1; j <= m; j++)
			{
				for (int k = 1; k <= cnt[i][j]; k++)
					G[i].add(i, a[i][j][k] + n, 1);
				bool flag = 0;
				if (G[i].BFS(S, E))
				{
					G[i].DFS(S, E, 1);
					ans[i] = j;
					flag = 1;
				}
				if (flag) break;
				for (int k = cnt[i][j]; k >= 1; k--)
					G[i].erase(i, a[i][j][k] + n);
			}
		}
		for (int i = 1; i <= n; i++)
			printf ("%d ", ans[i]);
		printf ("\n");
		// printf ("C == %d\n", (int)clock());
		for (int i = 1; i <= n; i++)
		{
			if (ans[i] <= s[i])
			{
				printf ("0 ");
				continue;
			}
 			int L = 1, R = i, ans = 0;
			while (L <= R)
			{
				int mid = (L + R) >> 1;
				if (OK(mid, i)) ans = mid, L = mid + 1;
				else R = mid - 1;
			}
			printf ("%d ", i - ans);
		}
		printf ("\n");
	}
}