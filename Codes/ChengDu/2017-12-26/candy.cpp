#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

const int INF = 0x3f3f3f3f;
const int MAXN = 1e5 + 3;
struct edge
{
	int END, next, cap;
}v[MAXN];
int first[MAXN], p;
void add(int a, int b, int c)
{
	v[p].END = b, v[p].next = first[a], v[p].cap = c, first[a] = p++;
	v[p].END = a, v[p].next = first[b], v[p].cap = 0, first[b] = p++; 
}
int dis[MAXN];
bool vis[MAXN];
bool BFS(int S, int E)
{
	memset (vis, 0, sizeof (vis));
	memset (dis, -1, sizeof (dis));
	queue<int> Q;
	vis[S] = 1;
	dis[S] = 0;
	Q.push(S);
	while (!Q.empty())
	{
		int k = Q.front();
		Q.pop();
		for (int i = first[k]; i != -1; i = v[i].next)
		{
			if (!vis[v[i].END] && v[i].cap > 0)
			{
				vis[v[i].END] = 1;
				dis[v[i].END] = dis[k] + 1;
				if (v[i].END == E) return 1;
				Q.push(v[i].END);
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
		if (dis[v[i].END] == dis[S] + 1 && (f = DFS(v[i].END, E, min(a, v[i].cap)) > 0))
		{
			v[i].cap -= f;
			v[i ^ 1].cap += f;
			a -= f;
			flow += f;
			if (f == 0)
				break;
		}
	}
	if (!flow) dis[S] = -1;
	return flow;
}

int Dinic(int S, int E)
{
	int ans = 0;
	while (BFS(S, E))
	{
		ans += DFS(S, E, INF);
	}
	return ans;
}


int Num[35][205];
bool flag[35][205];
int main()
{
	freopen("candy.in", "r", stdin);
	freopen("candy.out", "w", stdout);
	memset (first, -1, sizeof(first));
	int n = read(), m = read();
	for (int i = 1; i <= m; i++)
	{
		int k = read();
		for (int j = 1; j <= k; j++)
			Num[i][read()]++;
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		if (Num[1][i]) flag[1][i] = 1, cnt++;
		if (Num[1][i] >= 2)
			add(0, i, INF);
	}
	for (int i = 1; i <= n; i++)
		if (!flag[1][i]) add(i, n + 1, 1);
	for (int i = 2; i <= m; i++)
	{
		for (int j = 1; j <= n; j++) if (Num[i][j]) flag[i][j] = 1;
		for (int j = 1; j <= n; j++)
		{
			if (Num[i][j] < 2 || flag[1][j]) continue;
			for (int k = 1; k <= n; k++)
			{
				if (Num[1][k] >= 2 && !flag[i][k])
					add(k, j, 1);
			}
		}
	}
	printf ("%d\n", Dinic(0, n + 1) + cnt);
}
