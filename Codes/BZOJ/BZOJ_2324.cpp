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
const int MAXN = 1005;
struct edge
{
    int S, END, next, cap, v;
}v[MAXN * 100];
int first[MAXN], p;
void add(int a, int b, int f, int c)
{
    v[p].END = b, v[p].S = a, v[p].next = first[a], v[p].cap = f, v[p].v = c, first[a] = p++;
    v[p].END = a, v[p].S = b, v[p].next = first[b], v[p].cap = 0, v[p].v =-c, first[b] = p++;
}
int dis[MAXN], pre[MAXN];
bool vis[MAXN];
bool Spfa(int S, int E)
{
    memset (dis, 0x3f, sizeof (dis));
    memset (vis, 0, sizeof (vis));
    memset (pre, -1, sizeof (pre));
    dis[S] = 0;
    vis[S] = 1;
    queue<int> Q;
    Q.push(S);
    while (!Q.empty())
    {
        int k = Q.front(); Q.pop();
        vis[k] = 0;
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (v[i].cap == 0) continue;
            if (dis[v[i].END] > dis[k] + v[i].v)
            {
                dis[v[i].END] = dis[k] + v[i].v;
                pre[v[i].END] = i;
                if (!vis[v[i].END]) 
                {
                    Q.push(v[i].END);
                    vis[v[i].END] = 1;
                }
            }
        }
    }
    return dis[E] != 0x3f3f3f3f;
}
int Min_Profit(int S, int T)
{
    int ans = 0, flow;
    while (Spfa(S, T))
    {
        flow = INF;
        for (int i = pre[T]; i != -1; i = pre[v[i].S])
            flow = min(flow, v[i].cap);
        for (int i = pre[T]; i != -1; i = pre[v[i].S])
            v[i].cap -= flow, v[i ^ 1].cap += flow;
        ans += flow * dis[T];
    }
    return ans;
}
int map[155][155];
int main()
{
    memset (first, -1, sizeof (first));
    int n = read(), m = read(), k = read();
    memset (map, 0x3f, sizeof (map));
    for (int i = 1; i <= m; i++)
    {
        int a = read(), b = read(), c = read();
        map[a][b] = map[b][a] = min(map[a][b], c);
    }
    for (int i = 0; i <= n; i++) map[i][i] = 0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            for (int s = 0; s <= n; s++)
                if ((i <= s) || (i <= j))
                    map[j][s] = min(map[j][s], map[j][i] + map[i][s]);
    int t = n * 2 + 2, S = 0;
    for (int i = 1; i <= n; i++)
    {
        add(S, i << 1 | 1, 1, 0);
        add(i << 1, t, 1, 0);
    }
    add(S, 1, k, 0);
    for (int i = 0; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (map[i][j] != 0x3f3f3f3f) add(i << 1 | 1, j << 1, 1, map[i][j]);
    printf ("%d", Min_Profit(S, t));
}