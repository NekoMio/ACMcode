#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <set>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='0')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 5e4 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
struct data
{
    int h, key, id;
    bool operator < (const data &b) const
    {
        return key == b.key ? h < b.h : key < b.key;
    }
    bool operator > (const data &b) const 
    {
        return h == b.h ? key < b.key : h > b.h;
    }
}a[MAXN], b[MAXN];
int Min[MAXN << 2], flag[MAXN << 2];
set<data> st;
void Pushup(int rt)
{
    Min[rt] = min(Min[rt << 1], Min[rt << 1 | 1]);
}
void Build(int l, int r, int rt)
{
    if (l == r)
    {
        Min[rt] = a[l].key;
        return;
    }
    int mid = l + r >> 1;
    Build(l, mid, rt << 1);
    Build(mid + 1, r, rt << 1 | 1);
    Pushup(rt);
}
void Pushdown(int rt)
{
    if (flag[rt])
    {
        Min[rt << 1] += flag[rt];
        Min[rt << 1 | 1] += flag[rt];
        flag[rt << 1 | 1] += flag[rt];
        flag[rt << 1] += flag[rt];
        flag[rt] = 0;
    }
}
void Update(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        Min[rt] += c;
        flag[rt] += c;
        return;
    }
    Pushdown(rt);
    int mid = l + r >> 1;
    if (L <= mid) Update(L, R, c, l, mid, rt << 1);
    if (R > mid) Update(L, R, c, mid + 1, r, rt << 1 | 1);
    Pushup(rt);
}
void Set(int x, int l, int r, int rt)
{
    if (l == r)
    {
        Min[rt] = INF;
        return;
    }
    Pushdown(rt);
    int mid = l + r >> 1;
    if (x <= mid) Set(x, l, mid, rt << 1);
    else Set(x, mid + 1, r, rt << 1 | 1);
    Pushup(rt);
}
int n;
void Query(int l, int r)
{
    int rt = 1;
    while (l != r)
    {
        Pushdown(rt);
        int mid = l + r >> 1;
        if (Min[rt << 1] == 1) r = mid, rt = rt << 1;
        else l = mid + 1, rt = rt << 1 | 1;
    }
    printf ("%d %d\n", a[l].key, a[l].h);
    Update(1, l, -1, 1, n, 1);
    Set(l, 1, n, 1);
    st.erase(a[l]);
}
int main()
{
    n = read();
    long long ans = 1;
    for (int i = 1; i <= n; i++)
        a[i].h = read(), a[i].key = read();
    sort(a + 1, a + n + 1, [](const data &a, const data &b) {return a > b;});
    int cnt = 0, pos = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i].h == a[i - 1].h) cnt++;
        else cnt = 0, pos = i;
        ans = ans * (min(a[i].key, pos) + cnt) % MOD;
    }
    printf ("%d\n", ans);
    reverse(a + 1, a + n + 1);
    // memcpy(b, a, sizeof (b));
    sort(a + 1, a + n + 1, [](const data &a, const data &b) -> bool {return a.h == b.h ? a.key < b.key : a.h < b.h;});
    for (int i = 1; i <= n; i++)
    {
        a[i].id = i;
        st.insert(a[i]);
    }
    Build(1, n, 1);
    for (int i = 1; i <= n; i++)
    {
        if (Min[1] > 1)
        {
            data x = *st.begin();
            st.erase(x);
            printf ("%d %d\n", x.key, x.h);
            Update(1, x.id, -1, 1, n, 1);
            Set(x.id, 1, n, 1);
        }
        else Query(1, n);
    }
    // while (1);
}