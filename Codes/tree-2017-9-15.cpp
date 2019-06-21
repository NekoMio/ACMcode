#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long f[305][305];
int MOD;
int main()
{
    int k;
    scanf("%d%d", &k, &MOD);
    f[1][0] = f[1][1] = 1 % MOD;
    for (int i = 1; i < k; i++)
    {
        for (int l = 0; l <= k - i + 1; l++)
            for (int r = 0; r <= k - i + 1; r++)
            {
                long long num = f[i][l] * f[i][r] % MOD;
                if (r + l <= k - i)
                {
                    f[i + 1][r + l] = (f[i + 1][r + l] + num) % MOD;
                    f[i + 1][r + l] = (f[i + 1][r + l] + 2 * num * (l + r) % MOD) % MOD;
                }
                if (r + l + 1 <= k - i)
                    f[i + 1][r + l + 1] = (f[i + 1][r + l + 1] + num) % MOD;
                if (r + l - 1 <= k - i)
                {
                    f[i + 1][r + l - 1] = (f[i + 1][r + l - 1] + 2 * num * l * r % MOD) % MOD;
                    f[i + 1][r + l - 1] = (f[i + 1][r + l - 1] + num * (l * (l - 1) + r * (r - 1)) % MOD) % MOD;
                }
            }
    }
    printf("%lld", f[k][1]);
}
