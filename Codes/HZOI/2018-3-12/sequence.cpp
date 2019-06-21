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
const int MAXN = 1e5 + 5;
const int MAXM = 1e6 + 5;
int a[MAXN];
struct Quer
{
    int l, r, id;
}Q[MAXM];
int n, m;
struct edge
{
    int v, w, next;
}v[MAXN * 10];
int first[MAXN], p;
void add(int i, int x, int w)
{
    v[p].v = x;
    v[p].w = w;
    v[p].next = first[i];
    first[i] = p++;
}
struct Node
{
    Node *ch[2];
    int Min;
    Node()
    {
        Min = 0x3f3f3f3f;
    }
}*root[MAXN], *null;
Node *NewNode()
{
    Node *o = new Node();
    o->ch[0] = o->ch[1] = null;
    return o;
}
void Copy(Node *&a, Node *b)
{
    if (b == null) a = null;
    else a = NewNode(), *a = *b;
}
void Update(Node *&rt1, Node *rt2, int l, int r, int x, int c)
{
    if (l == r)
    {
        rt1->Min = min(rt1->Min, c);
        return;
    }
    int mid = l + r >> 1;
    if (x <= mid)
    {
        Copy(rt1->ch[0], rt2->ch[0]);
        if (rt1->ch[0] == null) rt1->ch[0] = NewNode();
        Update(rt1->ch[0], rt2->ch[0], l, mid, x, c);
    }
    else
    {
        Copy(rt1->ch[1], rt2->ch[1]);
        if (rt1->ch[1] == null) rt1->ch[1] = NewNode();
        Update(rt1->ch[1], rt2->ch[1], mid + 1, r, x, c);
    }
    rt1->Min = min(rt1->ch[0]->Min, rt1->ch[1]->Min);
}
int Query(Node *rt, int l, int r, int L, int R)
{
    if (L > R) return 2333333;
    if (L <= l && R >= r) return rt->Min;
    int mid = l + r >> 1;
    int ans = 2333333;
    if (L <= mid) ans = min(ans, Query(rt->ch[0], l, mid, L, R));
    if (R > mid) ans = min(ans, Query(rt->ch[1], mid + 1, r, L, R));
    return ans;
}
int T[MAXN];
void U(int x, int c)
{
    for (int i = x; i <= n; i += i & -i)
        T[i] = min(T[i], c);
}
int Qu(int x)
{
    int ans = 0x3f3f3f3f;
    for (int i = x; i > 0; i -= i & -i)
        ans = min(ans, T[i]);
    return ans;
}
int Mx, Mn;
int Ans[MAXM];
void Work()
{
    memset (first, -1, sizeof (first)); p = 0;
    memset (T, 0x3f, sizeof (T));
    for (int i = n; i > 0; i--)
    {
        int last = 0;
        Copy(root[i], root[i + 1]);
        if (root[i] == null) root[i] = NewNode();
        Update(root[i], root[i + 1], Mn, Mx, a[i], i);
        while (1)
        {
            if (!last) last = Query(root[i + 1], Mn, Mx, a[i], Mx);
            else last = Query(root[last + 1], Mn, Mx, a[i], (a[i] + a[last]) >> 1);
            if (last == 2333333) break;
            add(i, last, a[last] - a[i]);
        }
    }
    sort(Q + 1, Q + m + 1, [](const Quer &c, const Quer &b) -> bool {return c.l == b.l ? c.r < b.r : c.l < b.l;});
    int pos = n;
    for (int i = m; i >= 1; i--)
    {
        for (; pos >= Q[i].l && pos; pos--)
            for (int j = first[pos]; j != -1; j = v[j].next)
                U(v[j].v, v[j].w);
        Ans[Q[i].id] = min(Ans[Q[i].id], Qu(Q[i].r));
    }
}
int main()
{
    null = new Node();
    null->ch[0] = null->ch[1] = null;
    memset (Ans, 0x3f, sizeof (Ans));
    n = read();
    root[n + 1] = null;
    Mx = 0, Mn = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        a[i] = read(), Mx = max(Mx, a[i]), Mn = min(Mn, a[i]);
    m = read();
    for (int i = 1; i <= m; i++)
    {
        Q[i].l = read(), Q[i].r = read();
        Q[i].id = i;
    }
    Work();
    reverse(a + 1, a + n + 1);
    for (int i = 1; i <= m; i++) Q[i].l = n - Q[i].l + 1, Q[i].r = n - Q[i].r + 1, swap(Q[i].l, Q[i].r);
    for (int i = 1; i <= n; i++) root[i] = null;
    Work();
    for (int i = 1; i <= m; i++)
        printf ("%d\n", Ans[i]);
    // while (1);
}