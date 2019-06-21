#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 100005;
const int M = 200005;
struct data
{
    int s, c, m, pos, num, ans;
    bool operator < (const data &a) const
    {
        if (s == a.s && c == a.c) return m < a.m;
        if (s == a.s) return c < a.c;
        return s < a.s; 
    }
}a[N], b[N];
const bool cmp(const data &a, const data &b)
{
    if (a.c == b.c) a.m < b.m;
    return a.c < b.c;
}
int Sum[M], cnt, Color[M], C;
#define lowbit(_) ((_) & (-_))
void add(int x, int c)
{
    for (int i = x; i <= M; i += lowbit(i))
    {
        if (Color[i] != C) Sum[i] = 0;
        Color[i] = C;
        Sum[i] += c;
    }
}
int Query(int x)
{
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
    {
        if (Color[i] == C)
            ans += Sum[i];
    }
    return ans;
}
void CDQ(int l, int r)
{
    if (l == r) return;
    int mid = l + r >> 1;
    CDQ(l, mid), CDQ(mid + 1, r);
    sort(b + l, b + mid + 1, cmp);
    sort(b + mid + 1, b + r + 1, cmp);
    C++;
    for (int j = mid + 1, i = l; j <= r; j++)
    {
        for (; b[i].c <= b[j].c && i <= mid; i++)
            add(b[i].m, b[i].num);
        b[j].ans += Query(b[j].m);
    }
}
int main()
{
    int n, k;
    scanf ("%d%d", &n, &k);
    for (int i = 1; i <= n; i++){
        scanf ("%d%d%d", &a[i].s, &a[i].c, &a[i].m);
        a[i].pos = i;
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++)
    {
        if (a[i].c == a[i - 1].c && a[i].s == a[i - 1].s && a[i].m == a[i - 1].m)
            b[cnt].num++;
        else
            b[++cnt] = a[i], b[cnt].num = 1;
    }
    // for (int i = 1; i <= cnt; i++) printf ("%d%c", b[i].pos, " \n"[i == cnt]);
    CDQ(1, cnt);
    // for (int i = 1; i <= cnt; i++) printf ("%d%c", b[i].ans, " \n"[i == cnt]);
    // while(1);
    static int Ans[N];
    for (int i = 1; i <= cnt; i++) Ans[b[i].ans + b[i].num - 1] += b[i].num;
    for (int i = 0; i < n; i++) printf ("%d\n", Ans[i]);
    // while (1);
}
