#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 2000010;
struct Query
{
    int opt, a, b;
}Q[N];
int v[N << 1];
int vl[N << 2], vr[N << 2], Max[N << 2], Map[N << 2];
int a[N], Hash[N], t, cnt;
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
int Queryl(int x, int l, int r, int rt)
{
    if (x > Max[rt]) return 0;
    if (l == r) return 1;
    int m = l + r >> 1;
    if (x > Max[rt << 1 | 1])
        return Queryl(x, lch);
    else
        return vl[rt << 1] + Queryl(x, rch);
}
int Queryr(int x, int l, int r, int rt)
{
    if (x > Max[rt]) return 0;
    if (l == r) return 1;
    int m = l + r >> 1;
    if (x > Max[rt << 1])
        return Queryr(x, rch);
    else 
        return Queryr(x, lch) + vr[rt << 1 | 1];
}
void Pushup(int l, int r, int rt)
{
    Max[rt] = Max[rt << 1], Map[rt] = Map[rt << 1];
    if (Max[rt << 1 | 1] > Max[rt])
        Max[rt] = Max[rt << 1 | 1], Map[rt] = Map[rt << 1 | 1];
    int m = l + r >> 1;
    vl[rt << 1] = Queryl(Max[rt << 1 | 1], lch);
    vr[rt << 1 | 1] = Queryr(Max[rt << 1], rch);
}
void Insert(int a, int b, int l, int r, int rt)
{
    if (l == r)
        return vl[rt] = vr[rt] = 1, Max[rt] = b, Map[rt] = l, void();
    int m = l + r >> 1;
    if (a <= m)
        Insert(a, b, lch);
    else
        Insert(a, b, rch);
    Pushup(l, r, rt);
}
void Delete(int a, int l, int r, int rt)
{
    if (l == r)
        return vl[rt] = vr[rt] = 0, Max[rt] = 0, void();
    int m = l + r >> 1;
    if (a <= m)
        Delete(a, lch);
    else
        Delete(a, rch);
    Pushup(l, r, rt);
}
typedef pair<long long, int> Pair;
Pair QueryMx(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
        return Pair(Max[rt], Map[rt]);
    int m = l + r >> 1;
    Pair Max(0, 0);
    if (L <= m)
        Max = max(Max, QueryMx(L, R, lch));
    if (R > m) 
        Max = max(Max, QueryMx(L, R, rch));
    return Max;
}
Pair QueryL(int L, int R, int x, int l, int r, int rt)
{
    if (L == l && R == r)
        return Pair(Queryl(x, L, R, rt), max(Max[rt], x));
    int m = l + r >> 1;
    if (R <= m)
        return QueryL(L, R, x, lch);
    else if (L > m)
        return QueryL(L, R, x, rch);
    else
    {
        Pair A = QueryL(m + 1, R, x, rch);
        Pair B = QueryL(L, m, A.second, lch);
        return Pair(A.first + B.first, max(A.second, B.second));
    }
}
Pair QueryR(int L, int R, int x, int l, int r, int rt)
{
    if (L == l && R == r)
        return Pair(Queryr(x, L, R, rt), max(Max[rt], x));
    int m = l + r >> 1;
    if (R <= m) 
        return QueryR(L, R, x, lch);
    else if (L > m)
        return QueryR(L, R, x, rch);
    else
    {
        Pair A = QueryR(L, m, x, lch);
        Pair B = QueryR(m + 1, R, A.second, rch);
        return Pair(A.first + B.first, max(A.second, B.second));
    }
}
int Dep(int x)
{
    int ret = 0;
    if (x > 1)
        ret += QueryL(1, x - 1, v[x], 1, cnt, 1).first;
    if (x < cnt)
        ret += QueryR(x + 1, cnt, v[x], 1, cnt, 1).first;
    return ret;
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &Q[i].opt);
        if (Q[i].opt == 0)
            scanf("%d%d", &Q[i].a, &Q[i].b), Hash[++t] = Q[i].a;
        else if (Q[i].opt == 1)
            scanf("%d", &Q[i].a);
        else if (Q[i].opt == 2)
            scanf("%d%d", &Q[i].a, &Q[i].b);
    }
    sort(Hash + 1, Hash + t + 1);
    cnt = unique(Hash + 1, Hash + t + 1) - Hash - 1;
    for (int i = 1; i <= n; i++)
    {
        if (Q[i].opt == 0)
            Q[i].a = lower_bound(Hash + 1, Hash + cnt + 1, Q[i].a) - Hash;
        else if (Q[i].opt == 1)
            Q[i].a = lower_bound(Hash + 1, Hash + cnt + 1, Q[i].a) - Hash;
        else if (Q[i].opt == 2)
            Q[i].a = lower_bound(Hash + 1, Hash + cnt + 1, Q[i].a) - Hash, Q[i].b = lower_bound(Hash + 1, Hash + cnt + 1, Q[i].b) - Hash;
    }
    for (int i = 1; i <= n; i++)
    {
        if (Q[i].opt == 0)
            Insert(Q[i].a, Q[i].b, 1, cnt, 1), v[Q[i].a] = Q[i].b;
        else if (Q[i].opt == 1)
            Delete(Q[i].a, 1, cnt, 1);
        else if (Q[i].opt == 2)
        {
            if (Q[i].a > Q[i].b)
                swap(Q[i].a, Q[i].b);
            int LCA = QueryMx(Q[i].a, Q[i].b, 1, cnt, 1).second;
            printf("%d\n", Dep(Q[i].a) + Dep(Q[i].b) - 2 * Dep(LCA));
        }
    }
    // while (1);
}

/**
12
0 4 17
0 10 38
0 2 21
0 1 61
2 1 10
2 10 4
1 10
1 1
0 8 42
2 8 4
2 8 2
2 4 2
*/