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
struct edge
{
    int S, E, v;
    bool operator < (const edge &b) const
    {
        return v < b.v;
    }
}v[2005];
struct data
{
    int l, r, v;
}a[2005];
int fa[105];
int find(int x)
{
    if (x != fa[x]) return find(fa[x]);
    return fa[x];
}
int Sum;
void dfs(int s, int now, int t)
{
    if (now == a[s].r + 1)
    {
        if (t == a[s].v) Sum++;
        return;
    }
    int x = find(v[now].S), y = find(v[now].E);
    if (x != y)
    {
        fa[x] = y;
        dfs(s, now + 1, t + 1);
        fa[x] = x, fa[y] = y;
    }
    dfs(s, now + 1, t);
}
int main()
{
    int n = read(), m = read();
    for (int i = 1; i <= m; i++)
    {
        v[i].S = read(), v[i].E = read();
        v[i].v = read();
    }
    sort(v + 1, v + m + 1);
    for (int i = 1; i <= n; i++) fa[i] = i;
    int t = 0;
    int cnt = 0;
    for (int i = 1; i <= m; i++)
    {
        if (v[i].v != v[i - 1].v){
            a[++cnt].l = i;
            a[cnt - 1].r = i - 1;
        }
        int x = find(v[i].S), y = find(v[i].E);
        if (x != y)
        {
            fa[x] = y;
            a[cnt].v++; t++;
            // if(t == n - 1) break;
        }
    }
    a[cnt].r = m;
    if (t != n - 1) return printf ("0\n"), 0;
    for (int i = 1; i <= n; i++) fa[i] = i;
    int ans = 1;
    for (int i = 1; i <= n; i++)
    {
        Sum = 0;
        dfs(i, a[i].l, 0);
        ans = ans * Sum % 31011;
        for (int j = a[i].l; j <= a[i].r; j++)
        {
            int x = find(v[j].S), y = find(v[j].E);
            if (x != y) fa[x] = y;
        }
    }
    printf ("%d", ans);
}
