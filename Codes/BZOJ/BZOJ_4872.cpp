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
int MOD = 100003;
int a[100005];
int Inv[100005];
long long f[100005];
int pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return (int)ans;
}
int main()
{
    int n = read(), k = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    for (int i = 1; i <= n; i++)
        Inv[i] = pow_mod(i, MOD - 2);
    long long N = 1;
    for (int i = 1; i <= n; i++) N = N * i % MOD;
    int cnt = 0;
    for (int i = n; i >= 1; i--)
        if (a[i])
        {
            cnt++;
            for (int j = 1; j * j <= i; j++)
                if (i % j == 0)
                {
                    a[j] ^= 1;
                    if (j * j != i) a[i / j] ^= 1;
                }
        }
    long long ans = 0;
    for (int i = n; i >= 1; i--)
    {
        if (i <= k) f[i] = 1;
        else
            f[i] = (n + f[i + 1] * (n - i) % MOD) * Inv[i] % MOD;
        if (i <= cnt) ans = (ans + f[i]) % MOD;
    }
    printf ("%lld\n", 1ll * ans * N % MOD);
}