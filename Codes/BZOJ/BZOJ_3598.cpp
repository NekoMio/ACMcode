#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
long long K;
long long f[25][37000];
int a[25];
long long dfs(int now, int Sum, bool top)
{
    if (now == 0) return Sum;
    if (!top && f[now][Sum] != -1) return f[now][Sum];
    int n = top ? a[now]: K - 1;
    long long ans = 0;
    for (int i = 0; i <= n; i++)
        ans += dfs(now - 1, Sum + i * (now - 1), top && (i == n));
    if (!top) f[now][Sum] = ans;
    return ans;
}
long long dfs(int now, int Sum, int num, bool top)
{
    if (Sum < 0) return 0;
    if (!now) return Sum;
    if (!top && f[now][Sum] != -1) return f[now][Sum];
    int n = top ? a[now]: K - 1;
    long long ans = 0;
    for (int i = 0; i <= n; i++)
    {
        if (now >= num) ans += dfs(now - 1, i + Sum, num, top && (i == n));
        else ans += dfs(now - 1, Sum - i, num, top && (i == n));
    }
    if (!top) f[now][Sum] = ans;
    return ans;
}
long long Calc(long long x)
{
    int len = 0;
    while (x) a[++len] = x % K, x /= K;
    memset(f, -1, sizeof(f));
    long long ans = dfs(len, 0, 1);
    for (int i = 2; i <= len; i++) 
    {
        memset (f, -1, sizeof (f));
        ans -= dfs(len, 0, i, 1);
    }
    return ans;
}
int main()
{
    long long L, R; 
    scanf ("%lld%lld%lld", &L, &R, &K);
    printf ("%lld", Calc(R) - Calc(L - 1));
}