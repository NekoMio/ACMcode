#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 1000005;
const int INF = 0x7fffffff;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct edge
{
    int END, next, v;
}v[N << 1], e[N << 1];
int first[N], p, head[N], t;
struct funadd
{
    void operator ()(int a, int b)
    {
        v[p].END = b;
        v[p].next = first[a];
        first[a] = p++;
    }
    void operator ()(int a, int b, int c)
    {
        e[t].END = b;
        e[t].v = c;
        e[t].next = head[a];
        head[a] = t++;
    }
}add;
int f[N << 1][21], dep[N], L[N], R[N], cnt;
void Init_Dfs(int rt, int fa, int Dep)
{
    L[rt] = ++cnt;
    f[rt][0] = fa;
    dep[rt] = Dep;
    for (int i = 1; i <= 20; i++)
        f[rt][i] = f[f[rt][i - 1]][i - 1];
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        Init_Dfs(v[i].END, rt, Dep + 1);
    }
    R[rt] = cnt;
}
int LCA(int x, int y)
{
    if (dep[x] < dep[y]) swap(x, y);
    int d = dep[x] - dep[y];
    for (int i = 20; i >= 0; i--)
        if (d & (1 << i))
            d -= (1 << i), x = f[x][i];
    if (x == y) return x;
    for (int i = 20; i >= 0; i--)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}
int pt[N], st[N], top, vis[N];
bool Query[N];
bool cmp(const int &a, const int &b)
{
    return L[a] < L[b];
}
#define In(a, b) (L[b] <= L[a] && R[a] <= R[b])
long long Min[N], Max[N], ans1, ans2, k;
long long size[N], Sum;
void dfs(int rt)
{
    size[rt] = Query[rt];
    Min[rt] = Query[rt] ? 0 : INF, Max[rt] = Query[rt] ? 0 : -INF;
    for (int i = head[rt]; i != -1; i = e[i].next)
    {
        dfs(e[i].END);
        size[rt] += size[e[i].END];
        Sum += size[e[i].END] * (k - size[e[i].END]) * e[i].v;
        ans1 = min(ans1, Min[rt] + Min[e[i].END] + e[i].v);
        Min[rt] = min(Min[rt], Min[e[i].END] + e[i].v);
        ans2 = max(ans2, Max[rt] + Max[e[i].END] + e[i].v);
        Max[rt] = max(Max[rt], Max[e[i].END] + e[i].v);
    }
}
signed main()
{
    // freopen ("tree1.in", "r", stdin);
    // freopen ("tree.out", "w", stdout);
    int n = read(), a, b;
    memset (first, -1, sizeof (first));
    memset (head, -1, sizeof (head));
    for (int i = 1; i < n; i++)
    {
        a = read(), b = read();
        add(a, b), add(b, a);
    }
    Init_Dfs(1, 0, 0);
    int Q = read();
    while (Q--)
    {
        k = read();
        int len = k;
        for (int i = 1; i <= k; i++)
            pt[i] = read(), Query[pt[i]] = true, vis[pt[i]] = Q + 1;
        sort (pt + 1, pt + len + 1, cmp);
        for (int i = 1; i < k; i++)
        {
            int lca = LCA(pt[i], pt[i + 1]);
            if (vis[lca] != Q + 1)
                pt[++len] = lca, vis[lca] = Q + 1;
        }
        sort(pt + 1, pt + len + 1, cmp);
        int root = pt[1];
        st[top = 1] = pt[1], t = 0;
        for (int i = 2; i <= len; i++)
        {
            while (top && !In(pt[i], st[top])) top--;
            st[++top] = pt[i];
            add(st[top - 1], st[top], dep[st[top]] - dep[st[top - 1]]);
        }
        Sum = 0, ans1 = INF, ans2 = -INF;
        dfs(root);
        printf ("%lld %lld %lld\n", Sum, ans1, ans2);
        for (int i = 1; i <= len; i++)
            Query[pt[i]] = 0, head[pt[i]] = -1;
    }
    // while (1);
}