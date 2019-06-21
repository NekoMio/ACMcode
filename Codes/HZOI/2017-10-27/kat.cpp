#pragma GCC optimize("O2")
#include <cstdio>
#include <cstring>
using namespace std;
#define int long long 
const int MOD = 1000000007;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int pow_mod(int a, int b)
{
    int ans = 1; 
    while (b)
    {
        if (b & 1) ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
int w[1005];
int F[1005];
int C(int n, int m)
{
    if (n == m || !m) return 1;
    if (n < m) return 0;
    return F[n] * pow_mod(F[m] * F[n - m] % MOD, MOD - 2) % MOD;
}
signed main()
{
    // freopen("kat.in", "r", stdin);
    // freopen("kat.out", "w", stdout);
    int n, m, k;
    n = read(), m = read(), k = read();
    for (int i = 1; i <= m; i++)
        w[i] = read();
    if (n < k) return printf ("0"), 0;
    F[0] = 1;
    for (int i = 1; i <= 1000; i++)
        F[i] = F[i - 1] * i % MOD;
    int ans = 0;
    int Inv = pow_mod(m, MOD - 2) % MOD;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            ans = (ans + (((w[i] * pow_mod(Inv, j) % MOD) * C(k, j) % MOD) * pow_mod((i - 1) * Inv % MOD, k - j)) % MOD) % MOD;
        }
    }
    printf ("%lld", (ans * (n - k + 1) % MOD));
    // fclose(stdin), fclose(stdout);
    // while (1);
}
/*
2 2 2
1 2
750000007
*/
