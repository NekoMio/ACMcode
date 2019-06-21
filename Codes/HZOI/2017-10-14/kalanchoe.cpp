#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
const int N = 1e6;
int MOD;
int prime[N], Mini[N + 5];
bool isnprime[N + 5];
int tot;
void Get_prime()
{
    isnprime[1] = 1;
    for (int i = 2; i <= N; i++)
    {
        if (!isnprime[i]) prime[++tot] = i, Mini[i] = tot;
        for (int j = 1; j <= tot; j++)
        {
            if (prime[j] * i > N) break;
            isnprime[i * prime[j]] = 1;
            Mini[i * prime[j]] = j;
            if (i % prime[j] == 0) break;
        }
    }
}
int size[N];
void add(int x, int c)
{
    while (Mini[x])
    {
        size[Mini[x]] += c;
        x /= prime[Mini[x]];
    }
}
int C[5005];
int Get_C()
{
    int ans = 1;
    for (int i = 1; i <= tot; i++)
    {
        if (size[i])
        {
            for (int j = 1; j <= size[i]; j++)
            {
                ans = (ans * prime[i]) % MOD;
            }
        }
    }
    return ans;
}
int g[5005][5005];
int f[2][5005];
int a[N];
signed main()
{
    int n, m;
    scanf ("%lld%lld%lld", &n, &m, &MOD);
    for (int i = 1; i <= n; i++) 
        scanf ("%lld", &a[i]);
    g[1][1] = 1;
    Get_prime();
    for (int i = 2; i <= 5000; i++)
    {
        for (int j = 2; j <= 5000; j++)
            g[i][j] = (g[i - 1][j - 1] * j % MOD + g[i - 1][j] * (j - 1) % MOD) % MOD;
    }
    for (int i = 1; i <= 5000 && i <= m; i++)
        add(m - i + 1, 1), add(i, -1), C[i] = Get_C();
    f[0][0] = 1;
    int now = 1;
    for (int i = 1; i <= n; i++, now ^= 1)
    {
        if (a[i] == 1)
        {
            f[now][1] = f[now ^ 1][0] * m % MOD;
            if (a[i - 1] == 1) f[now][1] = (f[now][1] - f[now ^ 1][1] + MOD) % MOD;
            f[now][0] = f[now][1];
        }
        else
        {
            f[now][0] = 0;
            for (int j = 2; j <= a[i] && j <= m; j++)
            {
                f[now][j] = (f[now ^ 1][0] * g[a[i]][j] % MOD) * C[j] % MOD;
                if (a[i - 1] >= j) f[now][j] = (f[now][j] - f[now ^ 1][j] * g[a[i]][j] % MOD + MOD) % MOD;
                (f[now][0] += f[now][j]) %= MOD;
            }
        }
    }
    printf ("%lld", f[now^1][0]);
}