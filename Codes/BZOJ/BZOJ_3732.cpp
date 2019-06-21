#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int next, v, END;
}v[30005];
int first[15005],p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
struct data
{
    int a, b, v;
    bool operator < (const data &c) const 
    {
        return v < c.v;
    }
}a[30005];
int father[15005];
int find(int x)
{
    if(father[x] != x) father[x] = find(father[x]);
    return father[x];
}
int f[15005][17], Max[15005][17], dep[15005];
void dfs(int rt, int fa, int V, int Dep)
{
    f[rt][0] = fa;
    dep[rt] = Dep;
    Max[rt][0] = V;
    for (int i = 1; i <= 16; i++)
    {
        f[rt][i] = f[f[rt][i - 1]][i - 1];
        Max[rt][i] = max(Max[rt][i - 1], Max[f[rt][i - 1]][i - 1]);
    }
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if(v[i].END == fa) continue;
        dfs(v[i].END, rt, v[i].v, Dep + 1); 
    }
}
int Get(int x, int y)
{
    if(dep[x] < dep[y])
        swap(x, y);
    int d = dep[x] - dep[y], ans = 0;
    for (int i = 16; i >= 0; i--)
        if(d >= (1 << i))
        {
            d -= (1 << i);
            ans = max(ans, Max[x][i]);
            x = f[x][i];
        }
    if (x == y) return ans;
    for (int i = 16; i >= 0; i--)
        if(f[x][i] != f[y][i])
        {
            ans = max(ans, max(Max[x][i], Max[y][i]));
            x = f[x][i], y = f[y][i];
        }
    ans = max(ans, max(Max[x][0], Max[y][0]));
    return ans;
}
int main()
{
    int n, m, k;
    memset(first, -1, sizeof(first));
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &a[i].a, &a[i].b, &a[i].v);
    sort(a + 1, a + m + 1);
    for (int i = 1; i <= n; i++) father[i] = i;
    int t = 0;
    for (int i = 1; i <= m; i++)
    {
        if(find(a[i].a) != find(a[i].b))
        {
            father[find(a[i].a)] = find(a[i].b);
            add(a[i].a, a[i].b, a[i].v);
            add(a[i].b, a[i].a, a[i].v);
            t++;
            if(t == n - 1) break;
        }
    }
    dfs(1, 0, 0, 0);
    int s, e;
    while (k--)
    {
        scanf("%d%d", &s, &e);
        printf("%d\n", Get(s, e));
    }
}