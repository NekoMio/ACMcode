#include <cstring>
#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
struct data
{
    int s, e, a, b;
    bool operator<(const data &c) const
    {
        return a < c.a;
    }
} a[100005];
struct edge
{
    int END, v, next;
} v[200005];
int first[50005], p;
void add(int s, int e, int c)
{
    v[p].END = e;
    v[p].v = c;
    v[p].next = first[s];
    first[s] = p++;
}
bool flag[50005];
queue<int> Q;
int dis[50005];
void spfa()
{
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        flag[k] = 0;
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].END] > max(dis[k], v[i].v))
            {
                dis[v[i].END] = max(dis[k], v[i].v);
                if (!flag[v[i].END])
                {
                    flag[v[i].END] = 1;
                    Q.push(v[i].END);
                }
            }
        }
    }
}
int main()
{
    memset(first, -1, sizeof(first));
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d%d", &a[i].s, &a[i].e, &a[i].a, &a[i].b);
    }
    sort(a + 1, a + m + 1);
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= m; i++)
    {
        add(a[i].s, a[i].e, a[i].b);
        add(a[i].e, a[i].s, a[i].b);
        if (!flag[a[i].s])
        {
            Q.push(a[i].s);
            flag[a[i].s] = 1;
        }
        if (!flag[a[i].e])
        {
            Q.push(a[i].e);
            flag[a[i].e] = 1;
        }
        if (a[i + 1].a != a[i].a)
            spfa();
        ans = min(ans, a[i].a + dis[n]);
    }
    if (ans == 0x3f3f3f3f)
        puts("-1");
    else
        printf("%d\n",ans);
}