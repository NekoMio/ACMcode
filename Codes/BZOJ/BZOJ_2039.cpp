#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define int long long
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 3000005;
const int INF = 0x3f3f3f3f3f3f3f3f;
struct edge
{
    int next, END, cap;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b, int f)
{
    v[p].END = b, v[p].next = first[a], v[p].cap = f, first[a] = p++;
    v[p].END = a, v[p].next = first[b], v[p].cap = 0, first[b] = p++;
}
int dis[MAXN], vis[MAXN];
bool BFS(int S, int E)
{
    memset (dis, -1, sizeof (dis));
    memset (vis, 0, sizeof (vis));
    queue<int> Q;
    Q.push(S);
    dis[S] = 0;
    vis[S]  =1;
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
    return dis[E] != -1;
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
            a -= f;
            flow += f;
            if (a == 0) break;
        }
    }
    if (flow == 0) dis[S] = -1;
    return flow;
}
int Dinic(int S, int E)
{
    int ans = 0;
    while (BFS(S, E))
        ans += DFS(S, E, INF);
    return ans;
}
signed main()
{
    memset (first ,-1, sizeof (first));
    int n = read();
    int S = 0, T = n * 2 + 4;
    for (int i = 1; i <= n; i++)
        add(S, i, read());
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int tmp = 0;
        for (int j = 1; j <= n; j++)
        {
            int x = read();
            add(i, j, 2 * x);
            tmp += x;
            ans += x;
        }
        add(i, T, tmp);
    }
    printf ("%lld\n", ans - Dinic(S, T));
    // while (1);
}