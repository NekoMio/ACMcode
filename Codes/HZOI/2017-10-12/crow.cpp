#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
// #define int long long
const int N = 100005;
int Sum[N << 2];
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
void Pushup(int rt)
{
    Sum[rt] = Sum[rt << 1] + Sum[rt << 1 | 1]; 
}
void Update(int x, int c, int l, int r, int rt)
{
    if (l == r)
    {
        Sum[rt] = c;
        return;
    }
    int m = l + r >> 1;
    if (x <= m) Update(x, c, lch);
    else Update(x, c, rch);
    Pushup(rt);
}
void buildtree(int l, int r, int rt)
{
    if (l == r)
    {
        Sum[rt] = 1;
        return;
    }
    int m = l + r >> 1;
    buildtree(lch);
    buildtree(rch);
    Pushup(rt);
}
int find(int w, int l, int r, int rt)
{
    if (l == r)
        return l;
    int m = l + r >> 1;
    if (Sum[rt << 1] >= w)
        return find(w, lch);
    else
        return find(w - Sum[rt << 1], rch);
}
int Query(int w, int L, int R, int l, int r, int rt)
{
    if (L == l && R == r)
    {
        if (Sum[rt] < w)
            return -Sum[rt];
        return find(w, l, r, rt);
    }
    int m = l + r >> 1;
    if (R <= m)
        return Query(w, L, R, lch);
    else if (L > m)
        return Query(w, L, R, rch);
    else
    {
        int s1 = Query(w, L, m, lch);
        if (s1 > 0) return s1;
        int s2 = Query(w + s1, m + 1, R, rch);
        if (s2 > 0) return s2;
        return s1 + s2;
    }    
}
int Query_Sum(int L, int R, int l, int r, int rt)
{
    if (L == l && R == r)
        return Sum[rt];
    int m = l + r >> 1;
    if (R <= m)
        return Query_Sum(L, R, lch);
    if (L > m)
        return Query_Sum(L, R, rch);
    return Query_Sum(L, m, lch) + Query_Sum(m + 1, R, rch);
}
struct data
{
    int w, id;
    bool operator < (const data & b) const 
    {
        return w == b.w ? id < b.id : w < b.w;
    }
}a[N];
signed main()
{
    int n, m, x;
    scanf ("%d%d%d", &n, &m, &x);
    for (int i = 1; i <= n; i++)
        scanf ("%d", &a[i].w);
    int c;
    for (int i = 1; i <= n; i++)
    {
        scanf ("%d", &c);
        a[i].id = i;
        if (a[i].w <= x)
            a[i].w = (int)(floor(1.0 * (x - a[i].w) / c) + 1);
        else a[i].w = 0;
    }
    sort(a + 1, a + n + 1);
    // for (int i = 1; i <= n; i++)
        // printf ("%d\n", a[i].id);
    // printf("\n\n");
    buildtree(1, n, 1);
    int ans = 0, index = 1;
    for (int i = 1; i <= m; i++)
    {
        int now = 0;
        while (index <= n)
        {
            if (!(a[index].w - ans))
            {
                Update(a[index].id, 0, 1, n, 1);
                ++index;
                // printf ("%d\n", index);
                continue;
            }
            if (now == n)
                break;
            int tmp = Query(a[index].w - ans, now + 1, n, 1, n, 1);
            if (tmp <= 0) break;
            Update(a[index].id, 0, 1, n, 1);
            now = tmp;
            ans = a[index].w;
            ++index;
        }
        if (now < n)
            ans += Query_Sum(now + 1, n, 1, n, 1);
    }
    printf ("%d", ans);
    // while (1);
}