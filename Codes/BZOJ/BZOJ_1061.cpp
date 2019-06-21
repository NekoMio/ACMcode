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
const int INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 10005;
struct edge
{
    int S, END, next, v, cap;
}v[MAXN * 10];
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
    queue<int> Q;
    memset (dis, 0x3f, sizeof (dis));
    memset (vis, 0, sizeof (vis));
    memset (pre, -1, sizeof (pre));
    Q.push(S);
    vis[S] = 1;
    dis[S] = 0;
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        vis[k] = 0;
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].END] > dis[k] + v[i].v && v[i].cap > 0)
            {
                pre[v[i].END] = i;
                dis[v[i].END] = dis[k] + v[i].v;
                if (!vis[v[i].END])
                {
                    vis[v[i].END] = 1;
                    Q.push(v[i].END);
                }
            }
        }
    }
    return dis[E] != INF;
}
int Min_Profit(int S, int T)
{
    int ans = 0, flow;
    while (Spfa(S, T))
    {
        flow = INF;
        for (int i = pre[T]; i != -1; i = pre[v[i].S])
            flow = min(flow, v[i].cap);
        for (int i = pre[T]; i != -1; i = pre[v[i].S])
            v[i].cap -= flow, v[i ^ 1].cap += flow;
        ans += flow * dis[T];
    }
    return ans;
}
int D[MAXN];
signed main()
{
    // freopen ("employee.in", "r", stdin);
    // freopen ("employee.out", "w", stdout);
    memset (first, -1, sizeof(first));
    int n = read(), m = read();
    for (int i = 1; i <= n; i++)
        D[i] = read();
    for (int i = 1; i <= m; i++)
    {
        int a = read(), b = read(), c = read();
        add(a, b + 1, INF, c);
    }
    int S = 0, T = n + 2;
    for (int i = 1; i <= n + 1; i++)
    {
        int t = D[i] - D[i - 1];
        if (t >= 0) add(S, i, t, 0);
        else add(i, T, -t, 0);
        if (i > 1) add(i, i - 1, INF, 0);
    }
    printf ("%d\n", Min_Profit(S, T));
}