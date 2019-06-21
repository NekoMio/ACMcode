#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int END, next, v;
}v[4005];
int first[2005], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
bool vis[2005], flag;
int w[2005];
void dfs(int rt)
{
    vis[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (vis[v[i].END])
        {
            if (w[v[i].END] != w[rt] + v[i].v) flag = 1;
            continue;
        }
        else
        {
            w[v[i].END] = w[rt] + v[i].v;
            dfs(v[i].END);
        }
    }
}
int main()
{
    int T;
    scanf ("%d", &T);
    while (T--)
    {
        memset (first, -1, sizeof (first));
        memset (vis, 0, sizeof (vis));
        memset (w, 0, sizeof (w));
        p = 0;
        int n, m, k, a, b, c;
        scanf ("%d%d%d", &n, &m, &k);
        for (int i = 1; i <= k; i++)
        {
            scanf ("%d%d%d", &a, &b, &c);
            add(a + n, b, c);
            add(b, a + n, -c);
        }
        flag = 0;
        for (int i = 1; i <= n + m; i++)
        {
            if (!vis[i])
            {
                w[i] = 0;
                dfs(i);
            }
        }
        if (flag) printf ("No\n");
        else printf ("Yes\n");
    }
    getchar(), getchar();
}