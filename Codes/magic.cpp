#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
int size;
bool comp(int a, int b)
{
    return a > b;
}
int r[1010], l[1010];
int a[1000005];
int b[1000005], belong[1000005];
int add[1005];
void rebuild(int x)
{
    for (int i = l[x]; i <= r[x]; i++)
        b[i] = a[i];
    sort(b + l[x], b + r[x] + 1, comp);
}
int solve(int L, int R, int c)
{
    int l = L, r = R, ans = R + 1;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (b[mid] < c)
            l = mid + 1;
        else
            ans = mid, r = mid - 1;
    }
    return R - ans + 1;
}
int main()
{
    int n, Q;
    scanf("%d%d", &n, &Q);
    size = sqrt(n);
    int tot = (n - 1) / size + 1;
    for (int i = 1; i <= n; i++)
    {
        if (!l[(i - 1) / size + 1])
            l[(i - 1) / size + 1] = i;
        r[(i - 1) / size + 1] = i;
        belong[i] = (i - 1) / size + 1;
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
        b[i] = a[i];
    }
    for (int i = 1; i <= tot; i++)
        sort(b + l[i], b + r[i] + 1, comp);
    char c[10];
    int s, e, m;
    while (Q--)
    {
        scanf("%s", c);
        scanf("%d%d%d", &s, &e, &m);
        if (c[0] == 'A')
        {
            int ans = 0;
            if (belong[s] == belong[e])
            {
                for (int i = s; i <= e; i++)
                    if (b[i] + add[belong[i]] >= m)
                        ans++;
                printf("%d\n", ans);
            }
            else
            {
                for (int i = belong[s] + 1; i <= belong[e] - 1; i++)
                    ans += upper_bound(b + l[i], b + r[i] + 1, m - add[i], comp) - (b + l[i]);
                for (int i = s; i <= r[belong[s]]; i++)
                    if (b[i] + add[belong[i]] >= m)
                        ans++;
                for (int i = l[belong[e]]; i <= e; i++)
                    if (b[i] + add[belong[i]] >= m)
                        ans++;
                printf("%d\n", ans);
            }
        }
        else
        {
            if (belong[s] == belong[e])
            {
                for (int i = s; i <= e; i++)
                    a[i] += m;
                rebuild(belong[s]);
            }
            else
            {
                for (int i = belong[s] + 1; i <= belong[e] - 1; i++)
                    add[i] += m;
                for (int i = s; i <= r[belong[s]]; i++)
                    a[i] += m;
                rebuild(belong[s]);
                for (int i = l[belong[e]]; i <= e; i++)
                    a[i] += m;
                rebuild(belong[e]);
            }
        }
    }
}