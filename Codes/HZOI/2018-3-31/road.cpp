#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;
const int INF = 0x3f3f3f3f;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 4000;
int t[MAXN];
struct edge
{
    int END, next, cap;
}v[1000005];
int first[MAXN], p;
void add(int a, int b, int f)
{
    v[p].END = b, v[p].next = first[a], v[p].cap = f, first[a] = p++;
    v[p].END = a, v[p].next = first[b], v[p].cap = 0, first[b] = p++;
}
int q[MAXN];
int dis[MAXN];
bool BFS(int S, int T)
{
    memset (dis, -1, sizeof (dis));
    int h = 1, t = 0;
    q[++t] = S;
    dis[S] = 0;
    while (h <= t)
    {
        int k = q[h++];
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].END] == -1 && v[i].cap)
            {
                dis[v[i].END] = dis[k] + 1;
                if (v[i].END == T) return 1;
                q[++t] = v[i].END;
            }
        }
    }
    return 0;
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
    while (BFS(S, E))
        ans += DFS(S, E, INF);
    return ans;
}
int ID[65][65], S, T;
int Calc(int i, int j)
{
    return floor(10 * log(233 * (j - t[i]) * (j - t[i]) + 1));
}
int main()
{
    memset (first, -1, sizeof (first));
    int n = read(), m = read();
    for (int i = 1; i <= n; i++)
        t[i] = read();
    int Index = 0;
    S = ++Index, T = ++Index;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= n - 1; j++)
            ID[i][j] = ++Index;
    add(S, ID[1][0], Calc(1, 0));
    add(ID[1][0], T, INF);
    for (int i = 2; i <= n; i++)
    {
        add(S, ID[i][0], INF);
        for (int j = 0; j < n - 1; j++)
            add(ID[i][j], ID[i][j + 1], Calc(i, j + 1));
        add(ID[i][n - 1], T, INF);
    }
    for (int i = 1; i <= m; i++)
    {
        int a = read(), b = read();
        for (int k = 1; k < n; k++)
        {
            add(ID[a][k], ID[b][k - 1], INF);
            add(ID[b][k], ID[a][k - 1], INF);
            // add(ID[a][k - 1], ID[b][k], INF);
            // add(ID[b][k - 1], ID[a][k], INF);
            // add(ID[a][k - 1], ID[b][])
        }
    }
    printf ("%d\n", Dinic(S, T));
    // while (1);
}