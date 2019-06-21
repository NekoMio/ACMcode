#include <cstdio>
#include <algorithm>
#include <cstring>
struct data
{
    int a, b;
    bool operator < (const data &c) const 
    {
        return b < c.b;
    }
}d[100005];
int a[2000005], f[2000005];
int main()
{
    int n, m;
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf ("%d%d", &d[i].a, &d[i].b);
    std::sort(d + 1, d + n + 1);
    int now = 0;
    for (int i = 1; i <= n; i++)
    {
        if (d[i].b - d[i - 1].b >= 18)  a[now + 18] += d[i].a, now += 18;
        else a[now + d[i].b - d[i - 1].b] += d[i].a, now += d[i].b - d[i - 1].b;
    }
    memset(f, 0x80, sizeof (f));
    f[0] = 0;
    int ans = 0;
    for (int i = 4; i <= now; i++)
    {
        f[i] = f[i - 4] + a[i];
        if (i >= 7) f[i] = std::max(f[i], f[i - 7] + a[i]);
        ans = std::max(ans, f[i]);
    }
    printf ("%d", ans);
}