#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct data
{
    int s, e, v, op;
    bool operator<(const data &a) const
    {
        return v == a.v ? op < a.op : v < a.v;
    }
} a[300005];
int father[100005];
int find(int x) 
{
    if (father[x] != x)
        father[x] = find(father[x]);
    return father[x];
}
int size[100005], ans[200005];
int main()
{
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a[i].s, &a[i].e, &a[i].v);
        a[i].op = 0;
    }
    for (int i = m + 1; i <= q + m; i++)
    {
        scanf("%d%d", &a[i].s, &a[i].v);
        a[i].op = 1;
        a[i].e = i - m;
    }
    for (int i = 1; i <= n; i++)
        father[i] = i, size[i] = 1;
    sort(a + 1, a + q + m + 1);
    for (int i = 1; i <= m + q; i++)
    {
        if (a[i].op == 1)
        {
            ans[a[i].e] = size[find(a[i].s)];
        }
        else
        {
            if (find(a[i].e) != find(a[i].s))
            {
                size[find(a[i].e)] += size[find(a[i].s)];
                father[find(a[i].s)] = find(a[i].e);
            }
        }
    }
    for (int i = 1; i <= q; i++)
    {
        printf("%d\n", ans[i]);
    }
}