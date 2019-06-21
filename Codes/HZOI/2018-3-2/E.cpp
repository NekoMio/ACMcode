#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1000000007;
const int Inv2 = 500000004;
const int Inv6 = 166666668;
const int Inv24 = 41666667;
long long F[505];
int main()
{
    int n;
    scanf ("%d", &n);
    F[0] = F[1] = 1;
    for (int i = 2; i <= n / 2; i++)
        for (int j = 0; j <= i; j++)
            for (int k = 0; k <= j; k++)
                if (k + j < i)
                {
                    int l = i - k - j - 1;
                    if (l < j) break;
                    if (k == l) F[i] = (F[i] + (F[l] + F[l] * (F[l] - 1) % MOD + F[l] * (F[l] - 1) % MOD * (F[l] - 2) % MOD * Inv6 % MOD) % MOD) % MOD;
                    else if (k == j) F[i] = (F[i] + F[l] * ((F[j] + F[j] * (F[j] - 1) % MOD * Inv2 % MOD) % MOD) % MOD) % MOD;
                    else if (j == l) F[i] = (F[i] + F[k] * ((F[j] + F[j] * (F[j] - 1) % MOD * Inv2 % MOD) % MOD) % MOD) % MOD;
                    else F[i] = (F[i] + F[l] * F[k] % MOD * F[j] % MOD) % MOD;
                }
    long long ans = 0;
    for (int i = 0; i <= (n - 1) / 2; i++)
        for (int j = 0; j <= i; j++)
            for (int k = 0; k <= j; k++)
            {
                int l = n - i - j - k - 1;
                if (l < i || l > (n - 1) / 2) continue;
                if (k == l) ans = (ans + F[l] + F[l] * (F[l] - 1) % MOD * (F[l] - 2) % MOD * Inv2 % MOD + F[l] * (F[l] - 1) % MOD * 3 % MOD * Inv2 % MOD + F[l] * (F[l] - 1) % MOD * (F[l] - 2) % MOD * (F[l] - 3) % MOD * Inv24 % MOD) % MOD;
                else if (k == i) ans = (ans + F[l] * (F[i] + F[i] * (F[i] - 1) % MOD + F[i] * (F[i] - 1) % MOD * (F[i] - 2) % MOD * Inv6 % MOD) % MOD) % MOD;
                else if (j == l) ans = (ans + F[k] * (F[i] + F[i] * (F[i] - 1) % MOD + F[i] * (F[i] - 1) % MOD * (F[i] - 2) % MOD * Inv6 % MOD) % MOD) % MOD;
                else if (k == j && i == l) ans = (ans + (F[k] + F[k] * (F[k] - 1) % MOD * Inv2 % MOD) % MOD * ((F[i] + F[i] * (F[i] - 1) % MOD * Inv2 % MOD) % MOD) % MOD) % MOD;
                else if (k == j) ans = (ans + F[i] * F[l] % MOD * ((F[k] + F[k] * (F[k] - 1) % MOD * Inv2 % MOD) % MOD) % MOD) % MOD;
                else if (j == i) ans = (ans + F[k] * F[l] % MOD * ((F[j] + F[j] * (F[j] - 1) % MOD * Inv2 % MOD) % MOD) % MOD) % MOD;
                else if (i == l) ans = (ans + F[k] * F[j] % MOD * ((F[i] + F[i] * (F[i] - 1) % MOD * Inv2 % MOD) % MOD) % MOD) % MOD;
                else ans = (ans + F[k] * F[j] % MOD * F[i] % MOD * F[l] % MOD) % MOD;
            }
    if (!(n & 1)) ans = (ans + F[n / 2] + F[n / 2] * (F[n / 2] - 1) % MOD * Inv2 % MOD) % MOD;
    printf ("%lld\n", ans);
    // while (1);
}