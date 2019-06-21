#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 100005;
int a[305][305];
int H[305][305], n, m;
int dx[4] = {0, 0, 1, -1}, 
    dy[4] = {1, -1, 0, 0};
#define id(_,__) (((_) - 1) *  + (__))
struct edge
{
    int END, next, s, v;
    bool operator < (const edge &b) const 
    {
        return v < b.v;
    }
}E[N << 3], v[N << 1];
int first[N], p, o;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
int fa[N], dis[N];
int find(int x)
{
    if(fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}
bool vis[N];
int main()
{
    memset(first, -1, sizeof(first));
    memset(H, 0x3f, sizeof(H));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (i != 1) E[++o].END = id(i, j), E[o].s = id(i - 1, j), E[o].v = max(a[i][j], a[i - 1][j]);
            // E[++o].END = id(i, j), E[o].s = id(i + 1, j), E[o].v = max(a[i][j], a[i + 1][j]);
            if (j != 1) E[++o].END = id(i, j), E[o].s = id(i, j - 1), E[o].v = max(a[i][j], a[i][j - 1]);
            // E[++o].END = id(i, j), E[o].s = id(i, j + 1), E[o].v = max(a[i][j], a[i][j + 1]);
        }
    }
    for (int i = 1; i <= id(n, m); i++)
        fa[i] = i;
    int t = 0;
    sort(E + 1, E + o + 1);    
    for (int i = 1; i <= o; i++)
    {
        if(find(E[i].END) != find(E[i].s))
        {
            fa[find(E[i].END)] = find(E[i].s);
            add(E[i].END, E[i].s, E[i].v);
            add(E[i].s, E[i].END, E[i].v);
            t++;
            if(t == n * m - 1) break;
        }
    }
    queue<int> Q;
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 2; i < m; i++)
    {
        Q.push(id(1, i)), dis[id(1, i)] = a[1][i]; vis[id(1, i)] = 1;
        Q.push(id(n, i)), dis[id(n, i)] = a[n][i]; vis[id(n, i)] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        Q.push(id(i, 1)), dis[id(i, 1)] = a[i][1]; vis[id(i, 1)] = 1;
        Q.push(id(i, m)), dis[id(i, m)] = a[i][m]; vis[id(i, m)] = 1;
    }
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        vis[k] = 0;
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].END] > max(dis[k], v[i].v))
            {
                dis[v[i].END] = max(dis[k], v[i].v);
                if (!vis[v[i].END])
                {
                    Q.push(v[i].END);
                    vis[v[i].END] = 1;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            printf("%d ", max(0, dis[id(i, j)]) - a[i][j]);
        printf("\n");
    }
    // while(1);
}