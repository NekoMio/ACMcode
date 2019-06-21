#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const long long INF = 0x3f3f3f3f3f3f3f3f;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int cnt1, cnt2;
long long Sum1, Sum2;
const int MAXN = 2005;
struct edge
{
    int next, END;
    long long cap;
}v[MAXN * 10];
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
    queue<int> Q;
    memset (dis, -1, sizeof (dis));
    memset (vis, 0, sizeof (vis));
    dis[S] = 0;
    vis[S] = -1;
    Q.push(S);
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
long long Dinic(int S, int E)
{
    long long ans = 0;
    while (BFS(S, E)) ans += DFS(S, E, INF);
    return ans;
}
int dx[4] = {0,0,1,-1},
    dy[4] = {1,-1,0,0};
int n, m;
#define ID(_, __) (\
((_) - 1) * m + (__)\
)
int a[45][45];
int Color[45][45];
bool Judge(long long mid)
{
    memset (first, -1, sizeof (first));
    p = 0;
    int S = 0, T = n * m + 1;
    long long tot = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (Color[i][j])
            {
                add(S, ID(i, j), mid - a[i][j]), tot += mid - a[i][j];
                for (int k = 0; k < 4; k++)
                {
                    int nx = i + dx[k], ny = j + dy[k];
                    if (nx < 1 || ny < 1 || nx > n || ny > m) continue;
                    add(ID(i, j), ID(nx, ny), INF);
                }
            }
            else add(ID(i, j), T, mid - a[i][j]);
    if (Dinic(S, T) == tot) return 1;
    else return 0;
}

signed main()
{
    int T = read();
    while (T--)
    {
        cnt1 = cnt2 = Sum1 = Sum2 = 0;
        n = read(), m = read();
        int Max = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                a[i][j] = read(), Color[i][j] = (i + j) & 1;
                Max = max(Max, a[i][j]);
            }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (Color[i][j]) cnt1++, Sum1 += a[i][j];
                else cnt2++, Sum2 += a[i][j];
        if (cnt1 != cnt2)
        {
            long long x = (Sum1 - Sum2) / (cnt1 - cnt2);
            if (x >= Max)
            {
                if (Judge(x))
                {
                    printf ("%lld\n", x * cnt1 - Sum1);
                    continue;
                }
            }
            printf ("-1\n");
        }
        else
        {
            if (Sum1 != Sum2)
            {
                printf ("-1\n");
                continue;
            }
            else
            {
                long long l = Max, r = INF, ans = 0;
                while (l <= r)
                {
                    long long mid = l + r >> 1;
                    if (Judge(mid)) ans = mid, r = mid - 1;
                    else l = mid + 1;
                }
                printf ("%lld\n", ans * cnt1 - Sum1);
            }
        }
    }
}