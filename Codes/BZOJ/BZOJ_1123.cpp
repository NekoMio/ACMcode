#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 100005;
#define int long long
struct edge
{
    int END, next;
}v[N * 10];
int first[N], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int dfn[N], low[N], Index;
int size[N], ans[N], n;
bool iscut[N];
void Tarjan(int rt, int fa)
{
    dfn[rt] = low[rt] = ++Index;
    long long S = 0;
    size[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (!dfn[v[i].END])
        {
            Tarjan(v[i].END, rt);
            size[rt] += size[v[i].END];
            low[rt] = min(low[rt], low[v[i].END]);
            if (low[v[i].END] >= dfn[rt])
            {
                ans[rt] += S * size[v[i].END];
                S += size[v[i].END];
            }
        }
        else 
            low[rt] = min(low[rt], dfn[v[i].END]);
    }
    ans[rt] += (n - S - 1) * (S);
}
signed main()
{
    int m;
    scanf ("%lld%lld", &n, &m);
    memset (first, -1, sizeof (first));
    int a, b;
    for (int i = 1; i <= m; i++)
    {
        scanf ("%lld%lld", &a, &b);
        add(a, b);
        add(b, a);
    }
    Tarjan(1, -1);
    for (int i = 1; i <= n; i++)
        printf ("%lld\n", (ans[i] + (n - 1)) << 1);
    // while (1);
}