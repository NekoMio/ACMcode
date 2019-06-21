#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 100005;
int l[MAXN], Hash[MAXN << 1];
int Max[MAXN << 3], add[MAXN << 3], lazy[MAXN << 3];

void Pushup(int rt)
{
    Max[rt] = max(Max[rt << 1], Max[rt << 1 | 1]);
}
void Pushdown(int rt)
{
    if (add[rt])
    {
        add[rt << 1] += add[rt];
        add[rt << 1 | 1] += add[rt];
        Max[rt << 1] += add[rt];
        Max[rt << 1 | 1] += add[rt];
        if (lazy[rt << 1 | 1] != -1) lazy[rt << 1 | 1] += add[rt];
        if (lazy[rt << 1] != -1) lazy[rt << 1] += add[rt];
        add[rt] = 0;
    }
    if (lazy[rt] != -1)
    {
        add[rt << 1] = add[rt << 1 | 1] = 0;
        Max[rt << 1] = Max[rt << 1 | 1] = lazy[rt];
        lazy[rt << 1] = lazy[rt << 1 | 1] = lazy[rt];
        lazy[rt] = -1;
    }
}
void Build(int l, int r, int rt)
{
    lazy[rt] = -1;
    Max[rt] = 0, add[rt] = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    Build(l, mid, rt << 1);
    Build(mid + 1, r, rt << 1 | 1);
    // Pushup(rt);
}
void Update(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        add[rt] += c;
        Max[rt] += c;
        if (lazy[rt] != -1) lazy[rt] += c;
        return;
    }
    Pushdown(rt);
    int mid = (l + r) >> 1;
    if (L <= mid) Update(L, R, c, l, mid, rt << 1);
    if (R > mid) Update(L, R, c, mid + 1, r, rt << 1 | 1);
    Pushup(rt);
}
void Set(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        add[rt] = 0;
        Max[rt] = c;
        lazy[rt] = c;
        return;
    }
    Pushdown(rt);
    int mid = (l + r) >> 1;
    if (L <= mid) Set(L, R, c, l, mid, rt << 1);
    if (R > mid) Set(L, R, c, mid + 1, r, rt << 1 | 1);
    Pushup(rt);
}
int Query(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
        return Max[rt];
    Pushdown(rt);
    int mid = (l + r) >> 1;
    int ans = 0;
    if (L <= mid) ans = max(ans, Query(L, R, l, mid, rt << 1));
    if (R > mid) ans = max(ans, Query(L, R, mid + 1, r, rt << 1 | 1));
    return ans;
}
struct data
{
    int i, y, k;
    bool operator < (const data &b) const 
    {
        return i == b.i ? y < b.y : i < b.i;
    }
}c[MAXN];
int main()
{
    int T = read();
    while (T--)
    {
        int n = read(), m = read();
        int tot = 0;
        // memset (f, 0, sizeof (f));
        // memset (Max, 0, sizeof (Max));
        for (int i = 2; i <= n; i++) Hash[++tot] = l[i] = read();
        bool tp = 1;
        for (int i = 1; i <= m; i++)
        {
            c[i].i = read(), c[i].y = read() + 1, c[i].k = read();
            if (c[i].k == 0) tp = 0;
            Hash[++tot] = c[i].y;
        }
        if (tp)
        {
            printf ("%d\n", m);
            continue;
        }
        sort(Hash + 1, Hash + tot + 1);
        sort(c + 1, c + m + 1);
        int cnt = unique(Hash + 1, Hash + tot + 1) - Hash - 1;
        l[1] = cnt + 1;
        for (int i = 2; i <= n; i++) l[i] = lower_bound(Hash + 1, Hash + cnt + 1, l[i]) - Hash;
        for (int i = 1; i <= m; i++) c[i].y = lower_bound(Hash + 1, Hash + cnt + 1, c[i].y) - Hash;
        // int now = 0;
        // for (int i = 1; i <= n; i++)
        // {
        //     int s = now + 1;
        //     for (; now < m && c[now + 1].i == i; now++);
        //     int nowcnt = 0;
        //     for (int i = s; i <= now; i++) if (c[i].k == 0) nowcnt++;
        //     for (int k = 0; k <= cnt; k++)
        //     {
        //         if (s <= now && c[s].y <= k)
        //         {
        //             if (c[s].k)
        //                 nowcnt++; 
        //             else
        //                 nowcnt--;
        //             s++;
        //         }
        //         if (k <= l[i]) f[i][k] = Max[i - 1][l[i]] + nowcnt;
        //         else f[i][k] = f[i - 1][k] + nowcnt;
        //         if (k) Max[i][k] = max(Max[i][k - 1], f[i][k]);
        //         else Max[i][k] = f[i][k];
        //     }
        // }
        int now = 0;
        Build(0, cnt, 1);
        l[n + 1] = cnt + 1;
        for (int i = 1; i <= n; i++)
        {
            // int s = now + 1;
            for (; now < m && c[now + 1].i == i; now++)
            {
                if (c[now + 1].k == 0)
                    Update(0, c[now + 1].y - 1, 1, 0, cnt, 1);
                else
                    Update(c[now + 1].y, cnt, 1, 0, cnt, 1);
            }
            Set(0, l[i + 1], Query(0, l[i + 1], 0, cnt, 1), 0, cnt, 1);
        }
        printf ("%d\n", Max[1]);
    }
    // while (1);
}