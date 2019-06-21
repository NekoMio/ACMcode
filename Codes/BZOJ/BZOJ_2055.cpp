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
const int MAXN = 1005;
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
    int n = read(), m = read();
    memset (first, -1, sizeof (first));
    int s = 0, t = n * 2 + 2, T = n * 2 + 3, S = T + 1;
    // add(s, 1, m, 0);
    d[1] += m, d[s] -= m;
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        add(1, i << 1, INF, 0), add(i << 1 | 1, t, INF, 0);
        int k = read();
        d[i << 1] -= k, d[i << 1 | 1] += k;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            int k = read();
            if (k != -1) add(i << 1 | 1, j << 1, INF, k);
        }
    }
    add(t, s, INF, 0);
    for (int i = s; i <= t; i++)
    {
        if (d[i] > 0) add(S, i, d[i], 0);
        else if (d[i] < 0) add(i, T, -d[i], 0);
    }
    printf ("%d\n", Max_Profit(S, T));
}