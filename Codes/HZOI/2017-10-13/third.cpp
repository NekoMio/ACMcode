#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1005;
int a[N];
int Max[N << 2], Min[N << 2], lazy[N << 2], Sum[10];
void Pushup(int rt)
{
    Max[rt] = max(Max[rt << 1], Max[rt << 1 | 1]);
    Min[rt] = min(Min[rt << 1], Min[rt << 1 | 1]);
}
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
void buildtree(int l, int r, int rt)
{
    if (l == r)
    {
        Max[rt] = Min[rt] = a[l];
        return;
    }
    int m = l + r >> 1;
    buildtree(lch);
    buildtree(rch);
    Pushup(rt);
}
void Pushdown(int rt)
{
    if (lazy[rt])
    {
        lazy[rt << 1] = lazy[rt << 1 | 1] = lazy[rt];
        Max[rt << 1] = Min[rt << 1] = Max[rt << 1 | 1] = Min[rt << 1 | 1] = lazy[rt];
        lazy[rt] = 0;
    }
}
void Update(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        Min[rt] = Max[rt] = c;
        lazy[rt] = c;
        return;
    }
    int m = l + r >> 1;
    Pushdown(rt);
    if (L <= m) Update(L, R, c, lch);
    if (R > m) Update(L, R, c, rch);
    Pushup(rt);
}
void Query(int L, int R, int l, int r, int rt)
{
    if (Max[rt] == Min[rt])
    {
        Sum[Max[rt]] += min(r, R) - max(l, L) + 1;
        return;
    }
    int m = l + r >> 1;
    Pushdown(rt);
    if (L <= m) Query(L, R, lch);
    if (R > m) Query(L, R, rch);
    Pushup(rt);
}
int ans[N];
void Get_Ans(int l, int r, int rt)
{
    if (Max[rt] == Min[rt])
    {
        for (int i = l; i <= r; i++)
            ans[i] = Max[rt];
        return;
    }
    int m = l + r >> 1;
    Pushdown(rt);
    Get_Ans(lch);
    Get_Ans(rch);
}
int main()
{
    int n, q;
    scanf ("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf ("%d", &a[i]);
    buildtree(1, n, 1);
    int l, r, op;
    while (q--)
    {
        scanf ("%d%d%d", &l, &r, &op);
        memset(Sum, 0, sizeof(Sum));
        Query(l, r, 1, n, 1);
        if (op == 0)
        {
            int now = l;
            for (int i = 1; i <= 7; i++)
                if (Sum[i])
                    Update(now, now + Sum[i] - 1, i, 1, n, 1), now += Sum[i];
        }
        else
        {
            int now = l;
            for (int i = 7; i >= 1; i--)
                if (Sum[i])
                    Update(now, now + Sum[i] - 1, i, 1, n, 1), now += Sum[i];
        }
    }
    Get_Ans(1, n, 1);
    for (int i = 1; i <= n; i++)
        printf ("%d ", ans[i]);
}