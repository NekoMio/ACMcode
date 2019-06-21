#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 1e5 + 5;
struct edge
{
    int END, next;
}v[N << 1];
int first[N], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int dfn[N], low[N], Index;
bool iscut[N];
void Tarjan(int rt, int fa)
{
    dfn[rt] = low[rt] = ++Index;
    int S = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (!dfn[v[i].END])
        {
            S++;
            Tarjan(v[i].END, rt);
            low[rt] = min(low[rt], low[v[i].END]);
            if (low[v[i].END] >= dfn[rt]) iscut[rt] = 1;
        }
        else
            low[rt] = min(low[rt], dfn[v[i].END]);
    }
    if (fa < 0 && S == 1)
        iscut[rt] = 0;
}
int du[N];
int ans[N];
int main()
{
    int n, m;
    scanf ("%d%d", &n, &m);
    int a, b;
    memset(first, -1, sizeof (first));
    for (int i = 1; i <= m; i++)
    {
       scanf ("%d%d", &a, &b);
       add(a, b);
       add(b, a);
       du[a]++, du[b]++;
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            Tarjan(i, -1);
    for (int i = 1; i <= n; i++)
        if (du[i] == m - n + 2 && !iscut[i])
            ans[++ans[0]] = i;
    for (int i = 0; i <= ans[0]; i++)
        printf ("%d%c", ans[i], " \n"[!i]);
}