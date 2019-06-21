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
int pow_mod(int a, int b, int p)
{
    int ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % p;
        b >>= 1;
        a = a * a % p;
    }
    return ans;
}
const int MAXN = 262145;
const int MOD = 10007;
const int Inv2 = 5004;
void FWT(int *a, int n)
{
    for (int k = 1; k < (1 << n); k <<= 1)
        for (int i = 0; i < (1 << n); i++)
        {
            if (i & k) continue;
            int tmp = (a[i] + a[i + k]) % MOD;
            a[i + k] = (a[i] - a[i + k] + MOD) % MOD;
            a[i] = tmp;
        }
}
void IFWT(int *a, int n)
{
    for (int k = 1; k < (1 << n); k <<= 1)
        for (int i = 0; i < (1 << n); i++)
        {
            if (i & k) continue;
            int tmp = (a[i] + a[i + k]) % MOD * Inv2 % MOD;
            a[i + k] = (a[i] - a[i + k] + MOD) % MOD * Inv2 % MOD;
            a[i] = tmp;
        }
}
int a[2][MAXN];
int F[10008][35];
int powX[10008][35];
int Trans(int x, int t)
{
    int ans = 0;
    for (int i = 0; i <= 30; i++)
    {
        if (t & (1 << i))
        {
            ans = (ans + F[x][i]) % MOD;
            x = powX[x][i];
        }
    }
    return (ans + x) % MOD;
}
int main()
{
    int n = read(), p = read(), j = read();
    int m = (1 << n) - 1;
    for (int i = 0; i <= m; i++)
        a[0][i] = read();
    for (int i = 0; i <= 10006; i++)
        for (int j = 0; j <= 30; j++)
            powX[i][j] = pow_mod(i, pow_mod(2, 1 << j, MOD - 1), MOD);
    for (int i = 0; i <= 10006; i++) F[i][0] = i;
    for (int i = 1; i <= 30; i++)
        for (int j = 0; j <= 10006; j++)
            F[j][i] = (F[j][i - 1] + F[powX[j][i - 1]][i - 1]) % MOD;
    FWT(a[0], n);
    for (int i = 0; i <= m; i++)
    {
        a[0][i] = Trans(a[0][i], p);
    }
    IFWT(a[0], n);
    printf ("%d\n", a[0][j]);
}
