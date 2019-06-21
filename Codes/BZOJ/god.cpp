#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define LL long long
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
const int N = 100005;
LL Min[N << 2], Max[N << 2], Sum[N << 2];
int Sqr[N << 2];
void Pushup(int rt)
{
    Min[rt] = min(Min[rt << 1], Min[rt << 1 | 1]);
    Max[rt] = max(Max[rt << 1], Max[rt << 1 | 1]);
    if (Sum[rt << 1] != -1 && Sum[rt << 1 | 1] != -1)
        Sum[rt] = Sum[rt << 1] + Sum[rt << 1 | 1];
    else
        Sum[rt] = -1;
}
void Pushdown(int rt, int s)
{
    if (Sqr[rt])
    {
        Sqr[rt << 1] += Sqr[rt];
        Sqr[rt << 1 | 1] += Sqr[rt];
        Sum[rt << 1] = Sum[rt << 1 | 1] = -1;
        if (Max[rt << 1] > 1)
            for (int i = 1; i <= Sqr[rt]; i++)
            {
                Max[rt << 1] = sqrt(Max[rt << 1]);
                Min[rt << 1] = sqrt(Min[rt << 1]);
                if (Max[rt << 1] == 1)
                    break;
            }
        if (Max[rt << 1 | 1] > 1)
            for (int i = 1; i <= Sqr[rt]; i++)
            {
                Max[rt << 1 | 1] = sqrt(Max[rt << 1 | 1]);
                Min[rt << 1 | 1] = sqrt(Min[rt << 1 | 1]);
                if (Max[rt << 1 | 1] == 1)
                    break;
            }
        if (Max[rt << 1 | 1] == Min[rt << 1 | 1])
            Sum[rt << 1 | 1] = Max[rt << 1 | 1] * (s >> 1);
        if (Max[rt << 1] == Min[rt << 1])
            Sum[rt << 1] = Max[rt << 1] * (s - (s >> 1));
        Sqr[rt] = 0;
    }
}
void buildtree(int l, int r, int rt)
{
    if (l == r)
    {
        scanf("%lld", &Min[rt]);
        Sum[rt] = Max[rt] = Min[rt];
        return;
    }
    int m = l + r >> 1;
    buildtree(lch);
    buildtree(rch);
    Pushup(rt);
}
void Update(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        Sqr[rt] += 1;
        Max[rt] = sqrt(Max[rt]), Min[rt] = sqrt(Min[rt]);
        Sum[rt] = -1;
        if (Max[rt] == Min[rt])
            Sum[rt] = Max[rt] * (r - l + 1);
        return;
    }
    Sum[rt] = -1;
    Pushdown(rt, r - l + 1);
    int m = l + r >> 1;
    if (L <= m)
        Update(L, R, lch);
    if (R > m)
        Update(L, R, rch);
    Pushup(rt);
}
LL Query(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        if (Max[rt] == Min[rt])
        {
            return Sum[rt] = Max[rt] * (r - l + 1);
        }
        if (Sum[rt] != -1)
            return Sum[rt];
    }
    Pushdown(rt, r - l + 1);
    LL ans = 0;
    int m = l + r >> 1;
    if (L <= m)
        ans += Query(L, R, lch);
    if (R > m)
        ans += Query(L, R, rch);
    return ans;
    Pushup(rt);
}
void print(int l, int r, int rt)
{
    printf("l=%d,r=%d,rt=%d,Sum[rt]=%lld\n", l, r, rt, Sum[rt]);
    if (l == r)
        return;
    int m = l + r >> 1;
    print(lch);
    print(rch);
}
int main()
{
    int n, m;
    //freopen("god.in", "r", stdin);
    //freopen("god.out", "w", stdout);
    scanf("%d", &n);
    buildtree(1, n, 1);
    scanf("%d", &m);
    int op, l, r;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &op, &l, &r);
        if (l > r)
            swap(l, r);
        if (op)
        {
            printf("%lld\n", Query(l, r, 1, n, 1));
        }
        else
        {
            Update(l, r, 1, n, 1);
        }
    }
#ifdef Mine
    //while (1)
        ;
#endif
}
