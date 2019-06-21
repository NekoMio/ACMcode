#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int END, next, v;
}v[500005 << 1];
int first[500005], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
int q[500005];
double f[500005], g[500005];
void Get_F(int rt, int fa)
{
    f[rt] = 1.0 - q[rt] / 100.0; 
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa)
            continue;
        Get_F(v[i].END, rt);
        f[rt] *= (f[v[i].END] + (1.0 - f[v[i].END]) * (1.0 - v[i].v / 100.0));
    }
}
void Get_G(int rt, int fa, int j)
{
    if (rt == 1)
        g[rt] = 1;
    else
    {
        double P = g[fa] * f[fa] / (f[rt] + (1.0 - f[rt]) * (1.0 - v[j].v / 100.0));
        g[rt] = P + (1.0 - P) * (1.0 - v[j].v / 100.0);
    }
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if(v[i].END == fa)
            continue;
        Get_G(v[i].END, rt, i);
    }
}
int main()
{
    memset(first, -1, sizeof(first));
    int n;
    scanf("%d",&n);
    int a, b, c;
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
        add(b, a, c);
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", &q[i]);
    Get_F(1, 0);
    Get_G(1, 0, 0);
    double ans = 0;
    for (int i = 1; i <= n; i++)
        ans += (1 - f[i] * g[i]);
    printf("%.6lf", ans);
}