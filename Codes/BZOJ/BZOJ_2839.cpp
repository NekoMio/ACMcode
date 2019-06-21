#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
const int MOD = 1e9 + 7;
int f[1000005];
int Inv[1000005];
int pow_mod(int a, int b)
{
    int ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
int C(int n, int m)
{
    if (n < m) return 0;
    return f[n] * Inv[m] % MOD * Inv[n - m] % MOD;
}
signed main()
{
    int n, k;
    f[0] = 1;
    for (int i = 1; i <= 1000000; i++)
        f[i] = f[i - 1] * i % MOD;
    Inv[1000000] = pow_mod(f[1000000], MOD - 2) % MOD;
    for (int i = 1000000 - 1; i >= 0; i--)
        Inv[i] = Inv[i + 1] * (i + 1) % MOD; 
    scanf ("%lld%lld", &n, &k);
    int Ans = C(n, k);
    int Sum = 0;
    int m = n - k;
    int tmp = 2;
    for (int i = m; i >= 0; i--)
    {
        if (i & 1)
            Sum = (Sum - C(m, i) * tmp % MOD + MOD) % MOD;
        else
            Sum = (Sum + C(m, i) * tmp % MOD + MOD) % MOD;
        tmp = tmp * tmp % MOD;
    }
    Ans = Ans * Sum % MOD;
    printf ("%lld", Ans);
}