// 40 pts

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1e9 + 7;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
char s[50005];
int a[50005];
long long C[105][105], Sum[105];
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
int main()
{
    // freopen ("number2.in", "r", stdin);
    // freopen ("number.out", "w", stdout);
    // freopen ("1.in", "r", stdin);
    // freopen ("3.out", "w", stdout);
    int T = read();
    C[0][0] = 1;
    for (int i = 1; i <= 100; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= 100; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
    while (T--)
    {
        int n = read(), k = read();
        scanf ("%s", s + 1);
        for (int i = 1; i <= n; i++) 
            a[i] = s[i] - '0';
        for (int i = 1; i <= n; i++)
            a[i] += a[i - 1];
        memset (Sum, 0, sizeof (Sum));
        Sum[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            long long ans = 0;
            long long tmp = 1;
            for (int j = 0; j <= k; j++)
            {
                ans = (ans + C[k][j] * tmp % MOD * Sum[k - j] % MOD) % MOD;
                tmp = tmp * a[i] % MOD;
            }
            tmp = 1;
            for (int j = k; j >= 0; j--)
            {
                Sum[k - j] = (Sum[k - j] + tmp) % MOD;
                tmp = tmp * (MOD - a[i]) % MOD;
            }
            printf ("%lld ", ans);
        }
        printf ("\n");
    }
}