#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXM = 50005;
const int MAXN = 1000;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

struct edge
{
    int END, next, cap;
}v[MAXM << 1];
int first[MAXN];
int p;

void add(int a, int b, int c)
{
    v[p].END = b, v[p].next = first[a], v[p].cap = c, first[a] = p++;
    v[p].END = a, v[p].next = first[b], v[p].cap = 0, first[b] = p++;
}
int dis[MAXN];
bool vis[MAXN];
bool BFS(int S, int E)
{
    memset(vis, 0, sizeof(vis));
    memset(dis, -1, sizeof(dis));
    queue<int> Q;
    Q.push(S);
    dis[S] = 0;
    vis[S] = 1;
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (int i = first[u]; i != -1; i = v[i].next)
        {
            if (!vis[v[i].END] && v[i].cap > 0)
            {
                vis[v[i].END] = 1;
                dis[v[i].END] = dis[u] + 1;
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
            a -= f;
            flow += f;
            if (a == 0)
                break;
        }
    }
    if (!flow) dis[S] = -1;
    return flow;
}
int Dinic(int S, int E)
{
    int ans = 0;
    while (BFS(S, E))
        ans += DFS(S, E, INF);
    return ans;
}
struct data
{
    int x, y, r, t;
    data(int a = 0, int b = 0)
    {
        x = a, y = b;
    }
    data operator - (const data &b){
        return data(x - b.x, y - b.y);
    }
    double operator * (const data &b)
    {
        return x * b.y - b.x * y;
    }
}F[405], J[405], Q[405];

#define p2(_) ((_) * (_))
#define dis2(_, __) (p2((_).x - (__).x) + p2((_).y - (__).y))


bool Judge(data s, data x1, data x2)
{
    double a = (s - x1) * (s - x2) / sqrt(dis2(x1, x2));
    return p2(a) >= p2(s.r);
}
int n, m, K;
int mp[205][205];
void Build(int mid)
{
    memset(first, -1, sizeof (first));
    p = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j])
                add(i, j + n, 1);
    for (int i = 1; i <= m; i++)
        add(i + n, n + m + 1, 1);
    for (int i = 1; i <= n; i++)
    {
        if (F[i].t == 0) add(0, i, INF);
        else add(0, i, mid / F[i].t + 1);
    }
}

int main()
{
    memset (first, -1, sizeof (first)), p = 0;
    n = read(), m = read(), K = read();
    for (int i = 1; i <= n; i++)
        F[i].x = read(), F[i].y = read(), F[i].r = read(), F[i].t = read();
    for (int i = 1; i <= m; i++)
        J[i].x = read(), J[i].y = read();
    for (int i = 1; i <= K; i++)
        Q[i].x = read(), Q[i].y = read(), Q[i].r = read();
    static bool flag[MAXN];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (dis2(F[i], J[j]) <= p2(F[i].r))
            {
                int fla = 0;
                for (int k = 1; k <= K; k++)
                    if (!Judge(Q[k], F[i], J[j]))
                        fla = 1;
                if (!fla) mp[i][j] = 1, flag[j] = 1;
            }
    for (int i = 1; i <= m; i++) 
        if (!flag[i])
        {
            return printf ("-1\n");
        }
    int l = 0, r = 1e9;
    while (l <= r)
    {
        int mid = l + r >> 1;
        Build(mid);
        if (Dinic(0, n + m + 1) == m) 
            r = mid - 1;
        else l = mid + 1;
    }
    printf ("%d\n", l);
}