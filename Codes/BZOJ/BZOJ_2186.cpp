#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
bool isnprime[10000005];
long long Inv[10000005], F[10000005];
long long A[10000005];
int prime[2000005], MOD, Idx;
void Get_Prime()
{
    isnprime[1] = 1;
    for (int i = 2; i <= 10000000; i++)
    {
        if (!isnprime[i])
        {
            prime[++Idx] = i;
        }
        for (int j = 1; j <= Idx; j++)
        {
            if (prime[j] * i > 10000000)
                break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}
int main()
{
    Get_Prime();
    int T;
    scanf("%d%d", &T, &MOD);
    Inv[1] = 1;
    for (int i = 2; i <= 10000000; i++)
        Inv[i] = (MOD - MOD / i) * Inv[MOD % i] % MOD;

    F[0] = 1;
    for (int i = 1; i <= 10000000; i++)
        F[i] = F[i - 1] * i % MOD;

    long long now = 1;
    for (int i = 0; i <= Idx; i++)
    {
        now = (MOD + 1 - Inv[prime[i]]) * now % MOD;
        for (int j = prime[i]; j < prime[i + 1] && j <= 10000000; j++)
            A[j] = now;
    }
    
    while (T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        long long ans = F[n] * A[m] % MOD;
        printf("%lld\n", ans);
    }
}