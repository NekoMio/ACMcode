/*
 * @Author: WildRage 
 * @Date: 2017-07-15 15:44:55 
 * @Last Modified by: WildRage
 * @Last Modified time: 2017-07-15 16:33:45
 */
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
using namespace std;
const int INF = 0x7fffffff;
int a[105][105], b[105][105];
struct edge
{
    int S, END, next, cap, cost;
} v[2000005];
int first[50005], p;
void add(int a, int b, int f, int c)
{
    v[p].S = a, v[p].END = b, v[p].next = first[a], v[p].cap = f, v[p].cost = c, first[a] = p++;
    v[p].S = b, v[p].END = a, v[p].next = first[b], v[p].cap = 0, v[p].cost = -c, first[b] = p++;
}
int dis[50005], pre[50005];
bool vis[50005];
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
    return dis[E] != 0x3f3f3f3f;
}
int Max_Profit(int S, int T)
{
    int ans = 0, flow;
    while (Spfa(S, T))
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
int Dis(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}
int main()
{
    int n;
    memset(first, -1, sizeof(first));
    int Index = 0;
    scanf("%d",&n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            scanf("%1d", &a[i][j]);
            if (a[i][j])
                a[i][j] = ++Index;
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            scanf("%1d", &b[i][j]);
            if (b[i][j])
                b[i][j] = ++Index;
        }
    int S=0,T=50001;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (a[i][j] && !b[i][j])
            {
                add(S,a[i][j],1,0);
                for (int k = 1; k <= n; k++)
                    for (int m = 1; m <= n; m++)
                        if (!a[k][m] && b[k][m])
                            add(a[i][j], b[k][m], 1, Dis(i, j, k, m));
            }
    for (int k = 1; k <= n; k++)
        for (int m = 1; m <= n; m++)
            if (!a[k][m] && b[k][m])
                add(b[k][m],T,1,0);
    printf("%d",Max_Profit(S,T));
    //while(1);
}