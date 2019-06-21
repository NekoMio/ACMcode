#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1005;
#define dis(_, __) (\
(((_).x - (__).x) * ((_).x - (__).x)) + \
(((_).y - (__).y) * ((_).y - (__).y))\
)
struct Circle
{
    double x, y, r;
    bool operator < (const Circle &b) const 
    {
        return r < b.r;
    }
}a[MAXN];
struct edge
{
    int END, next;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
bool vis[MAXN];
double f[MAXN][2][2], tmp[MAXN][2][2];
void DFS(int rt, int fa)
{
    // vis[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        DFS(v[i].END, rt);
        for (int j = 0; j <= 1; j++)
            for (int k = 0; k <= 1; k++)
                tmp[rt][j][k] += f[v[i].END][j][k];
    }
    for (int i = 0; i <= 1; i++)
        for (int j = 0; j <= 1; j++)
        {
            f[rt][i][j] = max(
                tmp[rt][i ^ 1][j] + a[rt].r * a[rt].r * (i == 0 ? 1 : -1),
                tmp[rt][i][j ^ 1] + a[rt].r * a[rt].r * (j == 0 ? 1 : -1)
            );
        }
}
int main()
{
    memset (first, -1, sizeof (first));
    int n = read();
    for (int i = 1; i <= n; i++)
        a[i].x = read(), a[i].y = read(), a[i].r = read();
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (dis(a[i], a[j]) < a[j].r * a[j].r)
            {
                // printf ("%d %d\n", j, i);
                add(j, i);
                vis[i] = 1;
                break;
            }
    // while (1);
    double ans = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i])
        {
            DFS(i, 0);
            ans += f[i][0][0];
        }
    printf ("%.15f\n", ans * acos(-1.));
    // while (1);
}