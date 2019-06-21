#pragma GCC optimize ("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 101000;
char s[N];
int a[N];
int Max[N << 2], Min[N << 2], lazy[N << 2], Sum[30];
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1 
void PushUp(int rt)
{
    Max[rt] = max(Max[rt << 1], Max[rt << 1 | 1]);
    Min[rt] = min(Min[rt << 1], Min[rt << 1 | 1]);
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
    PushUp(rt);
}
void Update(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        lazy[rt] = c;
        Max[rt] = Min[rt] = c;
        return;
    }
    Pushdown(rt);
    int m = l + r >> 1;
    if (L <= m) Update (L, R, c, lch);
    if (R > m) Update (L, R, c, rch);
    PushUp(rt);
}
void Query(int L, int R, int l, int r, int rt)
{
    if (Max[rt] == Min[rt])
    {
        Sum[Max[rt]] += min(r, R) - max(L, l) + 1;
        return;
    }
    int m = l + r >> 1;
    Pushdown(rt);
    if (L <= m) Query(L, R, lch);
    if (R > m) Query(L, R, rch);
    PushUp(rt);
}
void Get_Ans(int l, int r, int rt)
{
    if (Max[rt] == Min[rt])
    {
        for (int i = l; i <= r; i++)
            a[i] = Max[rt];
        return;
    }
    int m = l + r >> 1;
    Pushdown(rt);
    Get_Ans(lch);
    Get_Ans(rch);
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    scanf("%s", s + 1);
    for (int i = 1; i <= n; i++)
        a[i] = s[i] - 'a' + 1;
    buildtree(1, n, 1);
    int l, r, op;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &l, &r, &op);
        if (op == 1)
        {
            memset(Sum, 0, sizeof(Sum));
            Query(l, r, 1, n, 1);
            int now = l;
            for (int i = 1; i <= 26; i++)
                if (Sum[i])
                    Update(now, now + Sum[i] - 1, i, 1, n, 1), now += Sum[i];
        }
        else
        {
            memset(Sum, 0, sizeof(Sum));
            Query(l, r, 1, n, 1);
            int now = l;
            for (int i = 26; i >= 1; i--)
                if (Sum[i])
                    Update(now, now + Sum[i] - 1, i, 1, n, 1), now += Sum[i];
        }
    }
    Get_Ans(1, n, 1);
    for (int i = 1; i <= n; i++)
    {
        printf("%c", char(a[i] + 'a' - 1));
    }
    // while (1);
}