#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
static inline int read()
{
    int x=0, f=1; char ch=getchar();
    while (ch<'0'||ch>'9') { if (ch == '-') f = -1; ch = getchar();}
    while (ch>='0'&&ch<='9') { x = x * 10 + ch-'0'; ch = getchar();}
    return x * f;
}
const int MAXN = 100005;
const int INF = 0x3f3f3f3f;
struct edge
{
    int END, next, cap;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b, int f)
{
    // printf ("add %d %d %d\n", a, b, f);
    v[p].END = b, v[p].next = first[a], v[p].cap = f, first[a] = p++;
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
        if (dis[v[i].END] == dis[S] + 1 && (f = DFS(v[i].END, E, min(v[i].cap, a))) > 0)
        {
            v[i].cap -= f;
            v[i ^ 1].cap += f;
            a -= f;
            flow += f;
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
int id[55][55][2];
int main()
{
    memset (first, -1, sizeof (first));
    int n = read(), m = read();
    static char s[55][55];
    for (int i = 1; i <= n; i++)
        scanf ("%s", s[i] + 1);
    int Index = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            id[i][j][0] = ++Index, id[i][j][1] = ++Index;
    int S = ++Index, T = ++Index;
    // printf ("S = %d T = %d\n", S, T);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            add(id[i][j][0], id[i][j][1], INF);
            if (s[i][j] == 'A')
            {
                add(S, id[i][j][0], INF);
                int Max = 0;
                for (int ni = i - 1; ni > 0; ni--)
                    if (s[ni][j] > '0' && s[ni][j] <= '9') 
                        Max = max(Max, s[ni][j] - '0');
                for (int ni = i - 1; ni > 0; ni--)
                    if (s[ni + 1][j] > '0' && s[ni + 1][j] <= '9') 
                        add(id[ni + 1][j][0], id[ni][j][0], Max - (s[ni + 1][j] - '0'));
                    else
                        add(id[ni + 1][j][0], id[ni][j][0], Max);
                ans += Max;
            }
            else if (s[i][j] == 'V')
            {
                add(S, id[i][j][0], INF);
                int Max = 0;
                for (int ni = i + 1; ni <= n; ni++)
                    if (s[ni][j] > '0' && s[ni][j] <= '9') 
                        Max = max(Max, s[ni][j] - '0');
                for (int ni = i + 1; ni <= n; ni++)
                    if (s[ni - 1][j] > '0' && s[ni - 1][j] <= '9') 
                        add(id[ni - 1][j][0], id[ni][j][0], Max - (s[ni - 1][j] - '0'));
                    else
                        add(id[ni - 1][j][0], id[ni][j][0], Max);
                ans += Max;
            }
            else if (s[i][j] == '>')
            {
                add(id[i][j][1], T, INF);
                int Max = 0;
                for (int nj = j + 1; nj <= m; nj++)
                    if (s[i][nj] > '0' && s[i][nj] <= '9') 
                        Max = max(Max, s[i][nj] - '0');
                for (int nj = j + 1; nj <= m; nj++)
                    if (s[i][nj - 1] > '0' && s[i][nj - 1] <= '9') 
                        add(id[i][nj][1], id[i][nj - 1][1], Max - (s[i][nj - 1] - '0'));
                    else
                        add(id[i][nj][1], id[i][nj - 1][1], Max);
                ans += Max;
            }
            else if (s[i][j] == '<')
            {
                add(id[i][j][1], T, INF);
                int Max = 0;
                for (int nj = j - 1; nj > 0; nj--)
                    if (s[i][nj] > '0' && s[i][nj] <= '9') 
                        Max = max(Max, s[i][nj] - '0');
                for (int nj = j - 1; nj > 0; nj--)
                    if (s[i][nj + 1] > '0' && s[i][nj + 1] <= '9') 
                        add(id[i][nj][1], id[i][nj + 1][1], Max - (s[i][nj + 1] - '0'));
                    else
                        add(id[i][nj][1], id[i][nj + 1][1], Max);
                ans += Max;
            }
        }
    printf ("%d\n", ans - Dinic(S, T));
    // while (1);
}