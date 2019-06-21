#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int pos[5005], link[5005];
struct data
{
    int x, y, z, s;
}a[5005];
bool cmpx(const data &b, const data &c)
{
    return b.x < c.x;
}
bool cmpz(const data &b, const data &c)
{
    return b.z > c.z;
}
bool check(int k, int x)
{
    if(pos[x] > a[k].y) return 0;
    if(!link[x])
    {
        link[x] = k;
        return 1;
    }
    else
    {
        if (a[link[x]].y < a[k].y) return check(k, x + 1);
        else if (check(link[x], x + 1))
        {
            link[x] = k;
            return 1;
        }
        else return 0;
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
    sort(a + 1, a + n + 1, cmpx);
    for (int i = 1; i <= n; i++) pos[i] = max(pos[i - 1] + 1, a[i].x);
    a[1].s = 1;
    for (int i = 2; i <= n; i++)
    {
        a[i].s = a[i - 1].s;
        while (pos[a[i].s] < a[i].x && a[i].s < n) a[i].s++;
    }
    sort(a + 1, a + n + 1, cmpz);
    long long ans = 0;
    for (int i = 1; i <= n; i++) if(check(i, a[i].s)) ans += a[i].z;
    printf("%lld\n", ans);
}