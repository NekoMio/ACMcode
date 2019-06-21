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
const int MOD = 998244353;
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
long long f[15][10][10], ans[15];
int main()
{
    int T = read(), m = read(), k = read();
    if (m == 1)
    {
        f[0][1][0] = 1;
        for (int i = 1; i <= 10; i++)
        {
            ans[i] += ans[i - 1];
            for (int j = 0; j <= k; j++)
            {
                if (j >= 1) (f[i][j - 1][0] += f[i - 1][j][0] * pow_mod(j + 1, MOD - 2) % MOD) %= MOD;
                (f[i][j][0] += f[i - 1][j][0] * pow_mod(j + 1, MOD - 2) % MOD) %= MOD;
                (ans[i] += f[i - 1][j][0] * pow_mod(j + 1, MOD - 2) % MOD) %= MOD;
                // (f[i][j][0] += f[i][j][0] * pow_mod())
            }
        }
    }
    else if (m == 2)
    {
        f[0][0][1] = 1;
        for (int i = 1; i <= 10; i++)
        {
            ans[i] += ans[i - 1];
            for (int j = 0; j <= k; j++)
                for (int l = 0; l <= k; l++) if (l + j <= k)
                {
                    if (l >= 1 && j + l + 1 <= k) 
                        (f[i][j + 1][l] += f[i - 1][j][l] * pow_mod(j + l + 1, MOD - 2) % MOD * l % MOD) %= MOD;
                    if (l >= 1 && j + l + 1 > k)
                        (f[i][j + 1][l - 1] += f[i - 1][j][l] * pow_mod(j + l + 1, MOD - 2) % MOD * l % MOD) %= MOD;
                    if (j >= 1) 
                        (f[i][j - 1][l] += f[i - 1][j][l] * pow_mod(j + l + 1, MOD - 2) % MOD * j % MOD) %= MOD;
                    (f[i][j][l] += f[i - 1][j][l] * pow_mod(j + l + 1, MOD - 2) % MOD) %= MOD;
                    (ans[i] += f[i - 1][j][l] * pow_mod(j + l + 1, MOD - 2) % MOD) %= MOD;
                }
        }
    }
    while (T--)
    {
        int n = read();
        printf ("%lld\n", ans[n]);
    }
}