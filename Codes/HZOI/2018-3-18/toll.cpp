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
const int MAXN = 105;
const int MAXM = 2505;
const long long INF = 0x3f3f3f3f3f3f3f3fll;
struct edge
{
    int END, next;
    long long cap;
}v[MAXM << 2];
int first[MAXN], p;
void add(int a, int b, long long c)
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
    Q.push(S);
    vis[S] = 1;
    dis[S] = 0;
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (!vis[v[i].END] && v[i].cap > 0)
            {
                vis[v[i].END] = 1;
                dis[v[i].END] = dis[k] + 1;
                Q.push(v[i].END);
            }
        }
    }
    return vis[E];
}
long long DFS(int S, int E, long long a)
{
    if (S == E || a == 0) return a;
    long long flow = 0, f;
    for (int i = first[S]; i != -1; i = v[i].next)
    {
        if (dis[v[i].END] == dis[S] + 1 && (f = DFS(v[i].END, E, min(a, v[i].cap))) > 0)
        {
            a -= f;
            flow += f;
            v[i].cap -= f;
            v[i ^ 1].cap += f;
            if (a == 0) break;
        }
    }
    if (flow == 0) dis[S] = -1;
    return flow;
}
long long Dinic(int S, int E)
{
    long long ans = 0;
    while (BFS(S, E))
    {
        ans += DFS(S, E, INF);
        if (ans >= INF) return -1;
    }
    return ans;
}
int main()
{
    memset (first, -1, sizeof (first));
    int n = read(), m = read();
    for (int i = 1; i <= m; i++)
    {
        int a = read(), b = read(), c = read();
        add(a, b, c);
        add(b, a, INF);
    }
    printf ("%lld\n", Dinic(1, n));
}