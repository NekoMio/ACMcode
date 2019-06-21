#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 300005;
int a[N];
struct edge
{
    int v, next, END;
} v[N << 1];
int first[N], p = 1;
int n;
int dep[N], size[N], fa[N], id[N], son[N], val[N], top[N], num;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
void dfs1(int rt, int f, int Dep)
{
    dep[rt] = Dep;
    size[rt] = 1;
    son[rt] = 0;
    fa[rt] = f;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == f)
            continue;
        dfs1(v[i].END, rt, Dep + 1);
        size[rt] += size[v[i].END];
        if (size[son[rt]] < size[v[i].END])
            son[rt] = v[i].END;
    }
}
void dfs2(int rt, int tp)
{
    top[rt] = tp;
    id[rt] = ++num;
    if (son[rt])
        dfs2(son[rt], tp);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa[rt] || v[i].END == son[rt])
            continue;
        dfs2(v[i].END, v[i].END);
    }
}
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
int sum[N << 2], Add[N << 2];
void Pushup(int rt)
{
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void Pushdown(int rt, int m)
{
    if (Add[rt])
    {
        Add[rt << 1] += Add[rt];
        Add[rt << 1 | 1] += Add[rt];
        sum[rt << 1] += Add[rt] * (m - m / 2);
        sum[rt << 1 | 1] += Add[rt] * (m / 2);
        Add[rt] = 0;
    }
}
void update(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        sum[rt] += (r - l + 1) * c;
        Add[rt] += c;
        return;
    }
    int m = (l + r) >> 1;
    Pushdown(rt, r - l + 1);
    if (L <= m)
        update(L, R, c, lch);
    if (R > m)
        update(L, R, c, rch);
    Pushup(rt);
}
int query(int x, int l, int r, int rt)
{
    if (l == r)
        return sum[rt];
    Pushdown(rt, r - l + 1);
    int m = (l + r) >> 1;
    if (x <= m)
        return query(x, lch);
    else
        return query(x, rch);
}
void LCA(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        update(id[top[x]], id[x], 1, 1, n, 1);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    update(id[x], id[y], 1, 1, n, 1);
}
int main()
{
    memset(first, -1, sizeof(first));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    int b, c;
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &b, &c);
        add(b, c);
        add(c, b);
    }
    dfs1(1, 0, 1);
    dfs2(1, 1);
    int now = a[1];
    for (int i = 2; i <= n; i++)
    {
        LCA(now, a[i]);
        update(id[a[i]], id[a[i]], -1, 1, n, 1);
        now = a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        int ans = query(id[i], 1, n, 1);
        printf("%d\n", ans);
    }
    //while(1);
}
