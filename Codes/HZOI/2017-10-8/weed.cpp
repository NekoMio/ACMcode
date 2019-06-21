#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct M
{
    int op, v;
}a[200005];
int n;
const int N = 200005;
int Sum[N << 2], Add[N << 2], Del[N << 2], tmp[N << 2];
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
int Query(int l, int r, int rt, int val)
{
    if (Add[rt] <= val) return 0;
    if (l == r) return (val == 0 ? Sum[rt] : 0);
    int m = l + r >> 1;
    if (Add[rt << 1 | 1] >= val)
        return tmp[rt] + Query(rch, val);
    else
        return Query(lch, val - Add[rt << 1 | 1] + Del[rt << 1 | 1]);
}
void Pushup(int l, int r, int rt)
{
    int m = l + r >> 1;
    Sum[rt] = Sum[rt << 1 | 1];
    Add[rt] = Add[rt << 1 | 1];
    Del[rt] = Del[rt << 1];
    if (Add[rt << 1] >= Del[rt << 1 | 1])
    {
        Add[rt] += Add[rt << 1] - Del[rt << 1 | 1];
        Sum[rt] += (tmp[rt] = Query(l, m, rt << 1, Del[rt << 1 | 1]));
    }
    else Del[rt] += Del[rt << 1 | 1] - Add[rt << 1], tmp[rt] = 0;
}
void Buildtree(int l, int r, int rt)
{
    if (l == r)
    {
        if (a[l].op == 0)
            Sum[rt] = a[l].v, Add[rt] = 1, tmp[rt] = 0, Del[rt] = 0;
        else
            Del[rt] = a[l].v, tmp[rt] = 0, Sum[rt] = 0, Add[rt] = 0;
        return;
    }
    int m = l + r >> 1;
    Buildtree(lch);
    Buildtree(rch);
    Pushup(l, r, rt);
}
void Update(int x, int op, int v, int l, int r, int rt)
{
    if (l == r)
    {
        if (op == 0)
            Sum[rt] = v, Add[rt] = 1, tmp[rt] = 0, Del[rt] = 0;
        else
            Del[rt] = v, tmp[rt] = 0, Sum[rt] = 0, Add[rt] = 0;
        return;
    }
    int m = l + r >> 1;
    if (x <= m)
        Update(x, op, v, lch);
    else
        Update(x, op, v, rch);
    Pushup(l, r, rt);
}
int main()
{
    // freopen("weed.in", "r", stdin);
    // freopen("1.out", "w", stdout);
    int rp;
    scanf("%d%d", &n, &rp);
    for (int i = 1; i <= n; i++)
        scanf ("%d%d", &a[i].op, &a[i].v);
    Buildtree(1, n ,1);
    int c, x, y;
    while (rp--)
    {
        scanf("%d%d%d", &c, &x, &y);
        Update(c, x, y, 1, n, 1);
        printf ("%d\n", Sum[1]);
    }
}
