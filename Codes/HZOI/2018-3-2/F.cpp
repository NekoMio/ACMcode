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
const int MAXN = 1e5 + 5;
struct data
{
    int Max, LMax, RMax;
    int l, r;
    int rl, lr;
    int ml, mr, mrl, mlr;
    int Sum;
    int Min, LMin, RMin;
    bool flag;
}T[MAXN << 2];
void Pushup(int rt)
{
    T[rt].Sum = T[rt << 1].Sum + T[rt << 1 | 1].Sum;
    // T[rt].Max = max(T[rt << 1].Max, T[rt << 1 | 1].Max);
    if (T[rt << 1].Max > T[rt << 1 | 1].Max)
    {
        T[rt].Max = T[rt << 1].Max;
        T[rt].l = T[rt << 1].l;
        T[rt].r = T[rt << 1].r;
    }
    else
    {
        T[rt].Max = T[rt << 1 | 1].Max;
        T[rt].l = T[rt << 1 | 1].l;
        T[rt].r = T[rt << 1 | 1].r;
    }
    if (T[rt << 1].RMax + T[rt << 1 | 1].LMax > T[rt].Max)
    {
        T[rt].Max = T[rt << 1].RMax + T[rt << 1 | 1].LMax;
        T[rt].l = T[rt << 1].rl;
        T[rt].r = T[rt << 1 | 1].lr;
    }
    // T[rt].Max = max(T[rt << 1].RMax + T[rt << 1].LMax, T[rt].Max);
    if (T[rt << 1].LMax > T[rt << 1].Sum + T[rt << 1 | 1].LMax)
    {
        T[rt].LMax = T[rt << 1].LMax;
        T[rt].lr = T[rt << 1].lr;
    }
    else
    {
        T[rt].LMax = T[rt << 1].Sum + T[rt << 1 | 1].LMax;
        T[rt].lr = T[rt << 1 | 1].lr;
    }
    // T[rt].LMax = max(T[rt << 1].LMax, T[rt << 1].Sum + T[rt << 1 | 1].LMax);
    if (T[rt << 1 | 1].RMax > T[rt << 1].RMax + T[rt << 1 | 1].Sum)
    {
        T[rt].RMax = T[rt << 1 | 1].RMax;
        T[rt].rl = T[rt << 1 | 1].rl;
    }
    else
    {
        T[rt].RMax = T[rt << 1].RMax + T[rt << 1 | 1].Sum;
        T[rt].rl = T[rt << 1].rl;
    }
    // T[rt].RMax = max(T[rt << 1 | 1].RMax, T[rt << 1].RMax + T[rt << 1 | 1].Sum);

    if (T[rt << 1].Min < T[rt << 1 | 1].Min)
    {
        T[rt].Min = T[rt << 1].Min;
        T[rt].ml = T[rt << 1].ml;
        T[rt].mr = T[rt << 1].mr;
    }
    else
    {
        T[rt].Min = T[rt << 1 | 1].Min;
        T[rt].ml = T[rt << 1 | 1].ml;
        T[rt].mr = T[rt << 1 | 1].mr;
    }
    if (T[rt << 1].RMin + T[rt << 1 | 1].LMin < T[rt].Min)
    {
        T[rt].Min = T[rt << 1].RMin + T[rt << 1 | 1].LMin;
        T[rt].ml = T[rt << 1].mrl;
        T[rt].mr = T[rt << 1 | 1].mlr;
    }

    // T[rt].Min = min(T[rt << 1].Min, T[rt << 1 | 1].Min);
    // T[rt].Min = min(T[rt << 1].RMin + T[rt << 1].LMin, T[rt].Min);
    if (T[rt << 1].LMin < T[rt << 1].Sum + T[rt << 1 | 1].LMin)
    {
        T[rt].LMin = T[rt << 1].LMin;
        T[rt].mlr = T[rt << 1].mlr;
    }
    else
    {
        T[rt].LMin = T[rt << 1].Sum + T[rt << 1 | 1].LMin;
        T[rt].mlr = T[rt << 1 | 1].mlr;
    }
    // T[rt].LMin = min(T[rt << 1].LMin, T[rt << 1].Sum + T[rt << 1 | 1].LMin);
    if (T[rt << 1 | 1].RMin < T[rt << 1].RMin + T[rt << 1 | 1].Sum)
    {
        T[rt].RMin = T[rt << 1 | 1].RMin;
        T[rt].mrl = T[rt << 1 | 1].mrl;
    }
    else
    {
        T[rt].RMin = T[rt << 1].RMin + T[rt << 1 | 1].Sum;
        T[rt].mrl = T[rt << 1].mrl;
    }
    // T[rt].RMin = min(T[rt << 1 | 1].RMin, T[rt << 1].RMin + T[rt << 1 | 1].Sum);
}
void Push(int rt)
{
    T[rt].Sum = -T[rt].Sum;
    swap(T[rt].l, T[rt].ml);
    swap(T[rt].r, T[rt].mr);
    swap(T[rt].lr, T[rt].mlr);
    swap(T[rt].rl, T[rt].mrl);
    int tmp = T[rt].Max;
    T[rt].Max = -T[rt].Min;
    T[rt].Min = -tmp;
    tmp = T[rt].LMax;
    T[rt].LMax = -T[rt].LMin;
    T[rt].LMin = -tmp;
    tmp = T[rt].RMax;
    T[rt].RMax = -T[rt].RMin;
    T[rt].RMin = -tmp;
    T[rt].flag ^= 1;
}
void Pushdown(int rt)
{
    if (T[rt].flag)
    {
        Push(rt << 1);
        Push(rt << 1 | 1);
        T[rt].flag = 0;
    }
}
void Update(int x, int c, int l, int r, int rt)
{
    if (l == r)
    {
        T[rt].Sum = c;
        T[rt].Max = T[rt].Min = c;
        T[rt].LMax = T[rt].RMax = c;
        T[rt].LMin = T[rt].RMin = c;
        return;
    }
    Pushdown(rt);
    int mid = l + r >> 1;
    if (x <= mid) Update(x, c, l, mid, rt << 1);
    else Update(x, c, mid + 1, r, rt << 1 | 1);
    Pushup(rt);
}
void flip(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        Push(rt);
        return;
    }
    int mid = l + r >> 1;
    Pushdown(rt);
    if (L <= mid)
        flip(L, R, l, mid, rt << 1);
    if (R > mid)
        flip(L, R, mid + 1, r, rt << 1 | 1);
    Pushup(rt);
}
data Merge(const data &a, const data &b)
{
    data ans;
    ans.Sum = a.Sum + b.Sum;
    // ans.Max = max(a.Max, b.Max);
    if (a.Max > b.Max)
    {
        ans.Max = a.Max;
        ans.l = a.l;
        ans.r = a.r;
    }
    else
    {
        ans.Max = b.Max;
        ans.l = b.l;
        ans.r = b.r;
    }
    if (a.RMax + b.LMax > ans.Max)
    {
        ans.Max = a.RMax + b.LMax;
        ans.l = a.rl;
        ans.r = b.lr;
    }
    // ans.Max = max(a.RMax + a.LMax, ans.Max);
    if (a.LMax > a.Sum + b.LMax)
    {
        ans.LMax = a.LMax;
        ans.lr = a.lr;
    }
    else
    {
        ans.LMax = a.Sum + b.LMax;
        ans.lr = b.lr;
    }
    // ans.LMax = max(a.LMax, a.Sum + b.LMax);
    if (b.RMax > a.RMax + b.Sum)
    {
        ans.RMax = b.RMax;
        ans.rl = b.rl;
    }
    else
    {
        ans.RMax = a.RMax + b.Sum;
        ans.rl = a.rl;
    }
    // ans.RMax = max(b.RMax, a.RMax + b.Sum);

    if (a.Min < b.Min)
    {
        ans.Min = a.Min;
        ans.ml = a.ml;
        ans.mr = a.mr;
    }
    else
    {
        ans.Min = b.Min;
        ans.ml = b.ml;
        ans.mr = b.mr;
    }
    if (a.RMin + b.LMin < ans.Min)
    {
        ans.Min = a.RMin + b.LMin;
        ans.ml = a.mrl;
        ans.mr = b.mlr;
    }

    // ans.Min = min(a.Min, b.Min);
    // ans.Min = min(a.RMin + a.LMin, ans.Min);
    if (a.LMin < a.Sum + b.LMin)
    {
        ans.LMin = a.LMin;
        ans.mlr = a.mlr;
    }
    else
    {
        ans.LMin = a.Sum + b.LMin;
        ans.mlr = b.mlr;
    }
    // ans.LMin = min(a.LMin, a.Sum + b.LMin);
    if (b.RMin < a.RMin + b.Sum)
    {
        ans.RMin = b.RMin;
        ans.mrl = b.mrl;
    }
    else
    {
        ans.RMin = a.RMin + b.Sum;
        ans.mrl = a.mrl;
    }
    // ans.Sum = a.Sum + b.Sum;
    // ans.Max = max(a.Max, b.Max);
    // ans.Max = max(ans.Max, a.RMax + b.LMax);
    // ans.LMax = max(a.LMax, a.Sum + b.LMax);
    // ans.RMax = max(a.RMax + b.Sum, b.RMax);

    // ans.Min = min(a.Min, b.Min);
    // ans.Min = min(ans.Min, a.RMin + b.LMin);
    // ans.LMin = min(a.LMin, a.Sum + b.LMin);
    // ans.RMin = min(a.RMin + b.Sum, b.RMin);
    return ans;
}
data Query(int L, int R, int l, int r, int rt)
{
    if (L == l && R == r)
        return T[rt];
    int mid = l + r >> 1;
    Pushdown(rt);
    if (R <= mid) return Query(L, R, l, mid, rt << 1);
    if (L > mid) return Query(L, R, mid + 1, r, rt << 1 | 1);
    return Merge(Query(L, mid, l, mid, rt << 1), Query(mid + 1, R, mid + 1, r, rt << 1 | 1));
}
int a[MAXN];
void Build(int l, int r, int rt)
{
    if (l == r)
    {
        T[rt].Sum = a[l];
        T[rt].l = l, T[rt].r = l;
        T[rt].lr = l, T[rt].rl = l;
        T[rt].mlr = l, T[rt].mrl = l;
        T[rt].ml = l, T[rt].mr = l; 
        T[rt].Max = T[rt].Min = a[l];
        T[rt].LMax = T[rt].RMax = a[l];
        T[rt].LMin = T[rt].RMin = a[l];
        return;
    }
    int mid = l + r >> 1;
    Build(l, mid, rt << 1);
    Build(mid + 1, r, rt << 1 | 1);
    Pushup(rt);
}
int stl[MAXN], str[MAXN];
int top;
signed main()
{
    int n = read(), m = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    Build(1, n, 1);
    while (m--)
    {
        int opt = read();
        if (opt == 1)
        {
            int l = read(), r = read(), k = read();
            int Sum = 0, ans = 0;
            top = 0;
            while (k--)
            {
                data tmp = Query(l, r, 1, n, 1);
                Sum += tmp.Max;
                flip(tmp.l, tmp.r, 1, n, 1);
                stl[++top] = tmp.l;
                str[top] = tmp.r;
                ans = max(ans, Sum);
            }
            for (int i = 1; i <= top; i++)
                flip(stl[i], str[i], 1, n, 1);
            printf ("%d\n", ans);
        }
        else
        {
            int a = read();
            Update(a, read(), 1, n, 1);
        }
    }
}