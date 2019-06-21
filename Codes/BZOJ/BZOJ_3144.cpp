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
const int INF = 0x3f3f3f3f;
const int MAXN = 100005;
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
    queue<int> Q;
    memset (dis, -1, sizeof (dis));
    memset (vis, 0, sizeof (vis));
    dis[S] = 0;
    vis[S] = 1;
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
    while (BFS(S, E)) ans += DFS(S, E, INF);
    return ans;
}
int f[45][45][45];
#define ID(_, __, ___) (\
((___) == 0) ? 0 : ((___) - 1) * P * Q + ((_) - 1) * Q + __\
)
int dx[4] = {0,0,1,-1},
    dy[4] = {1,-1,0,0};
int main()
{
    memset (first, -1, sizeof (first));
    int P = read(), Q = read(), R = read();
    int d = read(), T = P * Q * R + 1;
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= P; j++)
            for (int k = 1; k <= Q; k++)
                f[j][k][i] = read();
    for (int i = 1; i <= P; i++)
    {
        for (int j = 1; j <= Q; j++)
        {
            for (int k = 1; k <= R; k++)
            {
                add(ID(i, j, k - 1), ID(i, j, k), f[i][j][k]);
                if (k > d) 
                    for (int s = 0; s <= 3; s++)
                    {
                        int nx = i + dx[s], ny = j + dy[s];
                        if (nx < 1 || ny < 1 || nx > P || ny > Q) continue;
                        add(ID(i, j, k), ID(nx, ny, k - d), INF);
                    }
            }
            add(ID(i, j, R), T, INF);
        }
    }
    printf ("%d\n", Dinic(0, T));
}