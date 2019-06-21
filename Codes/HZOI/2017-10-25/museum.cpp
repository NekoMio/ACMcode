#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
struct edge
{
    int END, next, v;
}v[20005];
int first[10005], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
int ans = 0, k;
int fa[10005], size[10005];
int f[10005][10005];
int g[10005][10005];
int tmp[10005][2];
void DP(int rt, int fa)
{
    f[rt][1] = 0, g[rt][1] = 0;
    size[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        DP(v[i].END, rt);
        for (int h = 1; h <= k; h++) tmp[h][0] = f[rt][h], tmp[h][1] = g[rt][h];
        for (int h = 1; h <= size[rt] && h <= k; h++)
        {
            for (int j = 1; j <= size[v[i].END] && j + h <= k; j++)
            {
                tmp[h + j][0] = min(tmp[h + j][0], f[rt][h] + f[v[i].END][j] + 2 * v[i].v);
                tmp[h + j][1] = min(tmp[h + j][1], f[rt][h] + g[v[i].END][j] + v[i].v);
                tmp[h + j][1] = min(tmp[h + j][1], g[rt][h] + f[v[i].END][j] + 2 * v[i].v);
            }
        }
        size[rt] += size[v[i].END];
        for (int h = 1; h <= k; h++) f[rt][h] = tmp[h][0], g[rt][h] = tmp[h][1];
    }
}
int main()
{
    // freopen("museum.in", "r", stdin);
    // freopen("museum.out", "w", stdout);
    int n, x;
    memset (first, -1, sizeof (first));
    scanf("%d%d%d", &n, &k, &x);
    int a, b, c;
    memset (f, 0x3f, sizeof(f));
    memset (g, 0x3f, sizeof(g));
    for (int i = 1; i < n; i++)
    {
        scanf ("%d%d%d", &a, &b, &c);
        add(a, b, c);
        add(b, a, c);
    }
    ans = 0x3f3f3f3f;
    DP(x, 0);
    printf ("%d", min(g[x][k], f[x][k]));
}
