#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int INF = 0x3f3f3f3f;
struct edge
{
    int S, END, next, cap, v;
}v[100005];
int first[155], p;
void add(int a, int b, int f, int c)
{
    v[p].END = b, v[p].cap = f, v[p].S = a, v[p].v = c, v[p].next = first[a], first[a] = p++;
    v[p].END = a, v[p].cap = 0, v[p].S = b, v[p].v =-c, v[p].next = first[b], first[b] = p++;
}
#define ID(_, __) (((_) - 1) * m + (__))
int dx[4] = {0,0,1,-1},
    dy[4] = {1,-1,0,0};
int d[155];
char mp[15][15];
int dis[155], pre[155];
bool vis[155];
int q[1000005];
bool Spfa(int S, int E)
{
    memset (dis, 0x3f, sizeof (dis));
    memset (pre, -1, sizeof (pre));
    int h = 1, t = 0;
    q[++t] = S;
    dis[S] = 0;
    vis[S] = 1;
    while (h <= t)
    {
        int k = q[h++];
        vis[k] = 0;
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (v[i].cap && dis[v[i].END] > dis[k] + v[i].v)
            {
                dis[v[i].END] = dis[k] + v[i].v;
                pre[v[i].END] = i;
                if (!vis[v[i].END])
                {
                    vis[v[i].END] = 1;
                    q[++t] = v[i].END;
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
bool Judge(int S)
{
    for (int i = first[S]; i != -1; i = v[i].next)
        if (v[i].cap)
            return 0;
    return 1;
}
int main()
{
    // freopen ("1.in", "r", stdin);
    memset (first, -1, sizeof (first));
    int cnt = 1;
    while (scanf ("%s", mp[cnt] + 1) != EOF)
        cnt++;
    int n = cnt - 1, m = strlen(mp[1] + 1);
    int t = n * m + 1, s = 0, S = t + 1, T = S + 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++) if (mp[i][j] == '.')
        {
            if ((i + j) & 1)
            {
                if (i == 1 || j == 1 || i == n || j == m) add(ID(i, j), t, 1, 1);
                d[s] -= 2, d[ID(i, j)] += 2;
                for (int k = 0; k <= 3; k++)
                {
                    if (i + dx[k] > n || i + dx[k] <= 0) continue;
                    if (j + dy[k] > m || j + dy[k] <= 0) continue;
                    if (mp[i + dx[k]][j + dy[k]] == '#') continue;
                    add(ID(i, j), ID(i + dx[k], j + dy[k]), 1, 0);
                }
            }
            else
            {
                if (i == 1 || j == 1 || i == n || j == m) add(s, ID(i, j), 1, 1);
                d[ID(i, j)] -= 2, d[t] += 2;
            }
        }
    }
    for (int i = s; i <= t; i++)
    {
        if (d[i] > 0) add(S, i, d[i], 0);
        if (d[i] < 0) add(i, T,-d[i], 0);
    }
    add(t, s, INF, 0);
    int Cost = Min_Profit(S, T);
    if (Judge(S)) return printf ("%d\n", Cost / 2), 0;
    else return printf ("-1\n"), 0;
}
