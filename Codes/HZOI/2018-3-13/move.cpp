#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
template<typename _Tp>
inline _Tp read()
{
    _Tp x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MOD = 100003;
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
long long f[MOD + 2];
long long C(long long n, long long m)
{
    if (n < m) return 0;
    return f[n] * pow_mod(f[m] * f[n - m] % MOD, MOD - 2) % MOD;
}
long long DP[2][2];
int main()
{
    long long a = read<long long>(), b = read<long long>();
    long long n = (a + b), m = (a - b);
    if (n & 1) return printf ("0"), 0;
    if (m < 0) return printf ("0"), 0;
    n >>= 1, m >>= 1;
    f[0] = 1;
    for (int i = 1; i <= MOD; i++) f[i] = f[i - 1] * i % MOD;
    long long ans = 0;
    int now = 0;
    DP[now][0] = 1;
    long long x = n + m;
    for (int i = 0; i < 5; i++)
    {
        now ^= 1;
        memset (DP[now], 0, sizeof (DP[0]));
        int N = n % MOD, X = x % MOD, M = m % MOD;
        n /= MOD, x /= MOD, m /= MOD;
        for (int k = 0; k <= 1; k++)
            for (int j = 0; j < MOD; j++)
                if (j <= N && j <= M)
                {
                    int a = C(N, j), t = X - k - j;
                    if (t < 0)
                        DP[now][1] = (DP[now][1] + 1ll * DP[now ^ 1][k] * a % MOD * C(t + MOD, N) % MOD) % MOD;
                    else
                        DP[now][0] = (DP[now][0] + 1ll * DP[now ^ 1][k] * a % MOD * C(t, N) % MOD) % MOD;
                }
    }
    printf ("%d\n", DP[now][0]);
}