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
const int MOD = 10007;
const int MAXN = 50005;
int p[MAXN];
int pow_mod(int a, int b)
{
    int ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
struct fanc
{
    int k, b;
    fanc(int x = 0, int y = 0){k = x, b = y;}
    fanc operator () (fanc x) 
    {
        return fanc(k * x.k % MOD, (k * x.b + b) % MOD);
    }
    int operator () (int x)
    {
        return (k * x + b) % MOD;
    }
};
struct Node
{
    Node *ch[2], *fa, *sp;
    fanc f, g;
    Node() {;}
    void Pushup() {g = ch[1]->g(f(ch[0]->g));}
}*id[MAXN], *null;
Node *NewNode(fanc x)
{
    Node *o = new Node;
    o->f = x, o->g = x;
    o->ch[0] = o->ch[1] = o->fa = o->sp = null;
    return o;
}
int son(Node *rt)
{
    return rt->fa->ch[1] == rt;
}
bool IsRoot(Node *rt)
{
    return rt->fa->ch[0] != rt && rt->fa->ch[1] != rt;
}
void rotate(Node *rt)
{
    if (IsRoot(rt)) return;
    Node *fa = rt->fa, *Grand = fa->fa;
    bool t = !IsRoot(fa);
    int k = son(rt), kk = son(fa);
    fa->ch[k] = rt->ch[k ^ 1];
    if (rt->ch[k ^ 1] != null) rt->ch[k ^ 1]->fa = fa;
    rt->ch[k ^ 1] = fa, fa->fa = rt, rt->fa = Grand;
    if (t) Grand->ch[kk] = rt;
    fa->Pushup(), rt->Pushup();
}
void Splay(Node *rt)
{
    for (; !IsRoot(rt); rotate(rt))
        if (!IsRoot(rt->fa))
            rotate(son(rt) == son(rt->fa) ? rt->fa : rt);
}
void Access(Node *rt)
{
    for (Node *pre = null; rt != null; pre = rt, rt = rt->fa)
    {
        Splay(rt);
        rt->ch[1] = pre;
        rt->Pushup();
    }
}
Node *find(Node *rt)
{
    Access(rt);
    Splay(rt);
    while (rt->ch[0] != null) rt = rt->ch[0];
    return rt;
}
int Query(Node *rt)
{
    Node *RT = find(rt), *v = RT->sp;
    Access(v), Splay(v);
    int k = v->g.k, b = v->g.b;
    if (k == 1) return b ? -1 : -2;
    int x = b * pow_mod(1 - k + MOD, MOD - 2) % MOD;
    Access(rt), Splay(rt);
    return rt->g(x);
}
int vis[MAXN], tot;
void DFS(int x)
{
    vis[x] = tot;
    if (vis[p[x]] == tot) 
        id[x]->sp = id[p[x]];
    else
    {
        id[x]->fa = id[p[x]];
        if (!vis[p[x]]) DFS(p[x]);
    }
}
void Modify(Node *rt, int k, Node *o, int b)
{
    Node *RT = find(rt);
    rt->f.k = k;
    rt->f.b = b;
    rt->Pushup();
    if (rt == RT) rt->sp = null;
    else
    {
        Access(rt);
        Splay(rt);
        rt->ch[0] = rt->ch[0]->fa = null;
        rt->Pushup();
        if (find(RT->sp) != RT)
        {
            Access(RT);
            Splay(RT);
            RT->fa = RT->sp;
            RT->sp = null;
        }
    }
    Access(rt);
    Splay(rt);
    if (find(o) == rt) rt->sp = o;
    else rt->fa = o;
}
int main()
{
    null = new Node;
    null->ch[0] = null->ch[1] = null->fa = null->sp = null;
    null->f = null->g = fanc(1, 0);
    int n = read();
    for (int i = 1; i <= n; i++)
    {
        int k = read();
        p[i] = read();
        int b = read();
        id[i] = NewNode(fanc(k, b));
    }
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            ++tot, DFS(i);
    int Q = read();
    char s[10];
    while (Q--)
    {
        scanf ("%s", s);
        if (s[0] == 'A')
            printf ("%d\n", Query(id[read()]));
        else
        {
            int a = read();
            int k = read(), c = read(), b = read();
            Modify(id[a], k, id[c], b);
        }
    }
}