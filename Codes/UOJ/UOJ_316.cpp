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
int n;
const int MAXN = 1005;
long long f[MAXN], p, q;
long long g[MAXN][MAXN], h[MAXN][MAXN];
struct Matrix
{
    long long a[105][105];
    int n;
    Matrix(int x = 0)
    {
        memset (a, 0, sizeof (a));
        n = x;
    }
    Matrix operator*(const Matrix &b)
    {
        Matrix ans(n);
        for (int i = 1; i <= n; i++)
            for (int k = 1; k <= n; k++)
                if (a[i][k] != 0)
                    for (int j = 1; j <= n; j++)
                        if (b.a[k][j] != 0)
                            ans.a[i][j] = (ans.a[i][j] + a[i][k] * b.a[k][j] % MOD) % MOD;
        return ans;            
    }
    Matrix operator^(int b)
    {
        Matrix ans(n), a = *this;
        for (int i = 1; i <= n; i++) ans.a[i][i] = 1;
        while (b)
        {
            if (b & 1) ans = ans * a;
            b >>= 1;
            a = a * a;
        }
        return ans;
    }
}A;
long long Calc(int K)
{
    memset (f, 0, sizeof (f));
    memset (g, 0, sizeof (g));
    memset (h, 0, sizeof (h));
    g[K][0] = 1; h[K][0] = 1;
    g[K][1] = pow_mod(p, K) * q % MOD;
    for (int i = K - 1; i >= 1; i--)
    {
        g[i][0] = 1; h[i][0] = 1;
        for (int j = 1; j <= K / i; j++)
        {
            for (int k = 0; k <= j - 1; k++)
                h[i][j] = (h[i][j] + g[i + 1][j - k - 1] * h[i][k] % MOD * pow_mod(p, i) % MOD * q % MOD) % MOD;
            for (int k = 0; k <= j; k++)
                g[i][j] = (g[i][j] + g[i + 1][j - k] * h[i][k] % MOD) % MOD; 
        }
    }
    long long ans = 0;
    if (n <= 1000)
    {
        f[0] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= K && j < i; j++)
                f[i] = (f[i] + f[i - j - 1] * g[1][j] % MOD * q % MOD) % MOD;
        // long long ans = 0;
        for (int i = 0; i <= n; i++)
            ans = (ans + f[i] * g[1][n - i] % MOD) % MOD;
    }
    else
    {
        f[0] = 1;
        memset (A.a, 0, sizeof (A.a));
        for (int i = 1; i <= K; i++)
            for (int j = 0; j < i; j++)
                f[i] = (f[i] + f[i - j - 1] * g[1][j] % MOD * q % MOD) % MOD;
        for (int i = 0; i <= K; i++)
            A.a[1][i + 1] = g[1][i] * q % MOD;
        A.n = K + 1;
        for (int i = 2; i <= K + 1; i++)
            A.a[i][i - 1] = 1;
        A = A ^ (n - K);
        for (int i = n; i >= n - K; i--)
        {
            long long tmp = 0;
            for (int j = 1; j <= K + 1; j++)
                tmp = (tmp + f[K - j + 1] * A.a[n - i + 1][j] % MOD) % MOD;
            // printf ("%lld\n", tmp);
            ans = (ans + tmp * g[1][n - i] % MOD) % MOD;
        }
        // printf ("\n");
    }
    return ans;
}
int main()
{
    n = read();
    int K = read(), x = read(), y = read();
    p = x * pow_mod(y, MOD - 2) % MOD, q = MOD + 1 - p;
    long long ans = (Calc(K) - Calc(K - 1) + MOD) % MOD;
    printf ("%lld\n", ans);
}