#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int delta = 0;
struct edge
{
    int S, E, val, type;
    bool operator<(const edge &a) const
    {
        int v1 = val, v2 = a.val;
        if (!type)
            v1 += delta;
        if (!a.type)
            v2 += delta;
        return v1 == v2 ? type < a.type : v1 < v2;
    }
} v[100005 << 1];
int father[50005], n, m;
int find(int x)
{
    if (father[x] != x)
        father[x] = find(father[x]);
    return father[x];
}
void init()
{
    for (int i = 0; i < n; i++)
        father[i] = i;
}
int Kruskal(int &num)
{
    int t = 0, sum = 0;
    for (int i = 1; i <= m; i++)
        if (find(v[i].S) != find(v[i].E))
        {
            father[find(v[i].S)] = find(v[i].E);
            if (!v[i].type)
                num++;
            sum += (v[i].type ? v[i].val : v[i].val + delta);
            t++;
            if (t == n - 1)
                break;
        }
    return sum;
}
int main()
{
    freopen("nt2012_tree.in", "r", stdin);
    freopen("nt2012_tree.out", "w", stdout);
    int need;
    scanf("%d%d%d", &n, &m, &need);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d%d", &v[i].S, &v[i].E, &v[i].val, &v[i].type);
    }
    int l = -105, r = 105;
    int ans = 0;
    while (l <= r)
    {
        delta = (l + r) / 2;
        init();
        sort(v + 1, v + m + 1);
        int ned = 0;
        int num = Kruskal(ned);
        if (ned >= need)
        {
            l = delta + 1;
            ans = num - need * delta;
        }
        else
            r = delta - 1;
    }
    printf("%d", ans);
}