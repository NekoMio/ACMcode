#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 100005;
struct edge
{
    int END, next, cap;
}v[MAXN << 1];
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
    memset (dis, -1, sizeof (dis));
    memset (vis, 0, sizeof (vis));
    dis[S] = 0;
    vis[S] = 1;
    Q.push(S);
    while (!Q.empty())
    {
        int k = Q.front(); Q.pop();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (!vis[v[i].END] && v[i].cap > 0)
            {
                dis[v[i].END] = dis[k] + 1;
                vis[v[i].END] = 1;
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
int Dinic(int S, int E)
{
    int ans = 0;
    while (BFS(S, E)) ans += DFS(S, E, INF);
    return ans;
}
int id[105][105], Idx[1005];
int Index;
int a[105];
int mp[105][105];
int main()
{
    memset (first, -1, sizeof (first));
    int n = read(), m = read();
    int Mx = 0;
    for (int i = 1; i <= n; i++) 
        a[i] = read(), Mx = max(Mx, a[i]);
    int T = ++Index, S = ++Index;
    for (int i = 1; i <= Mx; i++)
    {
        Idx[i] = ++Index;
        add(Idx[i], T, m * i * i);
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            id[i][j] = ++Index;
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
        {
            int x = read();
            if (i == j) x -= a[i], add(id[i][j], Idx[a[i]], INF);
            else
            {
                add(id[i][j], id[i][j - 1], INF);
                add(id[i][j], id[i + 1][j], INF);
            }
            if (x > 0) ans += x, add(S, id[i][j], x);
            else add(id[i][j], T, -x);
        }
    printf ("%d\n", ans - Dinic(S, T));
}