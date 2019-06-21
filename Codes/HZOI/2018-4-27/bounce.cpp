#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 1805;
struct edge
{
	int S, END, next, cap, v;
}v[200005];
int first[MAXN], p;
void add(int a, int b, int c, int d)
{
	// printf ("%d %d %d %d\n", a, b, c, d);
	v[p].S = a, v[p].END = b, v[p].next = first[a], v[p].cap = c, v[p].v = d, first[a] = p++;
	v[p].S = b, v[p].END = a, v[p].next = first[b], v[p].cap = 0, v[p].v =-d, first[b] = p++;
}
int dis[MAXN], pre[MAXN];
bool vis[MAXN];
int q[1000005];
bool SPFA(int S, int E)
{
    memset (vis, 0, sizeof (vis));
    memset (dis, 0x80, sizeof (dis));
    memset (pre, -1, sizeof (pre));
    vis[E] = 1;
    dis[E] = 0;
    int h = 1, t = 0;
    q[++t] = E;
    // Q.push(S);
    while (h <= t)
    {
        int k = q[h++];
        vis[k] = 0;
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].END] < dis[k] + v[i ^ 1].v && v[i ^ 1].cap)
            {
            	dis[v[i].END] = dis[k] + v[i ^ 1].v;
            	pre[v[i].END] = i;
            	if (!vis[v[i].END])
            	{
            		q[++t] = v[i].END;
            		// Q.push(v[i].END);
            		vis[v[i].END] = 1;
            	}
            }
        }
    }
    return dis[S] != (int)0x80808080;
}
int res;
int DFS(int S, int E, int a)
{
	vis[S] = 1;
	if (S == E || a == 0) return a;
	int flow = 0, f;
	for (int i = first[S]; i != -1; i = v[i].next)
	{
		if (!vis[v[i].END] && v[i].cap && dis[v[i].END] == dis[S] - v[i].v)
		{
			f = DFS(v[i].END, E, min(a, v[i].cap));
			v[i].cap -= f, v[i ^ 1].cap += f;
			a -= f, flow += f;
			res += f * v[i].v;
			if (!a) break;
		}
	}
	return flow;
}
int mp[35][35];
int ID[35][35][2], Index, c[35][35], r[35][35], Color[35][35];
int main()
{
	int T = read();
	while (T--)
	{
		memset (first, -1, sizeof (first)), p = 0;
		Index = 0;
		memset (mp, 0, sizeof (mp));
		int n = read(), m = read();
		for (int i = 1; i <= n; i++)
			for (int j = 1; j < m; j++)
				c[i][j] = read();
		for (int i = 1; i < n; i++)
			for (int j = 1; j <= m; j++)
				r[i][j] = read();
		int K = read();
		for (int i = 1; i <= K; i++)
		{
			int a = read(), b = read();
			mp[a][b] = 1;
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
			{
				Color[i][j] = (i + j) & 1;
				// printf ("%d%c", Color[i][j], " \n"[j == m]);
			}
		int S = ++Index, T = ++Index;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
			{
				ID[i][j][0] = ++Index, ID[i][j][1] = ++Index;
				if (!mp[i][j]) add(ID[i][j][0], ID[i][j][1], 1, 0);
				// else d[ID[i][j][0]]++, d[ID[i][j][1]]--;
				add(S, ID[i][j][0], 1, 0);
				add(ID[i][j][1], T, 1, 0);
			}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
			{
				if (i > 1 && Color[i][j])
					add(ID[i][j][0], ID[i - 1][j][1], 1, r[i - 1][j]);
				if (i < n && Color[i][j])
					add(ID[i][j][0], ID[i + 1][j][1], 1, r[i][j]);
				if (j > 1 && !Color[i][j])
					add(ID[i][j][0], ID[i][j - 1][1], 1, c[i][j - 1]);
				if (j < m && !Color[i][j])
					add(ID[i][j][0], ID[i][j + 1][1], 1, c[i][j]);
			}
		int flow = 0;
		res = 0;
		while (SPFA(S, T))
		{
			vis[T] = 1;
			while (vis[T])
			{
				memset (vis, 0, sizeof (vis));
				flow += DFS(S, T, INF);
			}
		}
		if (flow != n * m) printf ("Impossible\n");
		else printf ("%d\n", res);
	}
}
