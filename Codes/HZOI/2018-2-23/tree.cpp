#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 5005;
const int INF = 0x3f3f3f3f;
struct Priority_queue
{
    priority_queue<int> Q1, Q2;
    inline int size()
    {
        return Q1.size() - Q2.size();
    }
    inline void push(const int &x)
    {
        Q1.push(x);
    }
    inline void erase(const int &x)
    {
        Q2.push(x);
    }
    inline int top()
    {
        while (!Q2.empty() && Q1.top() == Q2.top())
        {
            Q1.pop();
            Q2.pop();
        }
        if (!Q1.empty()) return Q1.top();
        else return -INF;
    }
};
struct Node
{
    Node *f, *ch[2];
    int Max, s, Mx;
    bool flip;
    Priority_queue st;
    Node();
}*null, *Q[MAXN];
Node::Node()
{
    ch[0] = ch[1] = f = null;
    flip = 0;
    Max = Mx = 0;
    s = 1;
}
inline bool son(Node *rt)
{
    return rt->f->ch[1] == rt;
}
inline void Pushflip(Node *rt)
{
    if (rt == null) return;
    rt->flip ^= 1;
    swap(rt->ch[0], rt->ch[1]);
    swap(rt->Mx, rt->Max);
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
inline bool IsRoot(Node *rt)
{
    return rt->f->ch[0] != rt && rt->f->ch[1] != rt;
}
void Pushup(Node *rt)
{
    if (rt == null) return;
    //rt->Max = max(rt->st.top(), max(rt->ch[0]->Max, rt->ch[1]->Max)) + 1;
    rt->s = rt->ch[0]->s + rt->ch[1]->s + 1;
    rt->Max = rt->Mx = 0;
    rt->Max = max(rt->Max, rt->st.top() + rt->ch[0]->s);
    rt->Max = max(rt->Max, rt->ch[0]->Max);
    rt->Max = max(rt->Max, rt->ch[1]->Max + rt->ch[0]->s + 1);
 
    rt->Mx = max(rt->Mx, rt->st.top() + rt->ch[1]->s);
    rt->Mx = max(rt->Mx, rt->ch[1]->Mx);
    rt->Mx = max(rt->Mx, rt->ch[0]->Mx + rt->ch[1]->s + 1);
}
inline void rotate(Node *rt)
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
        if (pre != null) rt->st.erase(pre->Max + 1);
        if (rt->ch[1] != null) rt->st.push(rt->ch[1]->Max + 1);
        rt->ch[1] = pre;
        Pushup(rt);
    }
}
void MakeRoot(Node *rt)
{
    Access(rt);
    Splay(rt);
    Pushflip(rt);
    // Pushup(rt);
}
void link(Node *a, Node *b)
{
    MakeRoot(a);
    MakeRoot(b);
    a->f = b;
    b->st.push(a->Max + 1);
    Pushup(b);
}
void Cut(Node *a, Node *b)
{
    MakeRoot(a), 
    Access(b), Splay(b);
    Pushdown(b);
    // b->st.push(b->ch[0]->Max + 1);
    b->ch[0]->f = null;
    b->ch[0] = null;
    Pushup(b);
}
Node *find(Node *rt, int k)
{
    while (1)
    {
        Pushdown(rt);
        if (rt->ch[0]->s + 1 == k) return rt;
        if (k > rt->ch[0]->s + 1) k -= rt->ch[0]->s + 1, rt = rt->ch[1];
        else rt = rt->ch[0];
    }
    return NULL;
}
int main()
{
    // freopen("T3.in", "r", stdin);
    // freopen("T3.out", "w", stdout);
    null = new Node();
    null->f = null->ch[1] = null->ch[0] = null;
    null->Max = null->Mx = -INF;
    null->s = 0;
    int n = read();
    for (int i = 1; i <= n; i++) Q[i] = new Node(), Q[i] -> st.push(0);
    for (int i = 1; i < n; i++)
    {
        int a = read(), b = read();
        link(Q[a], Q[b]);
    }
    char ch[3];
    int m = read();
    while (m--)
    {
        scanf ("%s", ch);
        if (ch[0] == 'L')
        {
            int a = read(), b = read();
            Cut(Q[b], Q[a]);
            link(Q[a], Q[b]);
        }
        else
        {
            int a = read(), b = read();
            MakeRoot(Q[a]);
            Access(Q[b]);
            Splay(Q[b]);
            int size = Q[b]->s >> 1;
            Node *C1 = find(Q[b], size), *C2 = find(Q[b], size + 1);
            Cut(C1, C2);
            MakeRoot(Q[a]);
            int ans = 0;
            ans = max(ans, Q[a]->Max);
            MakeRoot(Q[b]);
            ans = max(ans, Q[b]->Max);
            link(C1, C2);
            printf ("%d\n", ans);
        }
    }
}