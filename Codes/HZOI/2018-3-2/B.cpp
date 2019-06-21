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
const int MAXN = 1e5 + 5;
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
int dep[MAXN], fa[MAXN], top[MAXN], size[MAXN], son[MAXN];
int id[MAXN], Index;
void DFS1(int rt, int f)
{
    fa[rt] = f;
    dep[rt] = dep[f] + 1;
    size[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == f) continue;
        DFS1(v[i].END, rt);
        size[rt] += size[v[i].END];
        if (size[v[i].END] > size[son[rt]]) son[rt] = v[i].END;
    }
}
void DFS2(int rt, int t)
{
    top[rt] = t;
    id[rt] = ++Index;
    if (son[rt]) DFS2(son[rt], t);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END != fa[rt] && v[i].END != son[rt])
            DFS2(v[i].END, v[i].END);
    }
}
struct Node
{
    Node *ch[2];
    long long Sum;
    int flag;
}*root[100005], *null;
Node *NewNode()
{
    Node *o = new Node();
    o->ch[0] = o->ch[1] = null;
    o->Sum = o->flag = 0;
    return o;
}
void copy(Node *&a, Node *b)
{
    if (b == null) a = null;
    else a = NewNode(), *a = *b;
}
void Update(Node *rt1, Node *rt2, int L, int R, int l, int r, int c)
{
    if (L <= l && R >= r)
    {
        rt1->Sum += 1ll * (r - l + 1) * c;
        rt1->flag += c;
        return;
    }
    int mid = l + r >> 1;
    if (L <= mid)
    {
        if (rt1->ch[0] == rt2->ch[0]) copy(rt1->ch[0], rt2->ch[0]);
        if (rt1->ch[0] == null) rt1->ch[0] = NewNode();
        Update(rt1->ch[0], rt2->ch[0], L, R, l, mid, c);
    }
    if (R > mid)
    {
        if (rt1->ch[1] == rt2->ch[1]) copy(rt1->ch[1], rt2->ch[1]);
        if (rt1->ch[1] == null) rt1->ch[1] = NewNode();
        Update(rt1->ch[1], rt2->ch[1], L, R, mid + 1, r, c);
    }
    rt1->Sum = rt1->ch[0]->Sum + rt2->ch[1]->Sum;
}
void Update(int a, int b, int c, int t)
{
    copy(root[t], root[t - 1]);
    while (top[a] != top[b])
    {
        if (dep[top[a]] < dep[top[b]]) swap(a, b);
        Update(root[t], root[t - 1], id[top[a]], id[a], 1, Index, c);
        a = fa[top[a]];
    }
    if (dep[a] < dep[b])
        swap(a, b);
    Update(root[t], root[t - 1], id[b], id[a], 1, Index, c);
}
int Query(Node *rt, int x, int l, int r, int c)
{
    if (rt == null) return c;
    int mid = l + r >> 1;
    if (x <= mid) return Query(rt->ch[0], x, l, mid, c + rt->flag);
    else return Query(rt->ch[1], x, mid + 1, r, c + rt->flag);
}
int main()
{
    memset (first, -1, sizeof (first));
    null = new Node();
    null->ch[0] = null->ch[1] = null;
    null->Sum = 0;
    root[0] = NewNode();
    int n = read(), m = read(), q = read(), c = read();
    for (int i = 1; i < n; i++)
    {
        int a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    DFS1(1, 0);
    DFS2(1, 0);
    for (int i = 1; i <= m; i++)
    {
        int a = read(), b = read(), c = read();
        Update(a, b, c, i);
    }
    while (q--)
    {
        int a = read(), p = read() * c;
        int l = 1, r = m;
        int ans = -1;
        while (l <= r)
        {
            int mid = l + r >> 1;
            int x = Query(root[mid], id[a], 1, n, 0);
            if (x >= p) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        printf ("%d %d\n", ans, Query(root[m], id[a], 1, n, 0) % c);
    }
}