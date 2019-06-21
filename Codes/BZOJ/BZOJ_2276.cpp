#include <cstdio>
#include <cstring>
#include <algorithm>
const int MAXN = 1e5 + 5;
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int a[MAXN];
int op[MAXN], L[MAXN], R[MAXN];
int n, m;
int Sum[MAXN << 2], tag[MAXN << 2];
void Pushup(int rt)
{
    Sum[rt] = Sum[rt << 1] + Sum[rt << 1 | 1];
}
void build(int l, int r, int rt, int x)
{
    tag[rt] = -1;
    if (l == r) 
    {
        Sum[rt] = a[l] >= x;
        return;
    }
    int m = l + r >> 1;
    build (l, m, rt << 1, x);
    build (m + 1, r, rt << 1 | 1, x);
    Pushup(rt);
}
void Pushdown(int rt, int m)
{
    if (tag[rt] != -1)
    {
        tag[rt << 1] = tag[rt << 1 | 1] = tag[rt];
        Sum[rt << 1] = (m - (m >> 1)) * tag[rt];
        Sum[rt << 1 | 1] = (m >> 1) * tag[rt];
        tag[rt] = -1;
    }
}
void Update(int L, int R, int c, int l, int r, int rt)
{
    if (L > R) return;
    if (L <= l && R >= r)
    {
        Sum[rt] = (r - l + 1) * c;
        tag[rt] = c;
        return;
    }
    Pushdown(rt, r - l + 1);
    int m = l + r >> 1;
    if (L <= m) Update(L, R, c, l, m, rt << 1);
    if (R > m) Update(L, R, c, m + 1, r, rt << 1 | 1);
    Pushup(rt);
}
int Query(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
        return Sum[rt];
    Pushdown(rt, r - l + 1);
    int m = l + r >> 1;
    int ans = 0;
    if (L <= m) ans += Query(L, R, l, m, rt << 1);
    if (R > m) ans += Query(L, R, m + 1, r, rt << 1 | 1);
    return ans;
}
int p;
bool Judge(int mid)
{
    build(1, n, 1, mid);
    for (int i = 1; i <= m; i++)
    {
        int b = Query(L[i], R[i], 1, n, 1);
        if (op[i] == 0)
        {
            Update(L[i], R[i] - b, 0, 1, n, 1);
            Update(R[i] - b + 1, R[i], 1, 1, n, 1);
        }
        else
        {
            Update(L[i], L[i] + b - 1, 1, 1, n, 1);
            Update(L[i] + b, R[i], 0, 1, n, 1);
        }
    }
    return Query(p, p, 1, n, 1);
}
int main()
{
    // freopen ("heoi2016_sort.in", "r", stdin);
    // freopen ("heoi2016_sort.out", "w", stdout);
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    for (int i = 1; i <= m; i++)
        op[i] = read(), L[i] = read(), R[i] = read();
    int l = 1, r = n + 1;
    p = read();
    int ans = 0;
    while (l < r)
    {
        int mid = l + r >> 1;
        if (Judge(mid)) ans = mid, l = mid + 1;
        else r = mid;
    }
    printf ("%d\n", ans);
}