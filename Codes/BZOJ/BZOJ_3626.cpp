#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 50005;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct edge
{
    int END, next;
}v[N];
int first[N], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
struct data
{
    int x, z;
    int flag, id;
    bool operator < (const data &b) const
    {
        return x < b.x;
    }
}Q[N << 1];
int cnt = 0;
int dep[N], top[N], size[N], fa[N], son[N], id[N], Index;
void dfs1(int rt, int f, int Dep)
{
    dep[rt] = Dep;
    size[rt] = 1;
    fa[rt] = f;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        dfs1(v[i].END, rt, Dep + 1);
        size[rt] += size[v[i].END];
        if (size[v[i].END] > size[son[rt]]) son[rt] = v[i].END;
    }
}
void dfs2(int rt, int tp)
{
    top[rt] = tp;
    id[rt] = ++Index;
    if (son[rt]) dfs2(son[rt], tp);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if(v[i].END == son[rt]) continue;
        dfs2(v[i].END, v[i].END);
    }
}
int ans[N];
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
int Sum[N << 2], lazy[N << 2];
void Pushup(int rt)
{
    Sum[rt] = Sum[rt << 1] + Sum[rt << 1 | 1];
}
void Pushdown(int rt, int m)
{
    if (lazy[rt])
    {
        lazy[rt << 1] += lazy[rt];
        lazy[rt << 1 | 1] += lazy[rt];
        Sum[rt << 1] += (m - (m >> 1)) * lazy[rt];
        Sum[rt << 1 | 1] += (m >> 1) * lazy[rt];
        lazy[rt] = 0;
    }
}
void Update(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        Sum[rt] += (r - l + 1);
        lazy[rt] += 1;
        return;
    }
    Pushdown(rt, r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, lch);
    if (R > m) Update(L, R, rch);
    Pushup(rt);
}
int Query(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
        return Sum[rt];
    int m = (l + r) >> 1;
    Pushdown(rt, r - l + 1);
    int ans = 0;
    if (L <= m) ans += Query(L, R, lch);
    if (R > m) ans += Query(L, R, rch);
    return ans;
}
int n, q;
void Update(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        Update(id[top[x]], id[x], 1, n, 1);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    Update(id[x], id[y], 1, n, 1);
}
int Query(int x, int y)
{
    int ans = 0;
    while (top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        ans += Query(id[top[x]], id[x], 1, n, 1);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    ans += Query(id[x], id[y], 1, n, 1);
    return ans;
}
int main()
{
    n = read(), q = read();
    memset (first, -1, sizeof (first));
    int a = 0;
    for (int i = 2; i <= n; i++)
    {
        a = read();
        add(a + 1, i);
    }
    int b, c;
    for (int i = 1; i <= q; i++)
    {
        a = read(), b = read(), c = read();
        a++, b++, c++;
        Q[++cnt].x = a - 1, Q[cnt].z = c, Q[cnt].flag = -1, Q[cnt].id = i;
        Q[++cnt].x = b, Q[cnt].z = c, Q[cnt].flag = 1, Q[cnt].id = i;
    }
    dfs1(1, 0, 0);
    dfs2(1, 0);
    sort(Q + 1, Q + cnt + 1);
    int Now = 0;
    for (int i = 1; i <= cnt; i++)
    {
        while (Now < Q[i].x)
        {
            Now++,
            Update(1, Now);
        }
        ans[Q[i].id] += Q[i].flag * Query(1, Q[i].z);
    }
    for (int i = 1; i <= q; i++)
        printf("%d\n", ans[i] % 201314);
}
