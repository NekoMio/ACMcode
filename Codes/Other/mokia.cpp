#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 800005;
struct Query
{
    int x, y, op, val, id, pos;
    bool operator < (const Query &a) const
    {
        return x == a.x ? op < a.op : x < a.x;
    }
} Ask[MAXN], tmp[MAXN];
int n, m, Ans[MAXN];
#define lowbit(_) ((_)&(-_))
struct BIT
{
    int Sum[2000005];
    void add(int x, int c)
    {
        for (int i = x; i <= n; i += lowbit(i))
            Sum[i] += c;
    }
    int Query(int x)
    {
        int ans = 0;
        for (int i = x; i > 0; i -= lowbit(i))
            ans += Sum[i];
        return ans;
    }
}bit;
void add()
{
    int x1, y1, x2, y2;
    scanf ("%d%d%d%d", &x1, &y1, &x2, &y2);
    ++Ans[0];
    Ask[++m].pos = Ans[0], Ask[m].x = x1 - 1, Ask[m].y = y1 - 1, Ask[m].val = 1, Ask[m].op = 1;
    Ask[++m].pos = Ans[0], Ask[m].x = x2    , Ask[m].y = y2    , Ask[m].val = 1, Ask[m].op = 1;
    Ask[++m].pos = Ans[0], Ask[m].x = x1 - 1, Ask[m].y = y2    , Ask[m].val =-1, Ask[m].op = 1;
    Ask[++m].pos = Ans[0], Ask[m].x = x2    , Ask[m].y = y1 - 1, Ask[m].val =-1, Ask[m].op = 1;
}
void CDQ(int l, int r)
{
    if (l == r)
        return;
    int mid = l + r >> 1, l1 = l, l2 = mid + 1;
    for (int i = l; i <= r; i++)
    {
        if (Ask[i].id <= mid && !Ask[i].op)
            bit.add(Ask[i].y, Ask[i].val);
        if (Ask[i].id > mid && Ask[i].op)
            Ans[Ask[i].pos] += Ask[i].val * bit.Query(Ask[i].y);
    }
    for (int i = l; i <= r; i++)
        if (Ask[i].id <= mid && !Ask[i].op)
            bit.add(Ask[i].y, -Ask[i].val);
    for (int i = l; i <= r; i++)
    {
        if (Ask[i].id <= mid)
            tmp[l1++] = Ask[i];
        else tmp[l2++] = Ask[i];
    }
    for (int i = l; i <= r; i++)
        Ask[i] = tmp[i];
    CDQ(l, mid);
    CDQ(mid + 1, r);
    return;
}
int main()
{
    freopen("mokia.in", "r", stdin);
    freopen("mokia.out", "w", stdout);
    int op;
    scanf ("%d%d", &op, &n);
    while (1)
    {
        scanf ("%d", &op);
        if (op == 1)
        {
            m++;
            scanf ("%d%d%d", &Ask[m].x, &Ask[m].y, &Ask[m].val);
        }
        else if (op == 2)
            add();
        else break;
    }
    for (int i = 1; i <= m; i++)
        Ask[i].id = i;
    sort(Ask + 1, Ask + m + 1);
    CDQ(1 ,m);
    for (int i = 1; i <= Ans[0]; i++)
        printf ("%d\n", Ans[i]);
}