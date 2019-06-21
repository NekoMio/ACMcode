#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
static inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 10005;
struct Node
{
    Node *f, *ch[2];
    int v, Max, Min;
    bool Mark, flip;
    bool flag;
    Node()
    {
        f = ch[0] = ch[1] = NULL;
        Mark = 0, flag = 0, flip = 0;
    }
}*null, *Q[MAXN << 1];
static inline Node *NewNode(int x, bool fl)
{
    Node *o = new Node();
    o->f = o->ch[0] = o->ch[1] = null;
    if (fl) o->v = o->Max = o->Min = x;
    else o->v = 0, o->Max = -INF, o->Min = INF;
    o->flag = fl;
    return o;
}
static inline bool son(Node *rt)
{
    return rt->f->ch[1] == rt;
}
static inline void PushMark(Node *rt)
{
    if (rt == null) return;
    rt->Mark ^= 1, swap(rt->ch[0], rt->ch[1]);
}
static inline void Pushflip(Node *rt)
{
    if (rt == null) return;
    rt->flip ^= 1, swap(rt->Max, rt->Min);
    rt->v = -rt->v;
    rt->Max = -rt->Max;
    rt->Min = -rt->Min;
}
static inline void Pushdown(Node *rt)
{
    if (rt->Mark)
    {
        PushMark(rt->ch[0]);
        PushMark(rt->ch[1]);
        rt->Mark = 0;
    }
    if (rt->flip)
    {
        Pushflip(rt->ch[0]);
        Pushflip(rt->ch[1]);
        rt->flip = 0;
    }
}
static inline void Pushup(Node *rt)
{
    if (rt->flag == 0)
        rt->Min = INF, rt->Max = -INF;
    else rt->Min = rt->Max = rt->v;
    rt->Min = min(rt->Min, rt->ch[0]->Min);
    rt->Max = max(rt->Max, rt->ch[0]->Max);
    rt->Min = min(rt->Min, rt->ch[1]->Min);
    rt->Max = max(rt->Max, rt->ch[1]->Max);
}
static inline bool IsRoot(Node *rt)
{
    return rt->f->ch[0] != rt && rt->f->ch[1] != rt;
}
static inline void rotate(Node *rt)
{
    if (IsRoot(rt)) return;
    Node *fa = rt->f, *Grand = fa->f;
    int tmp = IsRoot(fa);
    Pushdown(fa), Pushdown(rt);
    int k = son(rt), kk = son(fa);
    fa->ch[k] = rt->ch[k ^ 1];
    if (rt->ch[k ^ 1] != null) rt->ch[k ^ 1]->f = fa;
    rt->ch[k ^ 1] = fa, fa->f = rt, rt->f = Grand;
    if (!tmp) Grand->ch[kk] = rt;
    Pushup(fa);
    Pushup(rt);
}
static inline void Clear(Node *rt)
{
    if (!IsRoot(rt)) Clear(rt->f);
    Pushdown(rt);
}
static inline void Splay(Node *rt)
{
    for (Clear(rt); !IsRoot(rt); rotate(rt))
        if (!IsRoot(rt->f))
            rotate(son(rt) == son(rt->f) ? rt->f : rt);
}
static inline Node *Access(Node *rt)
{
    Node *pre = null;
    for (; rt != null; pre = rt, rt = rt->f)
    {
        Splay(rt);
        rt->ch[1] = pre;
        Pushup(rt);
    }
    return pre;
}
static inline void MakeRoot(Node *rt)
{
    Access(rt);
    Splay(rt);
    PushMark(rt);
}
static inline void link(Node *a, Node *b)
{
    MakeRoot(a);
    a->f = b;
}
int main()
{
    int n = read();
    null = new Node();
    null->f = null->ch[0] = null->ch[1] = null;
    null->flag = 0;
    null->v = 0, null->Max = -INF, null->Min = INF;
    for (int i = 1; i <= n; i++)
    {
        Q[i] = NewNode(0, 0);
        Pushup(Q[i]);
    }
    for (int i = 1; i < n; i++)
    {
        int a = read(), b = read(), c = read();
        Q[i + n] = NewNode(c, 1);
        Pushup(Q[i + n]);
        link(Q[a], Q[i + n]);
        link(Q[b], Q[i + n]);
    }
    while (1)
    {
        static char s[10];
        scanf ("%s", s);
        if (s[0] == 'D') break;
        int a = read(), b = read();
        if (s[0] == 'Q')
        {
            MakeRoot(Q[a]);
            Node *x = Access(Q[b]);
            printf ("%d\n", x->Max);
        }
        else if (s[0] == 'C')
        {
            MakeRoot(Q[a + n]);
            Q[a + n]->v = b;
            Pushup(Q[a + n]);
        }
        else
        {
            MakeRoot(Q[a]);
            Node *x = Access(Q[b]);
            Pushflip(x);
        }
    }
}