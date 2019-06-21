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
const int MAXN = 120005;
struct edge
{
	int END, next, cap;
}v[2000005];
int first[MAXN], p;
void add(int a, int b, int f)
{
	// fprintf (stderr, "%d %d %d\n", a, b, f);
	v[p].END = b, v[p].next = first[a], v[p].cap = f, first[a] = p++;
	v[p].END = a, v[p].next = first[b], v[p].cap = 0, first[b] = p++;
}
int dis[MAXN];
int q[MAXN];
const int INF = 0x3f3f3f3f;
bool BFS(int S, int E)
{
	memset (dis, -1, sizeof (dis));
	int h = 1, t = 0;
	q[++t] = S;
	dis[S] = 0;
	while (h <= t)
	{
		int k = q[h++];
		for (int i = first[k]; i != -1; i = v[i].next)
		{
			if (dis[v[i].END] == -1 && v[i].cap > 0)
			{
				dis[v[i].END] = dis[k] + 1;
				q[++t] = v[i].END;
				if (v[i].END == E) return 1;
			}
		}
	}
	return 0;
}
int DFS(int S, int E, int a)
{
	if (S == E || a == 0) return a;
	int flow = 0, f;
	for (int i = first[S]; i != -1; i = v[i].next)
	{
		if (dis[v[i].END] == dis[S] + 1 && (f = DFS(v[i].END, E, min(a, v[i].cap))) > 0)
		{
			v[i].cap -= f;
			v[i ^ 1].cap += f;
			flow += f;
			a -= f;
			if (a == 0) break;
		}
	}
	if (!flow) dis[S] = -1;
	return flow;
}
int Dinic(int S, int T)
{
	int ans = 0;
	while (BFS(S, T))
		ans += DFS(S, T, INF);
	return ans;
}
int n[2], x[2][MAXN], y[2][MAXN];
int id[2][MAXN], Index;
int X[MAXN], Y[MAXN];
bool vis[MAXN];
void DFS(int rt, int c)
{
	vis[rt] = 1;
	// fprintf (stderr, "%d\n", rt);
	for (int i = first[rt]; i != -1; i = v[i].next)
		if (v[i].cap == c && !vis[v[i].END])
			DFS(v[i].END, c);
}
int main()
{
	#ifdef Mine
	freopen ("uno.8.1.in", "r", stdin);
	#endif
	memset (first, -1, sizeof (first));
	int m = read(), c = read();
	for (int i = 0; i <= 1; i++)
	{
		n[i] = read();
		for (int j = 1; j <= n[i]; j++)
		{
			x[i][j] = read(), y[i][j] = read();
			id[i][j] = ++Index;
		}
	}
	for (int i = 1; i <= m; i++) X[i] = ++Index;
	for (int j = 1; j <= c; j++) Y[j] = ++Index;
	fprintf (stderr, "=============");
	int S = ++Index, T = ++Index;
	for (int j = 1; j <= n[0]; j++)
	{
		add(S, id[0][j], 1);
		add(id[0][j], X[x[0][j]], 1);
		add(id[0][j], Y[y[0][j]], 1);
	}
	for (int k = 1; k <= n[1]; k++)
	{
		add(id[1][k], T, 1);
		add(X[x[1][k]], id[1][k], 1);
		add(Y[y[1][k]], id[1][k], 1);
	}
	fprintf (stderr, "%d\n", Dinic(S, T));
	memset (vis, 0, sizeof (vis));
	DFS(S, 1);
	for (int i = 1; i <= n[0]; i++)
		if (vis[id[0][i]])
			printf ("0\n");
		else
			printf ("1\n");
}
