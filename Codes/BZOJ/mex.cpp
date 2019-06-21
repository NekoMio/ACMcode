#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct Seg_Node
{
    int Min;
    Seg_Node *ch[2];
    Seg_Node()
    {
        Min = 0;
    }
} * root[200005], *null;
Seg_Node *NewSeg_Node()
{
    Seg_Node *S = new Seg_Node();
    S->ch[0] = S->ch[1] = null;
    return S;
}
void copy(Seg_Node *&a, Seg_Node *b)
{
    if (b == null)
        a = null;
    else
        a = NewSeg_Node(), *a = *b;
}
void Update(int v, int c, int l, int r, Seg_Node *&rt1, Seg_Node *rt2)
{
    copy(rt1, rt2);
    if (rt1 == null)
        rt1 = NewSeg_Node();
    if (l == r)
    {
        rt1->Min = c;
        return;
    }
    int m = l + r >> 1;
    if (v <= m)
        Update(v, c, l, m, rt1->ch[0], rt2->ch[0]);
    else
        Update(v, c, m + 1, r, rt1->ch[1], rt2->ch[1]);
    rt1->Min = min(rt1->ch[0]->Min, rt1->ch[1]->Min);
}
int Query(int l, int r, Seg_Node *rt, int x)
{
    if (l == r)
        return l;
    int mid = l + r >> 1;
    if (rt->ch[0]->Min < x)
        return Query(l, mid, rt->ch[0], x);
    else
        return Query(mid + 1, r, rt->ch[1], x);
}
int main()
{
    null = new Seg_Node();
    null->ch[0] = null->ch[1] = null;
    root[0] = null;
    int n, a, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a);
        Update(a, i, 0, 1e9, root[i], root[i - 1]);
    }
    int l, r;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &l, &r);
        printf("%d\n", Query(0, 1e9, root[r], l));
    }
}