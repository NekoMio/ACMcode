#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
const int INF = 0x3f3f3f3f;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
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
stack<int> st;
int dfn[MAXN], low[MAXN], Index;
int T, belong[MAXN];
void Tarjan(int rt)
{
    vis[rt] = 1;
    st.push(rt);
    dfn[rt] = low[rt] = ++Index;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].cap == 0) continue;
        if (!dfn[v[i].END])
        {
            Tarjan(v[i].END);
            low[rt] = min(low[rt], low[v[i].END]);
        }
        else if (vis[v[i].END]) low[rt] = min(low[rt], dfn[v[i].END]);
    }
    if (dfn[rt] == low[rt])
    {
        T++;
        int x = 0;
        while (x != rt)
        {
            x = st.top(); st.pop();
            belong[x] = T;
            vis[x] = 0;
        }
    }
}
int main()
{
    memset (first, -1, sizeof (first));
    int n = read(), m = read(), s = read(), t = read();
    for (int i = 1; i <= m; i++)
    {
        int a = read(), b = read(), c = read();
        add(a, b, c);
    }
    Dinic(s, t);
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            Tarjan(i);
    for (int i = 0; i < m; i++)
    {
        if (v[i << 1].cap) printf ("0 0\n");
        else
        {
            if (belong[v[i << 1].END] != belong[v[i << 1 | 1].END])
                printf ("1 ");
            else printf ("0 ");
            if (belong[v[i << 1].END] == belong[t] && belong[v[i << 1 | 1].END] == belong[s])
                printf ("1\n");
            else printf ("0\n");
        }
    }
}