#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 2 * 1e5 + 5;
const int INF = 0x3f3f3f3f;
struct data
{
    int p, c, id;
    bool mark;
    bool operator < (const data &a) const{
        return p < a.p;
    }
}a[N];
int n;
int f[N];
int H[N << 2], Min[N << 2], lf[N << 2];
#ifndef lch
#define lch  l, m, rt << 1
#endif
#ifndef rch
#define rch m + 1, r, rt << 1 | 1
#endif
int Calc(int MaxH, int l, int r, int rt)
{
    if (l == r) return Min[rt];
    int m = l + r >> 1;
    if (H[rt << 1] < H[rt << 1 | 1]) return Calc(MaxH, rch);
    else
    {
        if (H[rt << 1 | 1] < MaxH) return Calc(MaxH, lch);
        else return min(lf[rt << 1], Calc(MaxH, rch));
    }
}
void Pushup(int l, int r, int rt)
{
    H[rt] = max(H[rt << 1], H[rt << 1 | 1]);
    int m = l + r >> 1;
    if (H[rt << 1 | 1] > H[rt << 1]) Min[rt] = Min[rt << 1 | 1], lf[rt << 1] = INF;
    else
        Min[rt] = min(lf[rt << 1] = Calc(H[rt << 1 | 1], lch), Min[rt << 1 | 1]);
}
int MH;
int Query(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        if (H[rt] < MH) return INF;
        else
        {
            int tmp = Calc(MH, l, r, rt);
            MH = H[rt];
            return tmp;
        }
    }
    int m = l + r >> 1;
    int ans = INF;
    if (R > m) ans = min(ans, Query(L, R, rch));
    if (L <= m) ans = min(ans, Query(L, R, lch));
    return ans;
}
void Update(int pos, int l, int r, int rt)
{
    if (l == r)
    {
        H[rt] = a[pos].p; Min[rt] = f[a[pos].id];
        return;
    }
    int m = l + r >> 1;
    if (a[pos].id <= m) Update(pos, lch);
    else Update(pos, rch);
    Pushup(l, r, rt);
}
int main()
{
    scanf("%d", &n);
    memset (lf, 0x3f, sizeof (lf));
    memset (Min, 0x3f, sizeof (Min));
    for (int i = 1; i <= n; i++)
    {
        scanf ("%d", &a[i].p);
        a[i].id = i;
    }
    for (int i = 1; i <= n; i++)
        scanf ("%d", &a[i].c);
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++)
    {
        MH = 0;
        int tmp = Query(1, a[i].id, 1, n, 1);
        if (tmp >= INF) f[a[i].id] = a[i].c;
        else f[a[i].id] = tmp + a[i].c;
        Update(i, 1, n, 1);
    }
    MH = 0;
    printf ("%d", Query(1, n, 1, n, 1));
}
