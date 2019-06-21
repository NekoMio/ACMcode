#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1e9 + 7;
struct data
{
    int l, r;
    bool operator < (const data &a) const 
    {
        return l == a.l ? r < a.r : l < a.l;
    }
}a[2005];
long long f[2050][4050];
// 这一个是 i 上一个是 j 方案数
int st[4005];
int main()
{
    int n;
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf ("%d%d", &a[i].l, &a[i].r);
    sort(a + 1, a + n + 1);
    for (int i = 1, j = 1; i <= 4000; st[i++] = j)
        while (j <= n && a[j].l <= i)
            j++;
    for (int i = 1; i <= 4000; i++)
        f[n + 1][i] = 1;
    for (int i = n; i > 0; i--)
    {
        for (int j = 4000; j >= 0; j--)
        {
            f[i][j] = f[i + 1][j];
            if (a[i].l <= j)
            {
                int p = a[i].r, q = j;
                if (p > q)
                    swap(p, q);
                (f[i][j] += f[st[p]][q]) %= MOD;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        (ans += f[i + 1][a[i].r]) %= MOD;
    printf ("%d", ans);
    // while (1);
}