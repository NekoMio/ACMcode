#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct data
{
    long long l, r;
    bool operator < (const data &a)const 
    {
        return r == a.r ? l < a.l : r < a.r;
    }
}a[200005];
int main()
{
    int n;
    scanf("%d", &n);
    long long c, d;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &c, &d);
        a[i].l = c - d, a[i].r = c + d;
    }
    sort(a + 1, a + n + 1);
    int ans = 0, now = -0x7fffffff;
    for (int i = 1; i <= n; i++)
    {
        if (a[i].l >= now)
        {
            now = a[i].r;
            ans++;
        }
    }
    printf("%d", ans);
}