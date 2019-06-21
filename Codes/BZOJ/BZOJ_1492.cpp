#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int N = 1e5 + 5;

struct data
{
    double a, b, r, k, x, y;
    int id;
    bool operator < (const data &c) const 
    {
        return k > c.k;
    }
}a[N], t[N];

const double eps = 1e-9;

double ans, f[N];

double K(int _, int __)
{
    if (__ == 0) return -1e20;
    if (fabs(a[_].x - a[__].x) <= eps) return 1e20;
    return (a[__].y - a[_].y) / (a[__].x - a[_].x);
}

int st[N], top;

void CDQ(int l, int r)
{
    if (l == r)
    {
        f[l] = max(f[l], f[l - 1]);
        a[l].y = f[l] / (a[l].a * a[l].r + a[l].b);
        a[l].x = a[l].r * a[l].y;
        return;
    }
    int l1, l2, mid = l + r >> 1;
    l1 = l; l2 = mid + 1;
    for (int i = l; i <= r; i++)
        if (a[i].id <= mid) t[l1++] = a[i];
        else t[l2++] = a[i];
    for (int i = l; i <= r; i++) a[i] = t[i];
    CDQ(l, mid);
    int top = 0;
    for (int i = l; i <= mid; i++)
    {
        while (top && K(st[top - 1], st[top]) < K(st[top - 1], i) + eps) top--;
        st[++top] = i;
    }
    st[++top] = 0;
    int p = 1;
    for (int i = mid + 1; i <= r; i++)
    {
        while (p < top && K(st[p], st[p + 1]) + eps > a[i].k) p++;
        f[a[i].id] = max(f[a[i].id], a[st[p]].x * a[i].a + a[st[p]].y * a[i].b);
    }
    CDQ(mid + 1, r);
    l1 = l; l2 = mid + 1;
    for (int i = l; i <= r; i++)
        if (((a[l1].x < a[l2].x || (fabs(a[l1].x - a[l2].x) < eps && a[l1].y < a[l2].y)) || l2 > r) && l1 <= mid) t[i] = a[l1++];
        else t[i] = a[l2++];
    for (int i = l; i <= r; i++)
        a[i] = t[i];
}

int main()
{
    // freopen ("cash.in", "r", stdin);
    // freopen ("cash.out", "w", stdout);
    int n, s;
    scanf ("%d%d", &n, &s);
    f[0] = s;
    for (int i = 1; i <= n; i++)
        scanf ("%lf%lf%lf", &a[i].a, &a[i].b, &a[i].r), a[i].id = i, a[i].k = -a[i].a / a[i].b;
    sort(a + 1, a + n + 1);
    CDQ(1, n);
    printf ("%.3f", f[n]);
}