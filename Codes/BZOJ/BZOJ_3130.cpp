#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

const int MAXM = 1005;
const int MAXN = 105;
const int INF = 0x3f3f3f3f;

struct edge
{
    int END, next;
    double cap;
}v[MAXM << 1], tmp[MAXM << 1];
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
    memset (dis, -1, sizeof (dis));
    memset (vis, 0, sizeof (vis));
    dis[S] = 0;
    vis[S] = 1;
    queue<int> Q;
    Q.push(S);
    while (!Q.empty())
    {
        int k = Q.front(); Q.pop();
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
double DFS(int S, int E, double a)
{
    if (S == E || a < 1e-10) return a;
    double flow = 0, f;
    for (int i = first[S]; i != -1; i = v[i].next)
    {
        if (dis[v[i].END] == dis[S] + 1 && ((f = DFS(v[i].END, E, min(a, v[i].cap))) > 1e-15))
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
double Dinic(int S, int E)
{
    double ans = 0;
    while (BFS(S, E))
    {
        ans += DFS(S, E, INF);
    }
    return ans;
}

int main()
{
    memset (first, -1, sizeof (first));
    int n = read(), m = read(), p = read();
    double r = 0;
    for (int i = 1; i <= m; i++)
    {
        int a = read(), b = read(), c = read();
        add(a, b, c);
        r = max(r, (double)c);
    }
    memcpy(tmp, v, sizeof (tmp));
    int Maxflow = round(Dinic(1, n));
    double l = 0;
    printf ("%d\n", Maxflow);
    while (r - l > 1e-10)
    {
        double mid = (l + r) / 2;
        memcpy(v, tmp, sizeof(v));
        for (int i = 0; i < p; i++) v[i].cap = min(mid, v[i].cap);
        if (abs(Dinic(1, n) - Maxflow) < 1e-15) r = mid;
        else l = mid;
    }
    printf ("%.4lf", l * p);
}