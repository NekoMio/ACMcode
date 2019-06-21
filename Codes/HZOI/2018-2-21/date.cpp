#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1e5 + 5;
struct edge
{
    int END, next, v;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].v = c;
    v[p].next = first[a];
    first[a] = p++;
}
int Max[MAXN], Sum, root;
int size[MAXN];
int mid;
int vis[MAXN];
void Get_Size(int rt, int fa)
{
    size[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa || vis[v[i].END] == mid) continue;
        Get_Size(v[i].END, rt);
        size[rt] += size[v[i].END];
    }
}
void Get_Root(int rt, int fa)
{
    Max[rt] = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa || vis[v[i].END] == mid) continue;
        Max[rt] = max(Max[rt], size[v[i].END]);
        Get_Root(v[i].END, rt);
    }
    Max[rt] = max(Max[rt], Sum - Max[rt]);
    if (Max[rt] < Max[root]) root = rt;
}
int Mx[MAXN << 2];
const int INF = 0x80808080;
void Pushup(int rt)
{
    Mx[rt] = max(Mx[rt << 1], Mx[rt << 1 | 1]);
}
void Update(int x, int c, int l, int r, int rt)
{
    if (l == r)
    {
        Mx[rt] = max(c, Mx[rt]);
        return;
    }
    int mid = l + r >> 1;
    if (x <= mid) Update(x, c, l, mid, rt << 1);
    else Update(x, c, mid + 1, r, rt << 1 | 1);
    Pushup(rt);
}
void Remove(int x, int l, int r, int rt)
{
    if (l == r)
    {
        Mx[rt] = INF;
        return;
    }
    int mid = l + r >> 1;
    if (x <= mid) Remove(x, l, mid, rt << 1);
    else Remove(x, mid + 1, r, rt << 1 | 1);
    Pushup(rt);
}
int Query(int L, int R, int l, int r, int rt)
{
    if (L > R) return INF;
    if (L <= l && R >= r)
        return Mx[rt];
    int mid = l + r >> 1;
    int ans = INF;
    if (L <= mid) ans = max(ans, Query(L, R, l, mid, rt << 1));
    if (R > mid) ans = max(ans, Query(L, R, mid + 1, r, rt << 1 | 1));
    return ans;
}
int n, L, R;
void dfs_build(int rt, int fa, int dep, int len)
{
    if (dep > R) return;
    Update(dep, len, 1, R, 1);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa || vis[v[i].END] == mid) continue;
        dfs_build(v[i].END, rt, dep + 1, len + ((v[i].v < mid) ? -1 : 1));
    }
}
int Ans = INF;
void dfs_Update(int rt, int fa, int dep, int len)
{
    if (dep > R) return;
    Ans = max(Ans, len + Query(max(L - dep, 1), R - dep, 1, R, 1));
    if (dep >= L) Ans = max(Ans, len);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa || vis[v[i].END] == mid) continue;
        dfs_Update(v[i].END, rt, dep + 1, len + ((v[i].v < mid) ? -1 : 1));
    }
}
void dfs_remove(int rt, int fa, int dep)
{
    if (dep > R) return;
    Remove(dep, 1, R, 1);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa || vis[v[i].END] == mid) continue;
        dfs_remove(v[i].END, rt, dep + 1);
    }
}
void Calc(int rt)
{
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (vis[v[i].END] == mid) continue;
        dfs_Update(v[i].END, rt, 1, ((v[i].v < mid) ? -1 : 1));
        dfs_build(v[i].END, rt, 1, ((v[i].v < mid) ? -1 : 1));
    }
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (vis[v[i].END] == mid) continue;
        dfs_remove(v[i].END, rt, 1);
    }
}
void Solve(int rt)
{
    vis[rt] = mid;
    Calc(rt);
    Get_Size(rt, 0);
    // printf ("%d\n", rt);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (vis[v[i].END] != mid)
        {
            root = 0, Sum = size[v[i].END];
            Get_Root(v[i].END, 0);
            Solve(root);
        }
    }
}
int main()
{
    memset (Mx, 0x80, sizeof (Mx));
    memset (first, -1, sizeof (first));
    n = read(), L = read(), R = read();
    int r = 0;
    for (int i = 1; i < n; i++)
    {
        int a = read(), b = read(), c = read();
        add(a, b, c);
        add(b, a, c);
        r = max(r, c);
    }
    int l = 0;
    int ans;
    while (l <= r)
    {
        mid = l + r >> 1;
        // mid = 27628;
        Max[0] = Sum = n;
        // memset (vis, 0, sizeof (vis));
        root = 0;
        Get_Size(1, 0);
        Get_Root(1, 0);
        Ans = INF;
        Solve(root);
        // printf ("mid = %d\n", mid);
        if (Ans >= 0) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    printf ("%d\n", ans);
}