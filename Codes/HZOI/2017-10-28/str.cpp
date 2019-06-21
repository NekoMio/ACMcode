#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1e7 + 5;
const int MOD = 1e9 + 7;
long long F[MAXN];
long long pow_mod(long long a, long long b)
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
long long C(long long n, long long m)
{
    if (n < m) return 0;
    return F[n] * pow_mod(F[m] * F[n - m] % MOD, MOD - 2) % MOD;
}
int main()
{
    freopen("str.in", "r", stdin);
    freopen("str.out", "w", stdout);
    int n;
    scanf ("%d", &n);
    int k = 0;
    F[0] = 1;
    for (int i = 1; i <= MAXN - 3; i++)
        F[i] = F[i - 1] * i % MOD;
    while ((1ll << k) <= n) k++; 
    k--;
    long long Ans = C(1 << k, (1 << (k + 1)) - n) * F[n] % MOD;    
    printf ("%lld", Ans);
    fclose(stdin), fclose(stdout);
    // while (1);
}