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
inline char readchar()
{
    char ch=getchar();
    while (ch != '.' && ch != '#') ch=getchar();
    return ch;
}
const int MAXN = 10005;
const int INF = 0x3f3f3f3f;
struct edge
{
    int END, next, cap;
}v[200005];
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
    memset (vis, 0, sizeof (vis));
    memset (dis, -1, sizeof (dis));
    vis[S] = 1;
    dis[S] = 0;
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
int DFS(int S, int E, int a)
{
    if (S == E || a == 0) return a;
    int flow = 0, f;
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
int mp[105][105];
int dx[4] = {0,0,1,-1},
    dy[4] = {1,-1,0,0};
int n, m;
bool Test(int x, int y)
{
    if (x <= 0 || x > n) return 0;
    if (y <= 0 || y > m) return 0;
    if (mp[x][y]) return 0;
    return 1;
}
int x[MAXN], y[MAXN], cnt;
int XID[MAXN], YID[MAXN], ans[MAXN];
void DFS(int rt, int c)
{
    vis[rt] = 1;
    if (((XID[rt] + YID[rt]) & 1) == c && XID[rt])
        x[++cnt] = XID[rt], y[cnt] = YID[rt];
    for (int i = first[rt]; i != -1; i = v[i].next)
        if (v[i].cap == c && !vis[v[i].END])
            DFS(v[i].END, c);
}
bool cmp(const int &a, const int &b)
{
    return x[a] == x[b] ? y[a] < y[b] : x[a] < x[b];
}
int main()
{
    memset (first, -1, sizeof (first));
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            mp[i][j] = (readchar() == '#');
    int S = 0, T = n * m + 1;
    #define ID(_, __) (((_) - 1) * m + (__))  
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) 
        if (!mp[i][j])
        {
            if ((i + j) & 1)
            {
                add(S, ID(i, j), 1);
                for (int k = 0; k <= 3; k++)
                    if (Test(i + dx[k], j + dy[k]))
                        add(ID(i, j), ID(i + dx[k], j + dy[k]), 1);
                XID[ID(i, j)] = i, YID[ID(i, j)] = j;
            }
            else
            {
                add(ID(i, j), T, 1);
                XID[ID(i, j)] = i, YID[ID(i, j)] = j;
            }
        }
    Dinic(S, T);
    memset (vis, 0, sizeof (vis));
    DFS(S, 1);
    memset (vis, 0, sizeof (vis));
    DFS(T, 0);
    printf ("%d\n", cnt);
    for (int i = 1; i <= cnt; i++) ans[i] = i;
    sort(ans + 1, ans + cnt + 1, cmp);
    for (int i = 1; i <= cnt; i++)
        printf ("%d %d\n", x[ans[i]], y[ans[i]]);
}