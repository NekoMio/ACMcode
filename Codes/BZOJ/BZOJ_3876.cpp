#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 305;
const int INF = 0x3f3f3f3f;
struct edge
{
    int S, END, next, v, cap;
}v[MAXN * 100];
int first[MAXN], p;
void add(int a, int b, int f, int c)
{
    v[p].END = b, v[p].S = a, v[p].next = first[a], v[p].v = c, v[p].cap = f, first[a] = p++;
    v[p].END = a, v[p].S = b, v[p].next = first[b], v[p].v =-c, v[p].cap = 0, first[b] = p++;
}
bool vis[MAXN];
int dis[MAXN], pre[MAXN];
bool Spfa(int S, int E)
{
    memset (pre, -1, sizeof (pre));
    memset (dis, 0x3f, sizeof (dis));
    memset (vis, 0, sizeof (vis));
    vis[S] = 1;
    dis[S] = 0;
    queue<int> Q;
    Q.push(S);
    while(!Q.empty())
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
int d[MAXN];
int main()
{
    // freopen ("story8.in", "r", stdin);
    int n = read();
    memset (first, -1, sizeof (first));
    int S = 0, T = n + 1;
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int m = read();
        // add(i, T, m, 0);
        for (int j = 1; j <= m; j++)
        {
            int a = read(), b = read();
            add(i, a, INF, b);
            // add(S, a, 1, b);
            d[a] += 1, d[i] -= 1;
            ans += b;
        }
    }
    for (int i = 2; i <= n; i++)
        add(i, 1, INF, 0);
    for (int i = 1; i <= n; i++)
    {
        if (d[i] > 0) add(S, i, d[i], 0);
        if (d[i] < 0) add(i, T, -d[i], 0);
    }
    printf ("%d\n", ans + Max_Profit(S, T));
}