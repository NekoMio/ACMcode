#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define int long long
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 2e5;
const int INF = 0x3f3f3f3f;
struct edge
{
    int END, next, cap;
}v[1000005];
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
    queue<int> Q;
    memset (vis, 0, sizeof (vis));
    memset (dis, -1, sizeof (dis));
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
                Q.push(v[i].END);
            }
        }
    }
    return vis[E];
}
int DFS(int S, int E, int a)
{
    if (S == E || a == 0) return a;
    int flow = 0, f;
    for (int i = first[S]; i != -1; i = v[i].next)
    {
        if (dis[v[i].END] == dis[S] + 1 && (f = DFS(v[i].END, E, min(a, v[i].cap))) > 0)
        {
            a -= f;
            flow += f;
            v[i].cap -= f;
            v[i ^ 1].cap += f;
            if (a == 0) break;
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
char s[105];
int a[105], b[105];
int w[105][105], ID[105][105], id[105], Id[15], Index;
signed main()
{
	int T = read();
	while (T--)
	{
		memset (first, -1, sizeof (first));
		Index = 0;
		int n = read();
		scanf ("%s", s + 1);
		for (int i = 0; i <= 9; i++)
			a[i] = read(), b[i] = read();
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				w[i][j] = read(), ID[i][j] = ++Index;
		int S = ++Index, T = ++Index;
		for (int i = 0; i <= 9; i++)
		{
			Id[i] = ++Index;
			add(Id[i], T, b[i] - a[i]);
		}
		for (int i = 1; i <= n; i++)
		{
			id[i] = ++Index;
			// add(Id[s[i] - '0'], id[i], INF);
			add(id[i], Id[s[i] - '0'], INF);
			// add(S, id[i], a[s[i] - '0']);
			add(id[i], T, a[s[i] - '0']);
			for (int j = 1; j <= n; j++)
				if (i != j)
				{
					add(ID[i][j], id[i], INF);
					add(ID[j][i], id[i], INF);
				}
		}
		int ans = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (i != j)
				{
					add(S, ID[i][j], w[i][j]);
					ans += w[i][j];
				}
		// printf ("%d\n", ans);
		printf ("%lld\n", ans - Dinic(S, T));
	}
}
