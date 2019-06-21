#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 51061;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1e5 + 5;
struct Node
{
    Node *ch[2], *f;
    unsigned int v, Sum, s;
    unsigned int Mul, Add;
    bool flip;
    Node()
    {
        v = Sum = Add = 0;
        s = 1;
        Mul = 1;
        flip = 0;
        ch[0] = ch[1] = f = NULL;
    }
}*null, *Q[MAXN];
inline Node *NewNode(int x)
{
    Node *o = new Node();
    o->v = o->Sum = x;
    o->ch[0] = o->ch[1] = o->f = null;
    return o;
}
inline int son(Node *rt)
{
    return rt->f->ch[1] == rt;
}
inline bool IsRoot(Node *rt)
{
    return rt->f->ch[0] != rt && rt->f->ch[1] != rt;
}
inline void Pushflip(Node *rt)
{
    if (rt == null) return;
    rt->flip ^= 1, swap(rt->ch[0], rt->ch[1]);
}
inline void PushAdd(Node *rt, int c)
{
    if (rt == null) return;
    rt->Sum = (rt->s * c % MOD + rt->Sum) % MOD;
    rt->v = (rt->v + c) % MOD;
    rt->Add = (rt->Add + c) % MOD;
}
inline void PushMul(Node *rt, int c)
{
    if (rt == null) return;
    rt->Sum = rt->Sum * c % MOD;
    rt->v = rt->v * c % MOD;
    rt->Mul = rt->Mul * c % MOD;
    rt->Add = rt->Add * c % MOD;
}
inline void Pushdown(Node *rt)
{
    if (rt->flip)
    {
        Pushflip(rt->ch[0]);
        Pushflip(rt->ch[1]);
        rt->flip = 0;
    }
    if (rt->Mul != 1)
    {
        PushMul(rt->ch[0], rt->Mul);
        PushMul(rt->ch[1], rt->Mul);
        rt->Mul = 1;
    }
    if (rt->Add != 0)
    {
        PushAdd(rt->ch[0], rt->Add);
        PushAdd(rt->ch[1], rt->Add);
        rt->Add = 0;
    }
}
inline void Pushup(Node *rt)
{
    rt->s = 1 + rt->ch[0]->s + rt->ch[1]->s;
    rt->Sum = ((rt->v + rt->ch[0]->Sum) % MOD + rt->ch[1]->Sum) % MOD;
}
inline void rotate(Node *rt)
{
    if (IsRoot(rt)) return;
    Node *fa = rt->f, *Grand = fa->f;
    Pushdown(fa); Pushdown(rt);
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
            rotate(son(rt) == son(rt->f) ? rt->f : rt);
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
int main()
{
    // freopen("nt2012_wym_tree.in", "r", stdin);
	// freopen("nt2012_wym_tree.out", "w", stdout);
    null = new Node();
    null->ch[0] = null->ch[1] = null->f = null;
    null->s = 0;
    int n = read();
    int q = read();
    for (int i = 1; i <= n; i++) Q[i] = NewNode(1);
    for (int i = 1; i < n; i++)
    {
        int a = read(), b = read();
        link(Q[a], Q[b]);
    }
    char s[10];
    while (q--)
    {
        scanf ("%s", s);
        if (s[0] == '+')
        {
            int a = read(), b = read();
            MakeRoot(Q[a]);
            Access(Q[b]);
            Splay(Q[b]);
            PushAdd(Q[b], read() % MOD);
        }
        else if (s[0] == '-')
        {
            int a = read(), b = read();
            cut(Q[a], Q[b]);
            a = read(), b = read();
            link(Q[a], Q[b]);
        }
        else if (s[0] == '*')
        {
            int a = read(), b = read();
            MakeRoot(Q[a]);
            Access(Q[b]);
            Splay(Q[b]);
            PushMul(Q[b], read() % MOD);
        }
        else if (s[0] == '/')
        {
            int a = read(), b = read();
            MakeRoot(Q[a]);
            Access(Q[b]);
            Splay(Q[b]);
            printf ("%d\n", Q[b]->Sum);
        }
    }
}