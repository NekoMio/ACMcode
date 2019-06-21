#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MOD = 100000007;
int phi[2005], prime[2005], cnt;
bool isnprime[2005];
void Get_phi()
{
    isnprime[1] = 1;
    for (int i = 2; i <= 2000; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > 2000) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
    phi[1] = 1;
}
long long DP[2005][2005];
int n, k;
long long Calc(int x)
{
    int m = min(x, k);
    long long ans = 0;
    for (int i = 0; i <= m; i++)
    {
        if (i != x) ans = (ans + DP[x - i - 1][0] * (i + 1) % MOD) % MOD;
        if (i == x && n <= k) ans = (ans + 1) % MOD;
    }
    return ans;
}
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
int main()
{
    Get_phi();
    int T = read();
    while (T--)
    {
        n = read(), k = read();
        memset (DP, 0, sizeof (DP));
        DP[0][0] = 1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= k; j++)
            {
                if (j < k) (DP[i + 1][j + 1] += DP[i][j]) %= MOD;
                (DP[i + 1][0] += DP[i][j]) %= MOD;
            }
        long long ans = 0;
        for (int i = 1; i * i <= n; i++)
            if (n % i == 0)
            {
                ans = (ans + Calc(i) * phi[n / i] % MOD) % MOD;
                if (i * i != n) ans = (ans + Calc(n / i) * phi[i] % MOD) % MOD;
            }
        printf ("%d\n", ans * pow_mod(n, MOD - 2) % MOD);
    }
}