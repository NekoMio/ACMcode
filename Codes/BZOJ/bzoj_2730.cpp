#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int END, next;
} v[10005];
int first[500], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int dfn[500], low[500], Index;
bool iscut[500];
void Tarjan(int x, int fa)
{
    low[x] = dfn[x] = ++Index;
    int S = 0;
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (!dfn[v[i].END])
        {
            S++;
            Tarjan(v[i].END, x);
            low[x] = min(low[v[i].END], low[x]);
            if (low[v[i].END] >= dfn[x])
                iscut[x] = 1;
        }
        else
            low[x] = min(low[x], dfn[v[i].END]);
    }
    if (fa < 0 && S == 1)
        iscut[x] = 0;
}
bool vis[500];
int T, size, num;
int color[500];
void dfs(int x)
{
    vis[x] = 1;
    size++;
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (!vis[v[i].END])
        {
            if (!iscut[v[i].END])
                dfs(v[i].END);
            else
            {
                if (color[v[i].END] != T)
                    color[v[i].END] = T, num++;
            }
        }
    }
}
int main()
{
    //freopen("bzoj_2730.in","r",stdin);
    //freopen("bzoj_2730.out","w",stdout);
    int P1 = 0;
    while (1)
    {
        memset(vis, 0, sizeof(vis));
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(iscut, 0, sizeof(iscut));
        memset(first, -1, sizeof(first));
        memset(color, 0, sizeof(color));
        p = 0;
        Index = 0;
        P1++;
        int n = 0, a, b, m;
        scanf("%d", &m);
        if (m == 0)
            break;
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d", &a, &b);
            n = max(a, n);
            n = max(b, n);
            add(a, b);
            add(b, a);
        }
        for (int i = 1; i <= n; i++)
            if (!dfn[i])
                Tarjan(i, -1);
        int ans1 = 0;
        long long ans2 = 1;
        T = 0;
        for (int i = 1; i <= n; i++)
        {
            if (!vis[i] && !iscut[i])
            {
                T++, size = 0, num = 0;
                dfs(i);
                if (num == 1)
                    ans1++, ans2 *= size;
            }
        }
        if (T == 1)
            ans1 = 2, ans2 = n * (n - 1) / 2;
        printf("Case %d: %d %lld\n", P1, ans1, ans2);
    }
}