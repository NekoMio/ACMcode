#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct point
{
    long long x, y, ID;
    bool operator < (const point &a) const
    {
        return x < a.x;
    }
}a[100005];
bool cmp(const point a, const point b)
{
    return a.y < b.y;
}
long long Lx[100005], Rx[100005], Ly[100005], Ry[100005];
long long dis(int i, int j)
{
    return abs(a[i].x - a[j].x) + abs(a[i].y - a[j].y);
}
int main()
{
    int n;
    scanf ("%d", &n);
    int x, y;
    for (int i = 1; i <= n; i++)
    {
        scanf ("%d%d", &x, &y);
        a[i].x = x + y;
        a[i].y = x - y;
        a[i].ID = i;
    }
    sort(a + 1, a + n + 1);
    long long S = 0;
    for (int i = 1; i <= n; i++)
        S += a[i].x, Lx[a[i].ID] = abs(S - a[i].x * i);
    S = 0;
    for (int i = n; i >= 1; i--)
        S += a[i].x, Rx[a[i].ID] = abs(S - a[i].x * (n - i + 1));
    S = 0;
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++) 
        S += a[i].y, Ly[a[i].ID] = abs(S - a[i].y * i);
    S = 0;
    for(int i = n; i >= 1; i--)
        S += a[i].y, Ry[a[i].ID] = abs(S - a[i].y * (n - i + 1));
    long long ans = 0x3f3f3f3f3f3f3f3f;
    for (int i = 1; i <= n; i++)
        ans = min(ans, Lx[i] + Ly[i] + Rx[i] + Ry[i]);
    printf ("%lld", ans / 2);
}