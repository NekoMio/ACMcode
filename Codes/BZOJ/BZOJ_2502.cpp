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
#define int long long
const int MAXN = 100005;
const int INF = 0x3f3f3f3f;
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
    memset (vis, 0, sizeof (vis));
    memset (dis, -1, sizeof (dis));
    queue<int> Q;
    vis[S] = 1;
    dis[S] = 0;
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
    while (BFS(S, E))
    {
        ans += DFS(S, E, INF);
    }
    return ans;
}
int B[MAXN], in[MAXN], out[MAXN];
signed main()
{
    int n = read();
    memset (first, -1, sizeof (first));
    int s = 0, t = n + 1, S = t + 1, T = S + 1;
    for (int i = 1; i <= n; i++)
    {
        int m = read();
        for (int j = 1; j <= m; j++)
        {
            int x = read();
            add(i, x, INF);
            B[i]--, B[x]++;
            in[x]++, out[i]++;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        add(s, i, INF);
        if (out[i] == 0) add(i, t, INF);
    }
    for (int i = 1; i <= n; i++)
    {
        if (B[i] > 0) add(S, i, B[i]);
        else if (B[i] < 0) add(i, T, -B[i]);   
    }
    Dinic(S, T);
    add(t, s, INF);
    Dinic(S, T);
    printf ("%lld\n", v[p - 1].cap);
}