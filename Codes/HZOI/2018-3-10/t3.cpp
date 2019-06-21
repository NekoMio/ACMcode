// #pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 60005;
struct edge
{
    int END, next;
}v[MAXN << 1];
int first[MAXN], p = 2;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int fa[MAXN];
int num[MAXN];
void dfs(int rt, int f)
{
    fa[rt] = f;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == f) continue;
        dfs(v[i].END, rt);
        num[rt] = max(num[rt], num[v[i].END] + 1);
    }
}
int f[MAXN][601], c[MAXN];
void Remove(int pre, int rt, int _pre, int t)
{
    if (rt != 1) Remove(rt, fa[rt], _pre, t + c[pre]);

    for (int i = 300 - num[_pre] + t + c[pre]; i <= 300 + num[_pre] + t + c[pre]; i++)
    {
        if (i - t - c[pre] < 0) continue;
        f[rt][i] -= f[_pre][i - t - c[pre]];
    }
}
int tmp = 0;
void Update(int pre, int rt)
{
    int _pre = pre, _rt = rt;
    Remove(pre, rt, pre, 0);
    c[pre] = 1;
    int s = 1;
    tmp = 0;
    while (rt != 0)
    {
        for (int i = 300 - num[_pre]; i <= 300 + num[_pre]; i++)
        {
            // if (600 - i - s + 1 < 0 || 600 - i - s + 1 > 600) continue;
            if (i != 600) 
            if (pre != _pre)
                tmp += (f[rt][600 - i - s + 1] - f[pre][600 - i - c[pre] - s + 1]) * f[_pre][i];
            else 
                tmp += f[rt][600 - i - s + 1] * f[_pre][i];
        }
        s += c[rt];
        pre = rt;
        rt = fa[rt];
    }
    s = 1;
    rt = _rt, pre = _pre;
    while (rt != 0)
    {
        for (int i = 300 - num[_pre] + s; i <= 300 + num[_pre] + s; i++)
        {
            if (i - s < 0 || i < 0) continue;
            f[rt][i] += f[_pre][i - s];
        }
        s += c[rt];
        pre = rt;
        rt = fa[rt];
    }
}
struct data
{
    int a, b, c;
    bool operator < (const data &d) const 
    {
        return c < d.c;
    }
}E[MAXN];
void dfs(int rt)
{
    f[rt][300] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa[rt]) continue;
        dfs(v[i].END);
        for (int j = 300 - num[rt]; j <= 300 + num[rt]; j++)
        {
            if (j + c[v[i].END] < 0 || j + c[v[i].END] > 600) continue;
            f[rt][j + c[v[i].END]] += f[v[i].END][j];
        }
    }
}
void Print(int rt)
{
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa[rt]) continue;
        Print(v[i].END);
        for (int j = 300 - 4; j <= 300 + 4; j++)
            printf ("f[%d][%d] = %d\n", rt, j, f[rt][j]);
    }
}
int main()
{
    // freopen ("draw15.in", "r", stdin);
    // freopen ("draw.out", "w", stdout);
    memset (first, -1, sizeof (first));
    int n = read();
    for (int i = 1; i < n; i++)
    {
        E[i].a = read(), E[i].b = read(), E[i].c = read();
        add(E[i].a, E[i].b);
        add(E[i].b, E[i].a);
    }
    dfs(1, 0);
    for (int i = 2; i <= n; i++)
        c[i] = -1;
    dfs(1);
    sort(E + 1, E + n);
    long long ans = 0;
    for (int i = 1; i < n; i++)
    {
        // printf ("-------------------------\n");
        // Print(1);
        // printf ("-------------------------\n");
        if (E[i].a == fa[E[i].b])
            Update(E[i].b, E[i].a);
        else
            Update(E[i].a, E[i].b);
        // printf ("%d\n", tmp);
        ans += 1ll * tmp * E[i].c;
    }
    printf ("%lld\n", ans);
    // while (1);
}