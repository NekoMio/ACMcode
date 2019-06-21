#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int N = 1e5 + 5;
struct edge
{
    int END, next;
}v[N << 1];
int first[N], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int f[N << 2][17];
int dep[N];
int L[N], R[N], cnt;
void dfs(int rt, int fa, int Dep)
{
    L[rt] = ++cnt;
    dep[rt] = Dep;
    f[rt][0] = fa;
    for (int i = 1; i <= 16; i++)
        f[rt][i] = f[f[rt][i - 1]][i - 1];
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        dfs(v[i].END, rt, Dep + 1);
    }
    R[rt] = ++cnt;
}
int LCA(int a, int b)
{
    if (dep[a] < dep[b]) swap(a, b);
    int d = dep[a] - dep[b];
    for (int i = 16; i >= 0; i--)
        if (d & (1 << i))
            d -= (1 << i), a = f[a][i];
    if (a == b) return a;
    for (int i = 16; i >= 0; i--)
        if (f[a][i] != f[b][i])
            a = f[a][i], b = f[b][i];
    return f[a][0];
}
struct data
{
    int a, b, lca;
    bool operator < (const data &c) const 
    {
        return dep[lca] > dep[c.lca];
    }
}Query[N * 3];
int Sum[N << 1];
#define lowbit(_) ((_)&(-_))
void U(int x, int c)
{
    for (int i = x; i <= cnt; i += lowbit(i))
        Sum[i] += c;
}
int Q(int x)
{
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += Sum[i];
    return ans;
}
int Ans[N];
int main()
{
    freopen("ping.in", "r", stdin);
    freopen("ping.out", "w", stdout);
    int n = read(), m = read();
    memset (first, -1, sizeof (first));
    int a, b;
    for (int i = 1; i <= m; i++)
    {
        a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    dfs(1, 0, 0);
    int k = read();
    for (int i = 1; i <= k; i++) 
    {
        Query[i].a = read();
        Query[i].b = read();
        Query[i].lca = LCA(Query[i].a, Query[i].b);
    }
    sort(Query + 1, Query + k + 1);
    int ans = 0;
    for (int i = 1; i <= k; i++)
    {
        if (Q(L[Query[i].a]) + Q(L[Query[i].b]) - Q(L[Query[i].lca]) - Q(L[Query[i].lca] - 1)) continue;
        U(L[Query[i].lca], 1), U(R[Query[i].lca], -1);
        Ans[++ans] = Query[i].lca;
    }
    printf ("%d\n", ans);
    for (int i = 1; i <= ans; i++)
        printf ("%d ", Ans[i]);
    fclose(stdin), fclose(stdout);
    return 0;
}