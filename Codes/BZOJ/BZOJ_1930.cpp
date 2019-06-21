#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1000005;
const int INF = 0x3f3f3f3f;
struct edge
{
    int S, END, next, cap, cost;
} v[MAXN << 1];
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
    memset(dis, -1, sizeof(dis));
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
            if (dis[v[i].END] < dis[u] + v[i].cost)
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
struct Node 
{
    int x, y;
    bool operator < (const Node &B) const 
    {
        return x < B.x || (x == B.x && y < B.y);
    }
}X[MAXN];
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
        X[i].x = read(), X[i].y = read();
    sort(X + 1, X + n + 1);
    memset (first, -1, sizeof (first));
    add(0, 1, 2, 0);
    int T = 2 * n + 2;
    for (int i = 1; i <= n; i++)
    {
        add(1, i << 1, 1, 0);
        add(i << 1 | 1, T, 1, 0);
        add(i << 1, i << 1 | 1, 1, 1);
        add(i << 1, i << 1 | 1, 1, 0);
    }
    for (int i = 1; i <= n; i++)
    {
        int Min = INF;
        for (int j = i + 1; j <= n; j++)
        {
            if (X[j].y < Min && X[j].y >= X[i].y)
                add(i << 1 | 1, j << 1, 2, 0);
            if (X[j].y >= X[i].y)
                Min = min(Min, X[j].y);
        }
    }
    printf ("%d\n", Max_Profit(0, T));
    // while (1);
}