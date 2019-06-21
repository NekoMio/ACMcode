/*
 * @Author: WildRage 
 * @Date: 2017-08-06 17:57:21 
 * @Last Modified by: WildRage
 * @Last Modified time: 2017-08-06 18:07:40
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
struct data
{
    int h, w;
} a[2005], b[2005];
int n, A, B, C, m;
int comp(const data &a, const data &b)
{
    return a.h < b.h;
}
int cmp(const data &a, const data &b)
{
    return a.w < b.w;
}
int c[2005];
int lowbit(int x)
{
    return x & (-x);
}
void add(int x, int w)
{
    for (int i = x; i <= m; i += lowbit(i))
        c[i] += w;
}
int sum(int x)
{
    int s = 0;
    for (int i = x; i; i -= lowbit(i))
        s += c[i];
    return s;
}
int ans = 0;
void solve(int from)
{
    int h_min = a[from].h, w_min;
    int all;
    memcpy(b, a, sizeof(b));
    memset(c, 0, sizeof(c));
    sort(b + from, b + n + 1, cmp);
    int Sum[2005], Hash[2005];
    for (int i = from; i <= n; i++)
        Hash[i] = Sum[i] = b[i].h * A + b[i].w * B;
    sort(Hash + from, Hash + n + 1);
    m = unique(Hash + from, Hash + n + 1) - Hash - 1;
    for (int i = from; i <= n; i++)
    {
        int x = upper_bound(Hash + from, Hash + m + 1, Sum[i]) - Hash - 1;
        add(x, 1);
    }
    for (int i = from; i <= n; i++)
    {
        w_min = b[i].w;
        all = C + A * h_min + B * w_min;
        int x = upper_bound(Hash + from, Hash + m + 1, all) - Hash - 1;
        ans = max(ans, sum(x));
        add(upper_bound(Hash + from, Hash + m + 1, Sum[i]) - Hash - 1, -1);
    }
}
int main()
{
    //freopen("beauty.in", "r", stdin);
    //freopen("beauty.out", "w", stdout);
    scanf("%d", &n);
    scanf("%d%d%d", &A, &B, &C);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &a[i].h, &a[i].w);
    }
    sort(a + 1, a + n + 1, comp);
    for (int i = 1; i <= n; i++)
        solve(i);
    printf("%d", ans);
}
