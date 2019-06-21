#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
struct edge
{
    int END, next;
    long long v;
} v[4005];
int first[2005], p, m, n;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
long long f[2005][2005];
int size[2005];
long long tmp[2005];
void DP(int rt, int fa)
{
    size[rt] = 1;
    f[rt][0] = f[rt][1] = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa)
            continue;
        DP(v[i].END, rt);
        for (int j = 0; j <= size[rt]; j++)
            tmp[j] = f[rt][j];
        for (int j = min(size[rt], m); j >= 0; j--)
        {
            for (int k = 0; k <= size[v[i].END] && k + j <= m; k++)
            {
                long long add = ((size[v[i].END] - k) * (n - m - size[v[i].END] + k) + k * (m - k)) * v[i].v + f[v[i].END][k];
                f[rt][j + k] = max(f[rt][j + k], tmp[j] + add);
            }
        }
        size[rt] += size[v[i].END];
    }
}
int main()
{
    // freopen("haoi2015_t1.in", "r", stdin);
    // freopen("haoi2015_t1.out", "w", stdout);
    scanf("%d%d", &n, &m);
    memset(first, -1, sizeof(first));
    memset(f, 0xF0, sizeof(f));
    int a, b, c;
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
        add(b, a, c);
    }
    DP(1, 0);
    printf("%lld", f[1][m]);
}