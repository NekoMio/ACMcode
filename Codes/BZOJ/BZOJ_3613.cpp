#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int MOD, Sa, Sb, Sc, Sd;
long long F(long long x)
{
    long long ans = 0;
    ans += ((Sa * x % MOD) * x % MOD) * x % MOD;
    (ans += (Sb * x % MOD) * x % MOD) %= MOD;
    (ans += Sc * x % MOD) %= MOD;
    (ans += Sd) %= MOD;
    return ans;
}
int A[5000005];
int main()
{
    int n;
    scanf("%d%d%d%d%d%d%d", &n, &Sa, &Sb, &Sc, &Sd, &A[1], &MOD);
    int Max = A[1], ans = 0;
    for (int i = 2; i <= n; i++)
    {
        A[i] = (F(A[i - 1]) + F(A[i - 2])) % MOD;
        ans = max(ans, (Max - A[i] + 1) >> 1);
        Max = max(Max, A[i]);
    }
    printf("%d", ans);
}