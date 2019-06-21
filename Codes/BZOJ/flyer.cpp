#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
const int INF = 0x3f3f3f3f;
class Dinic
{
  public:
    struct edge
    {
        int END, next, cap;
    } v[1005];
    int first[105], p;
    Dinic()
    {
        memset(first, -1, sizeof(first));
    }
    void add(int a, int b, int c)
    {
        v[p].END = b, v[p].next = first[a], v[p].cap = c, first[a] = p++;
        v[p].END = a, v[p].next = first[b], v[p].cap = 0, first[b] = p++;
    }
    int dis[105];
    bool vis[10005];
    bool BFS(int S, int E)
    {
        memset(vis, 0, sizeof(vis));
        memset(dis, -1, sizeof(dis));
        queue<int> Q;
        Q.push(S);
        dis[S] = 0;
        vis[S] = 1;
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
    int dinic(int S, int E)
    {
        int ans = 0;
        while (BFS(S, E))
        {
            ans += DFS(S, E, INF);
        }
        return ans;
    }
} dinic;

int main(int argc, char const *argv[])
{
    freopen("flyer.in","r",stdin);
    freopen("flyer.out","w",stdout);
    int n, n1, a, b;
    scanf("%d%d", &n, &n1);
    while (scanf("%d%d", &a, &b) != EOF)
        dinic.add(a, b, 1);
    int S = 0, T = n + 1;
    for (int i = 1; i <= n1; i++)
    {
        dinic.add(S, i, 1);
    }
    for (int i = n1 + 1; i <= n; i++)
    {
        dinic.add(i, T, 1);
    }
    printf("%d\n", dinic.dinic(S, T));
    return 0;
}
