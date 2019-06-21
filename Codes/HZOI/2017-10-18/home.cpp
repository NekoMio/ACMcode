#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 200005;
struct egde
{
    int END, next;
}v[MAXN << 2];
int first[MAXN], p;
int S, T;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int dfn[MAXN], low[MAXN], Index;
bool iscut[MAXN];
bool Judge(int a)
{
    if (!dfn[1] || !dfn[T]) return 0;
    if (dfn[1] <= Index && dfn[1] >= dfn[a] && dfn[T] <= Index && dfn[T] >= dfn[a]) return 0;
    if ((dfn[1] > Index || dfn[1] < dfn[a]) && (dfn[T] > Index || dfn[T] < dfn[a])) return 0;
    return 1;
}
void Tarjan(int rt, int fa)
{
    dfn[rt] = low[rt] = ++Index;
    int s = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        // if (!f[v[i].END]) continue;
        if (!dfn[v[i].END])
        {
            s++;
            Tarjan(v[i].END, rt);
            low[rt] = min(low[rt], low[v[i].END]);
            if (low[v[i].END] >= dfn[rt] && Judge(v[i].END))
                iscut[rt] = 1;
        }
        else
            low[rt] = min(low[rt], dfn[v[i].END]);
    }
    if (fa < 0 && s == 1)
        iscut[rt] = 0;
}
int main()
{
    int t;
    scanf ("%d", &t);
    while (t--)
    {
        int n, m;
        scanf ("%d%d", &n, &m);
        memset(first, -1, sizeof (first));
        // memset(f, -1, sizeof (f));
        memset (dfn, 0, sizeof (dfn));
        memset (low, 0, sizeof (low));
        // memset (vis, 0, sizeof (vis));
        memset (iscut, 0, sizeof (iscut));
        p = 0;
        int a, b;
        for (int i = 1; i <= m; i++)
        {
            scanf ("%d%d", &a, &b);
            add(a, b);
            add(b, a);
        }
        T = n;
        // dfs(1, 1);
        Tarjan(1, -1);
        for (int i = 1; i <= n; i++)
            if (!dfn[i])
                Tarjan(i, -1);
        for (int i = 1; i <= n; i++)
        {
            printf ("%d\n: \t%d\n\t%d\n", i, dfn[i], low[i]);
        }
        int ans = 0;
        for (int i = 2; i < n; i++)
            if (iscut[i])
                ans++;
        printf ("%d\n", ans);
        for (int i = 2; i < n; i++)
            if (iscut[i])
                printf ("%d ", i);
        printf ("\n");
    }
}