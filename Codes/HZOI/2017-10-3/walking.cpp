#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1000005;
struct edge
{
    int next, END;
}v[N << 1];
int a[N], first[N], p;
int du[N];
double f[N], g[N];
void add(int a, int b)
{
    v[p].next = first[a];
    v[p].END = b;
    first[a] = p++;
}
void dfs(int rt, int fa)
{
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        dfs(v[i].END, rt);
        f[rt] += g[v[i].END] / du[rt];
        g[rt] += g[v[i].END] / (du[rt] - 1); 
    }
    f[rt] += a[rt];
    g[rt] += a[rt];
}
void DP(int rt, int fa)
{
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        f[v[i].END] += (g[rt] - g[v[i].END] / (du[rt] - 1)) / du[v[i].END];
        g[v[i].END] += (g[rt] - g[v[i].END] / (du[rt] - 1)) / (du[v[i].END] - 1);
        DP(v[i].END, rt);
    }
}
int main()
{
    int n;
    memset(first, -1, sizeof(first));
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    int s, e;
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &s, &e);
        add(s, e);
        add(e, s);
        du[e]++, du[s]++;
    }
    int rt = 1;
    for (int i = 1; i <= n; i++)
        if(du[i] != 1)
        {
            rt = i;
            break;
        }
    dfs(rt, 0);
    DP(rt, 0);
    double Max = 1e15;
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (f[i] < Max)
        {
            Max = f[i];
            ans = i;
        }
    printf("%d\n", ans);
}