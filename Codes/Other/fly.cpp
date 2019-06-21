#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
struct edge
{
    int END, next, v;
} v[100005];
int first[10005], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}

int dis[10005][11];
bool flag[10005][11];
int Top;
struct data
{
    int k, tmp;
    bool operator<(const data &a) const
    {
        return dis[k][tmp] > dis[a.k][a.tmp];
    }
};
int Spfa(int S, int T)
{
    memset(dis, 0x3f, sizeof(dis));
    flag[S][0] = 1;
    priority_queue<data> Q;
    Q.push((data){S, 0});
    dis[S][0] = 0;
    while (!Q.empty())
    {
        int k = Q.top().k;
        int tmp = Q.top().tmp;
        flag[k][tmp] = 0;
        Q.pop();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].END][tmp] > dis[k][tmp] + v[i].v)
            {
                dis[v[i].END][tmp] = dis[k][tmp] + v[i].v;
                if (!flag[v[i].END][tmp])
                {
                    flag[v[i].END][tmp] = 1;
                    Q.push((data){v[i].END, tmp});
                }
            }
            if (dis[v[i].END][tmp + 1] > dis[k][tmp] && tmp + 1 <= Top)
            {
                dis[v[i].END][tmp + 1] = dis[k][tmp];
                if (!flag[v[i].END][tmp + 1])
                {
                    flag[v[i].END][tmp + 1] = 1;
                    Q.push((data){v[i].END, tmp + 1});
                }
            }
        }
    }
    int ans = 0x7fffffff;
    for (int i = 0; i <= Top; i++)
        ans = min(ans, dis[T][i]);
    return ans;
}
int main(int argc, char const *argv[])
{
    memset(first, -1, sizeof(first));
    int n, m;
    scanf("%d%d%d", &n, &m, &Top);
    int S, T;
    scanf("%d%d", &S, &T);
    S++, T++;
    int a, b, c;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        add(a + 1, b + 1, c);
        add(b + 1, a + 1, c);
    }
    printf("%d", Spfa(S, T));
    return 0;
}
