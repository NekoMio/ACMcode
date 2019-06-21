#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 200005;
const int INF = 0x3f3f3f3f;
struct edge
{
    int S, E, id, v;
    bool nok;
    bool operator < (const edge &a) const 
    {
        // if (a.nok) return 0;
        // if (nok) return 0;
        return v < a.v;
    }
    bool operator > (const edge &a) const 
    {
        return id < a.id;
    }
}v[1000005];
map<int, int> a[MAXN >> 1];
struct Node
{
    Node *ch[2], *f;
    int s, Max, v, id, MaxID;
    bool flip;
    Node()
    {
        s = 1, Max = -INF;
        flip = 0, id = -1;
        ch[0] = ch[1] = f = NULL;
    }
}*null, *Q[2000005];
inline Node* NewNode(int x, int id)
{
    Node *o = new Node();
    o->Max = o->v = x;
    o->id = o->MaxID = id;
    o->ch[0] = o->ch[1] = o->f = null;
    return o; 
}
inline int son(Node *rt)
{
    return rt->f->ch[1] == rt;
}
inline void Pushflip(Node *rt)
{
    if (rt == null) return;
    rt->flip ^= 1, swap(rt->ch[0], rt->ch[1]);
}
inline void Pushdown(Node *rt)
{
    if (rt->flip)
    {
        Pushflip(rt->ch[0]);
        Pushflip(rt->ch[1]);
        rt->flip = 0;
    }
}
inline void Pushup(Node *rt)
{
    if (rt == null) return;
    rt->Max = rt->v;
    rt->MaxID = rt->id;
    if (rt->ch[0]->Max > rt->Max)
        rt->Max = rt->ch[0]->Max, rt->MaxID = rt->ch[0]->MaxID;
    if (rt->ch[1]->Max > rt->Max)
        rt->Max = rt->ch[1]->Max, rt->MaxID = rt->ch[1]->MaxID;  
    rt->s = 1 + rt->ch[0]->s + rt->ch[1]->s;
}
inline bool IsRoot(Node *rt)
{
    return rt->f->ch[0] != rt && rt->f->ch[1] != rt;
}
inline void rotate(Node *rt)
{
    if (IsRoot(rt)) return;
    Node *fa = rt->f, *Grand = fa->f;
    Pushdown(fa), Pushdown(rt);
    int tmp = IsRoot(fa);
    int k = son(rt), kk = son(fa);
    fa->ch[k] = rt->ch[k ^ 1];
    if (rt->ch[k ^ 1] != null) rt->ch[k ^ 1]->f = fa;
    rt->ch[k ^ 1] = fa, fa->f = rt, rt->f = Grand;
    if (!tmp) Grand->ch[kk] = rt;
    Pushup(fa), Pushup(rt);
}
inline void Clear(Node *rt)
{
    if (!IsRoot(rt)) Clear(rt->f);
    Pushdown(rt);
}
inline void Splay(Node *rt)
{
    for (Clear(rt); !IsRoot(rt); rotate(rt))
        if (!IsRoot(rt->f))
            rotate(son(rt->f) == son(rt) ? rt->f : rt);
}
inline void Access(Node *rt)
{
    for (Node *pre = null; rt != null; pre = rt, rt = rt->f)
    {
        Splay(rt);
        rt->ch[1] = pre;
        Pushup(rt);
    }
}
inline void MakeRoot(Node *rt)
{
    Access(rt);
    Splay(rt);
    Pushflip(rt);
}
inline void link(Node *a, Node *b)
{
    MakeRoot(a);
    a->f = b;
}
inline void cut(Node *a, Node *b)
{
    MakeRoot(a);
    Access(b);
    Splay(b);
    Pushdown(b);
    b->ch[0]->f = null;
    b->ch[0] = null;
    Pushup(b);
}
struct Query_data
{
    int a, b;
    bool type;
}Query[100005];
int father[100005];
int ans[100005], cnt;
int find(int x)
{
    if (father[x] != x) father[x] = find(father[x]);
    return father[x];
}
int main()
{
    // freopen ("tube_strong.in", "r", stdin);
    // freopen ("tube_strong.out", "w", stdout);
    null = new Node();
    null->s = 0;
    null->ch[0] = null->ch[1] = null->f = null;
    int n = read(), m = read(), q = read();
    for (int i = 1; i <= m; i++)
    {
        v[i].S = read(), v[i].E = read(), v[i].v = read();
        v[i].nok = 0;
        v[i].id = i;
        a[v[i].S][v[i].E] = i;
        a[v[i].E][v[i].S] = i;
    }
    for (int i = 1; i <= q; i++)
    {
        Query[i].type = (read() == 1), Query[i].a = read(), Query[i].b = read();
        if (!Query[i].type)
            v[a[Query[i].a][Query[i].b]].nok = 1;
    }
    sort(v + 1, v + m + 1);
    for (int i = 1; i <= n; i++) father[i] = i, Q[i] = NewNode(-INF, -1);
    for (int i = 1; i <= m; i++)
    {
        if (v[i].nok) continue;
        if (find(v[i].S) != find(v[i].E))
        {
            Q[v[i].id + n] = NewNode(v[i].v, v[i].id);
            link(Q[v[i].id + n], Q[v[i].S]);
            link(Q[v[i].id + n], Q[v[i].E]);
            father[find(v[i].S)] = find(v[i].E);
        }
    }
    sort(v + 1, v + m + 1, greater<edge>());
    for (int i = q; i >= 1; i--)
    {
        if (Query[i].type)
        {
            MakeRoot(Q[Query[i].a]);
            Access(Q[Query[i].b]);
            Splay(Q[Query[i].b]);
            ans[++cnt] = Q[Query[i].b]->Max;
        }
        else
        {
            MakeRoot(Q[Query[i].a]);
            Access(Q[Query[i].b]);
            Splay(Q[Query[i].b]);
            int now = a[Query[i].a][Query[i].b];
            if (Q[Query[i].b]->Max > v[now].v)
            {
                int id = Q[Query[i].b]->MaxID;
                cut(Q[id + n], Q[v[id].S]);
                cut(Q[id + n], Q[v[id].E]);
                Q[now + n] = NewNode(v[now].v, now);
                link(Q[now + n], Q[v[now].S]);
                link(Q[now + n], Q[v[now].E]);
            }
        }
    }
    for (int i = cnt; i >= 1; i--)
        printf ("%d\n", ans[i]);
}