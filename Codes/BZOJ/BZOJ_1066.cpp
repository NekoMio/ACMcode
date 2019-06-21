#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;

const int MAXM = 1e5 + 5;
const int MAXN = 1e4 + 5;
const int INF = 0x7fffffff;

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
}v[MAXM];
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
    memset (vis, 0, sizeof (vis));
    memset (dis, -1, sizeof (dis));
    queue<int> Q;
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
    return dis[E] != -1;
}
int DFS(int S, int E, int a)
{
    if (S == E || a == 0) return a;
    int flow = 0, f;
    for (int i = first[S]; i != -1; i = v[i].next)
    {
        if (dis[v[i].END] == dis[S] + 1 && (f = DFS(v[i].END, E, min(a, v[i].cap)) > 0))
        {
            v[i].cap -= f;
            v[i ^ 1].cap += f;
            a -= f;
            flow += f;
            if (f == 0)
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
    {
        ans += DFS(S, E, INF);
    }
    return ans;
}

int map[25][25];

#define ID(_, __, ___) (((_) * 21 + (__)) + (21 * 21 + 1) * (___ - 1))
#define dis(_, __, ___, ____) (\
((___) - (_)) * ((___) - (_)) + ((____) - (__)) * ((____) - (__))\
)
int main()
{
    memset (first, -1, sizeof (first));
    int n = read(), m = read(), d = read();    
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf ("%1d", &map[i][j]);
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        static char s[25];
        scanf ("%s", s + 1);
        for (int j = 1; j <= m; j++)
            if (s[j] == 'L')
                add(0, ID(i, j, 1), 1), cnt++;
    }
    int T = ID(n + 1, m + 1, 2);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
        if (map[i][j])
        {
            add(ID(i, j, 1), ID(i, j, 2), map[i][j]);
            for (int k = 1; k <= n; k++) for (int l = 1; l <= m; l++) 
                if (i != k || l != j)
                    if (dis(i, j, k, l) <= d * d && map[k][l])
                        add(ID(i, j, 2), ID(k, l, 1), INF);
            if (j + d > m || j <= d || d + i > n || i <= d)
                add(ID(i, j, 2), T, INF);
        }
    printf ("%d\n", cnt - Dinic(0, T));
}