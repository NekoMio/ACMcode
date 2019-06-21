#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int INF = 1e9;
struct Seg_Node
{
    int l, r;
    Seg_Node *ch[2];
    int Sum;
} * root[100005], *null;
int a[100005];
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
void Update(int v, int l, int r, Seg_Node *&rt1, Seg_Node *rt2)
{
    copy(rt1, rt2);
    if(rt1==null)
        rt1=NewSeg_Node();
    rt1->Sum += v;
    rt1->l = l, rt1->r = r;
    if (l == r)
        return;
    int m = l + r >> 1;
    if (v <= m)
    {
        Update(v, l, m, rt1->ch[0], rt2->ch[0]);
    }
    else
    {
        Update(v, m + 1, r, rt1->ch[1], rt2->ch[1]);
    }
}
int Query(int R, int l, int r, Seg_Node *rt1, Seg_Node *rt2)
{
    if (R >= r)
        return rt1->Sum - rt2->Sum;
    int m = l + r >> 1;
    if (R <= m)
        return Query(R, l, m, rt1->ch[0], rt2->ch[0]);
    return Query(R, l, m, rt1->ch[0], rt2->ch[0]) + Query(R, m + 1, r, rt1->ch[1], rt2->ch[1]);
}
int main()
{
    null = new Seg_Node();
    null->ch[0] = null->ch[1] = null;
    root[0] = null;
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
    {
        Update(a[i], 1, 1e9, root[i], root[i - 1]);
    }
    int m;
    scanf("%d", &m);
    int a, b, ans;
    while (m--)
    {
        scanf("%d%d", &a, &b);
        int res = 1;
        ans = min(INF, Query(res, 1, 1e9, root[b], root[a - 1]));
        while (ans >= res && res < 1e9)
        {
            res = ans + 1;
            ans = min(INF, Query(res, 1, 1e9, root[b], root[a - 1]));
        }
        printf("%d\n", ans + 1);
    }
}
