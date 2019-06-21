#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int E, S, type, use;
    bool operator < (const edge &a) const 
    {
        return type > a.type;
    }
}v[100005];
int fa[20005];
int find(int x)
{
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}
bool vis[100005];
int main()
{
    int n, m, k;
    scanf ("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++)
        scanf ("%d%d%d", &v[i].S, &v[i].E, &v[i].type), v[i].use = 0;
    sort(v + 1, v + m + 1);
    int cnt = 0;
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= m; i++)
    {
        if (find(v[i].S) != find(v[i].E))
        {
            fa[find(v[i].S)] = find(v[i].E);
            vis[i] = 1; cnt += (v[i].type^1);
        }
    }
    if (cnt > k) return printf ("no solution\n"), 0;
    for (int i = 1; i <= n; i++) fa[i] = i;
    int t = 0;
    for (int i = 1; i <= m; i++)
    {
        if (vis[i] && !v[i].type)
        {
            k--;t++;
            v[i].use = 1;
            fa[find(v[i].S)] = find(v[i].E);
        }
    }
    for (int i = 1; i <= m; i++)
    {
        if (k > 0 && !v[i].type && !vis[i] && find(v[i].S) != find(v[i].E))
        {
            k--;t++;
            v[i].use = 1;
            fa[find(v[i].S)] = find(v[i].E);
        }
    }
    if (k) return printf ("no solution\n"), 0;
    for (int i = 1; i <= m; i++)
    {
        if (v[i].type && find(v[i].S) != find(v[i].E))
        {
            t++;
            v[i].use = 1;
            fa[find(v[i].S)] = find(v[i].E);
        }
    }
    if (t != n - 1) return printf ("no solution\n"), 0;
    for (int i = 1; i <= m; i++)
    {
        if (v[i].use == 1)
            printf ("%d %d %d\n", v[i].S, v[i].E, v[i].type);
    }
    // while (1);
}