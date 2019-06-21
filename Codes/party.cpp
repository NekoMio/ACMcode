#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 100005;
struct edge
{
    int END, next;
} v[1000005], f[1000005];
int first[N], p, ffirst[N], fp;
;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
    f[fp].END = a;
    f[fp].next = ffirst[b];
    ffirst[b] = fp++;
}
int dfn[N], ans;
bool vis[N], isnhead[N], huan;
void Dfs(int x)
{
    queue<int> Q;
    Q.push(x);
    dfn[x] = 1;
    vis[x] = 1;
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (v[i].END == x)
            {
                ans = dfn[k];
                return;
            }
            dfn[v[i].END] = dfn[k] + 1;
            ans = max(ans, dfn[v[i].END]);
            vis[v[i].END] = 1;
            Q.push(v[i].END);
        }
    }
}

int dfs(int x)
{
    ans = 0;
    memset(vis, 0, sizeof(vis));
    Dfs(x);
    return ans;
}
int main()
{
    freopen("party.in","r",stdin);
    freopen("party.out","w",stdout);
    int n, m;
    int a, b;
    memset(first, -1, sizeof(first));
    memset(ffirst, -1, sizeof(ffirst));
    scanf("%d%d", &n, &m);
    while (m--)
    {
        scanf("%d%d", &a, &b);
        add(a, b);
        isnhead[b] = 1;
    }
    int Max = 0, Min = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!isnhead[i])
        {
            int s = dfs(i);
            Max += s, Min = max(Min, s);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (!dfn[i])
        {
            int s = dfs(i);
            Max = s, Min = s;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        int d = 0;
        for (int j = ffirst[i]; j != -1; j = f[j].next)
        {
            if (!d)
                d = dfn[f[j].END];
            else
            {
                if (d != dfn[f[j].END])
                {
                    Max = Min = -1;
                    break;
                }
            }
        }
        if (Max == -1)
            break;
    }
    if (Max < 3)
        Max = Min = -1;
    else if (Min < 3)
        Min = 3;
    printf("%d %d\n", Max, Min);
}