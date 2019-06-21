#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
const int N = 105;
const int INF = 0x7fffffff;
struct edge
{
    int END, next, cap;
} v[10005];
int first[600], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].cap = c;
    first[a] = p++;
    v[p].END = a;
    v[p].next = first[b];
    v[p].cap = 0;
    first[b] = p++;
}
int dis[10005];
bool vis[10005];
bool BFS(int S, int E)
{
    memset(vis, 0, sizeof(vis));
    memset(dis, -1, sizeof(dis));
    queue<int> Q;
    dis[S] = 0;
    vis[S] = 1;
    Q.push(S);
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (int i = first[u]; i != -1; i = v[i].next)
        {
            if (!vis[v[i].END] && v[i].cap > 0)
            {
                vis[v[i].END] = 1;
                dis[v[i].END] = dis[u] + 1;
                if (v[i].END == E)
                    return 1;
                Q.push(v[i].END);
            }
        }
    }
    return 0;
}
int DFS(int S, int E, int a)
{
    if (S == E || a == 0)
        return a;
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
    if (!flow)
        dis[S] = -1;
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
int id(int a, int b)
{
    return a + b * N;
}
int main()
{
    memset(first,-1,sizeof(first));
    int f, d, n;
    int T = 420;
    int a, b;
    scanf("%d%d%d", &n, &f, &d);
    for (int i = 1; i <= f; i++)
        add(0, id(i, 1), 1);
    for (int i = 1; i <= d; i++)
        add(id(i, 2), T, 1);
    int fi = 0, di = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &fi, &di);
        while(fi--)
        {
            scanf("%d",&a);
            add(id(a, 1), id(i, 0), 1);
        }
        while(di--)
        {
            scanf("%d",&b);
            add(id(i, 3), id(b, 2), 1);
        }
        add(id(i, 0), id(i, 3), 1);
    }
    printf("%d", Dinic(0, T));
}
