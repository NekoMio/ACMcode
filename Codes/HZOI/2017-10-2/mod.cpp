#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 100005;
int Max[N << 2], MOD[N << 2];
long long Sum[N << 2];
void PushUp(int rt)
{
    Max[rt] = max(Max[rt << 1], Max[rt << 1 | 1]);
    Sum[rt] = Sum[rt << 1] + Sum[rt << 1 | 1];
}
void BuildTree(int l, int r, int rt)
{
    if(l == r)
    {
        scanf("%d", &Max[rt]);
        Sum[rt] = Max[rt];
        return;
    }
    int m = l + r >> 1;
    BuildTree(l, m, rt << 1);
    BuildTree(m + 1, r, rt << 1 | 1);
    PushUp(rt);
}
void Update(int L, int R, int mod, int l, int r, int rt)
{
    if (Max[rt] < mod)
        return;
    if (l == r)
    {
        Max[rt] = Max[rt] % mod;
        Sum[rt] = Max[rt];
        return;
    }
    int m = l + r >> 1;
    if (L <= m) Update(L, R, mod, l, m, rt << 1);
    if (R > m) Update(L, R, mod, m + 1, r, rt << 1 | 1);
    PushUp(rt);
}
void Change(int x, int c, int l, int r, int rt)
{
    if (l == r)
    {
        Max[rt] = c, Sum[rt] = c;
        return;
    }
    int m = l + r >> 1;
    if (x <= m) Change(x, c, l, m, rt << 1);
    else Change(x, c, m + 1, r, rt << 1 | 1);
    PushUp(rt);
}
long long Query(int L, int R, int l, int r ,int rt)
{
    if (L <= l && R >= r)
        return Sum[rt];
    int m = l + r >> 1;
    long long ans = 0;
    if (L <= m) ans += Query(L, R, l, m, rt << 1);
    if (R > m) ans += Query(L, R, m + 1, r, rt << 1 | 1);
    return ans;
}
int main()
{
    freopen("mod.in", "r", stdin);
    freopen("mod.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    BuildTree(1, n, 1);
    int op, a, b, c;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &op);
        if(op == 1)
        {
            scanf("%d%d", &a, &b);
            printf("%lld\n", Query(a, b, 1, n ,1));
        }
        else if (op == 2)
        {
            scanf("%d%d%d", &a, &b, &c);
            Update(a, b, c, 1, n, 1);
        }
        else if (op == 3)
        {
            scanf("%d%d", &a, &b);
            Change(a, b, 1, n, 1);
        }
    }
}
