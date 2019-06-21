#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f;
class Mincost
{
  public:
    int first[20005], p;
    Mincost()
    {
        memset(first, -1, sizeof(first));
    }
    class edge
    {
      public:
        int END, S, next, cap, cost;
    } v[100005];

    void add(int a, int b, int f, int c)
    {
        v[p].END = b, v[p].next = first[a], v[p].S = a, v[p].cap = f, v[p].cost = c, first[a] = p++;
        v[p].END = a, v[p].next = first[b], v[p].S = b, v[p].cap = 0, v[p].cost = -c, first[b] = p++;
    }
    int dis[20005], pre[20005];
    bool vis[20005];
    bool spfa(int S, int E)
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
        return dis[E] != 0x3f3f3f3f;
    }
    int MinCost(int S, int T)
    {
        int ans = 0, flow;
        while (spfa(S, T))
        {
            flow = INF;
            for (int i = pre[T]; i != -1; i = pre[v[i].S])
                flow = min(flow, v[i].cap);
            for (int i = pre[T]; i != -1; i = pre[v[i].S])
                v[i].cap -= flow, v[i ^ 1].cap += flow;
            ans += dis[T] * flow;
        }
        return ans;
    }
} Min;
int a[205];
int main(int argc, char const *argv[])
{
    freopen("napkin.in","r",stdin);
    freopen("napkin.out","w",stdout);
    int n, p, m, f, c, s;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
    }
    scanf("%d%d%d%d%d", &p, &m, &f, &c, &s);
    int S = 0, T = n * 3;
    for (int i = 1; i <= n; i++)
    {
        Min.add(S, i, a[i], 0);
        Min.add(n + i, T, a[i], 0);
        Min.add(S, i + n, INF, p);
        //Min.add(i, i + n, a[i], 0);
        if (i + 1 <= n)
            Min.add(i, i + 1, INF, 0);
        if (i + m <= n)
            Min.add(i, i + n + m, INF, f);
        if (i + c <= n)
            Min.add(i, i + n + c, INF, s);
    }
    printf("%d", Min.MinCost(S, T));
    return 0;
}
