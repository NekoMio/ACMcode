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
const int MAXN = 100005;
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
struct Node
{
    Node *ch[2];
    long long Min;
    Node()
    {
        Min = 0x3f3f3f3f3f3f3f3fll;
        ch[0] = ch[1] = NULL;
    }
}*Root[MAXN];
int n;
void Insert(Node *&rt, int x, long long c, int l = 1, int r = n)
{
    if (rt == NULL) rt = new Node();
    rt->Min = min(rt->Min, c);
    if (l == r) return;
    int mid = l + r >> 1;
    if (x <= mid) Insert(rt->ch[0], x, c, l, mid);
    else Insert(rt->ch[1], x, c, mid + 1, r);
}
long long Query(Node *rt, int l, int r, int L, int R)
{
    if (!rt) return 0x3f3f3f3f3f3f3f3fll;
    if (L <= l && R >= r)
        return rt->Min;
    int mid = l + r >> 1;
    long long ans = 0x3f3f3f3f3f3f3f3fll;
    if (L <= mid) ans = min(ans, Query(rt->ch[0], l, mid, L, R));
    if (R > mid) ans = min(ans, Query(rt->ch[1], mid + 1, r, L, R));
    return ans;
}
int fa[MAXN];
bool vis[MAXN];
int size[MAXN], Max[MAXN], root, Sum;
void Get_Root(int rt, int fa)
{
    size[rt] = 1;
    Max[rt] = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (!vis[v[i].END] && v[i].END != fa)
        {
            Get_Root(v[i].END, rt);
            size[rt] += size[v[i].END];
            Max[rt] = max(Max[rt], size[v[i].END]);
        }
    }
    Max[rt] = max(Max[rt], Sum - size[rt]);
    if (Max[rt] < Max[root]) root = rt;
}
void DFS(int rt, int f, int t, long long d = 0)
{
    Insert(Root[t], rt, d);
    for (int i = first[rt]; i != -1; i = v[i].next)
        if (v[i].END != f && !vis[v[i].END])
            DFS(v[i].END, rt, t, d + v[i].v);
}
long long len[MAXN];
void Solve(int rt, int f, long long d = 0)
{
    fa[rt] = f;
    len[rt] = d;
    vis[rt] = 1;
    DFS(rt, 0, rt);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (!vis[v[i].END])
        {
            root = 0, Sum = size[v[i].END];
            Get_Root(v[i].END, 0);
            Solve(root, rt, Query(Root[rt], 1, n, root, root));
        }
    }
}
int main()
{
    memset (first, -1, sizeof (first));
    n = read();
    for (int i = 1; i < n; i++)
    {
        int a = read(), b = read(), c = read();
        add(a, b, c);
        add(b, a, c);
    }
    root = 0;
    Max[0] = Sum = n;
    Get_Root(1, 0);
    Solve(root, 0);
    int q = read();
    while (q--)
    {
        int L = read(), R = read();
        int x = read(), S = x;
        long long ans = 0x3f3f3f3f3f3f3f3fll;
        // long long tmp = 0;
        while (x)
        {
            ans = min(ans, Query(Root[x], 1, n, S, S) + Query(Root[x], 1, n, L, R));
            // tmp += len[x];
            x = fa[x];
        }
        printf ("%lld\n", ans);
    }
 
    // while (1);
}
