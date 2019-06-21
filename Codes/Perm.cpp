#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int MOD;
long long f[1000005];
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
long long C(int n, int m)
{
    if (m > n)
        return 0;
    return f[n] * pow_mod(f[m] * f[n - m] % MOD, MOD - 2) % MOD;
}
int n;
int size[1000005];
long long ans = 1;
void DFS(int x)
{
    if (x > n)
        return;
    size[x] = 1;
    DFS(x << 1 | 1)
    , DFS(x << 1);
    if ((x << 1) <= n)
        size[x] += size[x << 1];
    if ((x << 1 | 1) <= n)
        size[x] += size[x << 1 | 1];
}
void dfs(int x)
{
    if (x > n)
        return;
    if ((x << 1) > n || (x << 1 | 1) > n)
        return;
    ans = ans * C(size[x] - 1, size[x << 1]) % MOD;
    dfs(x << 1);
    dfs(x << 1 | 1);
}
int main()
{
    scanf("%d%d", &n, &MOD);
    f[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        int x = i;
        if (x % MOD == 0)
            x /= MOD;
        f[i] = f[i - 1] * x % MOD;
    }
    DFS(1);
    dfs(1);
    printf("%lld", ans);
}