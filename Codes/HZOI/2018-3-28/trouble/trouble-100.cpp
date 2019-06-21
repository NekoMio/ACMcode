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
char s[50];
int mp[50][50];
int Color[50][50];
int ID[50][50][4], Index;
const int MAXN = 6005;
const int INF = 0x3f3f3f3f;
struct edge
{
    int S, END, next, cap, cost;
} v[MAXN * 20];
int first[MAXN], p;
void add(int a, int b, int f, int c)
{
    v[p].S = a, v[p].END = b, v[p].next = first[a], v[p].cap = f, v[p].cost = c, first[a] = p++;
    v[p].S = b, v[p].END = a, v[p].next = first[b], v[p].cap = 0, v[p].cost = -c, first[b] = p++;
}
int dis[MAXN], pre[MAXN];
bool vis[MAXN];
bool Spfa(int S, int E)
{
    memset(dis, 0x3f, sizeof(dis));
    memset(pre, -1, sizeof(pre));
    memset(vis, 0, sizeof(vis));
    queue<int> Q;
    Q.push(S);
    vis[S] = 1;
    dis[S] = 0;
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        vis[u] = 0;
        for (int i = first[u]; i != -1; i = v[i].next)
        {
            if (!v[i].cap)
                continue;
            if (dis[v[i].END] > dis[u] + v[i].cost)
            {
                dis[v[i].END] = dis[u] + v[i].cost;
                pre[v[i].END] = i;
                if (!vis[v[i].END])
                {
                    vis[v[i].END] = 1;
                    Q.push(v[i].END);
                }
            }
        }
    }
    return dis[E] != -1;
}
int t;
int Max_Profit(int S, int T, int Q)
{
    int ans = 0, flow;
    while (Spfa(S, T) && Q)
    {
        flow = 1;
        for (int i = pre[T]; i != -1; i = pre[v[i].S])
            flow = min(flow, v[i].cap);
        for (int i = pre[T]; i != -1; i = pre[v[i].S])
            v[i].cap -= flow, v[i ^ 1].cap += flow;
        ans += dis[T] * flow;
		if (t >= 8 && t <= 12) printf ("%d\n", ans > 0 ? 1 : 0);
		else printf ("%d\n", ans);
		Q--;
    }
    return ans;
}
int main()
{
	memset (first, -1, sizeof (first));
	t = read();
	int n = read(), m = read(), A = read(), B = read();
	for (int i = 1; i <= n; i++)
	{
		scanf ("%s", s + 1);
		for (int j = 1; j <= m; j++)
			mp[i][j] = (s[j] == '0');
	}
	int Q = read();
	int S = ++Index, T = ++Index;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			Color[i][j] = (i & 1) ^ (j & 1);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			for (int k = 0; k <= 2; k++)
				ID[i][j][k] = ++Index;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if (!mp[i][j]) continue;
			if (Color[i][j])
			{
				add(S, ID[i][j][0], 1, 0);
				add(S, ID[i][j][0], 1, A);
				add(S, ID[i][j][0], 1, 2 * A);
				add(S, ID[i][j][0], 1, 3 * A);
				add(ID[i][j][0], ID[i][j][1], 1, 0);
				add(ID[i][j][0], ID[i][j][1], 1, B - A);
				add(ID[i][j][0], ID[i][j][2], 1, 0);
				add(ID[i][j][0], ID[i][j][2], 1, B - A);
				if (j < m) add(ID[i][j][1], ID[i][j + 1][1], 1, 0);
				if (j > 1) add(ID[i][j][1], ID[i][j - 1][1], 1, 0);
				if (i < n) add(ID[i][j][2], ID[i + 1][j][2], 1, 0);
				if (i > 1) add(ID[i][j][2], ID[i - 1][j][2], 1, 0);
			}
			else
			{
				add(ID[i][j][2], ID[i][j][0], 1, 0);
				add(ID[i][j][2], ID[i][j][0], 1, B - A);
				add(ID[i][j][1], ID[i][j][0], 1, 0);
				add(ID[i][j][1], ID[i][j][0], 1, B - A);
				add(ID[i][j][0], T, 1, 0);
				add(ID[i][j][0], T, 1, A);
				add(ID[i][j][0], T, 1, 2 * A);
				add(ID[i][j][0], T, 1, 3 * A);
			}
		}
	Max_Profit(S, T, Q);
}