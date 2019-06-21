#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100000;
#define int long long
struct data
{
    int a, t, id;
    bool operator < (const data &b) const {
        if (b.t == t) return a > b.a;
        return t > b.t;
    }
}a[MAXN + 5];

int cmp1(const data &a, const data &b)
{
    return a.id < b.id;
}

int cmp2(const data &a, const data &b)
{
    if (b.t == a.t) return a.a < b.a;
    return a.t > b.t;
}

#define lowbit(_) ((_) & (-_))
int Sum[MAXN + 5], Color[MAXN + 5], C;
void Update(int x, int c)
{
    for (int i = x; i <= MAXN; i += lowbit(i))
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
int ans[MAXN + 5];
int Ans = 0;
void CDQ(int l, int r)
{
    if (l == r) return;
    int mid = l + r >> 1;
    CDQ(l, mid), CDQ(mid + 1, r);
    sort(a + l, a + mid + 1);
    sort(a + mid + 1, a + r + 1);
    C++;
    for (int j = mid + 1, i = l; j <= r; j++)
    {
        for (; a[i].t >= a[j].t && i <= mid; i++)
            Update(a[i].a, 1);
        ans[a[j].t] += Query(MAXN) - Query(a[j].a);
    }
}
void CDQ2(int l, int r)
{
    if (l == r) return;
    int mid = l + r >> 1;
    CDQ2(l, mid), CDQ2(mid + 1, r);
    sort(a + l, a + mid + 1, cmp2);
    sort(a + mid + 1, a + r + 1, cmp2);
    C++;
    for (int j = mid + 1, i = l; j <= r; j++)
    {
        for (; a[i].t > a[j].t && i <= mid; i++)
            Update(a[i].a, 1);
        ans[a[j].t] += Query(a[j].a - 1);
    }
}
int pos[MAXN];
signed main()
{
    // freopen("inverse.in", "r", stdin);
    // freopen("inverse.out", "w", stdout);
    int n, m;
    scanf ("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf ("%d", &a[i].a), a[i].id = n - i + 1, pos[a[i].a] = i;
    int id;
    for (int i = 1; i <= m; i++)
    {
        scanf ("%lld", &id);
        a[pos[id]].t = i;
    }
    for (int i = 1; i <= n; i++)
        if (!a[i].t)
            a[i].t = m + 1;
    CDQ(1, n);
    sort(a + 1, a + n + 1, cmp1);
    CDQ2(1, n);
    for (int i = m; i >= 1; i--) ans[i] += ans[i + 1];
    for (int i = 1; i <= m; i++) printf ("%lld\n", ans[i]);
    // while (1);
}