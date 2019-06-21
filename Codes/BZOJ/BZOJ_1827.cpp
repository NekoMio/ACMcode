#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define int long long
int c[100005];
struct edge
{
    int END, next, v;
}v[200005];
int first[100005], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
int size[100005];
int vi[100005];
void DFS(int rt, int fa)
{
    size[rt] = c[rt];
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        DFS(v[i].END, rt);
        size[rt] += size[v[i].END];
        vi[rt] += v[i].v * size[v[i].END] + vi[v[i].END];
    }
}
int ans = 0x3f3f3f3f3f3f3f3fll;
void DP(int rt, int fa, int S)
{
    ans = min(S, ans);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        DP(v[i].END, rt, S + v[i].v * (size[1] - size[v[i].END]) - v[i].v * size[v[i].END]);
    }
}
signed main()
{
    memset(first, -1, sizeof (first));
    int n, a, b, d;
    scanf ("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf ("%lld", &c[i]);
    for (int i = 1; i < n; i++)
    {
        scanf ("%lld%lld%lld", &a, &b, &d);
        add(a, b, d);
        add(b, a, d);
    }
    DFS(1, 0);
    DP(1, 0, vi[1]);
    printf ("%lld", ans);
}