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
const int MOD = 258280327;
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
int C[55][55];
int pow2[500];
long long G[55][55][9], F[55][55], P[55][55][9][(1 << 9) + 1];
long long p(int a, int b, int m, int k)
{
    if (a > b) swap(a, b);
    if (a == 0 || k <= 0) return pow2[(a + b) * m];
    if (k >= (1 << m)) return 0;
    if (P[a][b][m][k] != -1) return P[a][b][m][k];
    P[a][b][m][k] = 0;
    for (int i = 0; i <= a; i++)
        for (int j = 0; j <= b; j++)
            if ((i == 0 && j == b) || (i == a && j == 0))
                P[a][b][m][k] = (P[a][b][m][k] + p(a, b, m - 1, k - (1 << (m - 1)))) % MOD;
            else
                P[a][b][m][k] = (P[a][b][m][k] + p(i, j, m - 1, k) * p(a - i, b - j, m - 1, k) % MOD * C[a][i] % MOD * C[b][j] % MOD) % MOD;
    return P[a][b][m][k];
}
long long g(int a, int b, int m)
{
    if (m <= 0) return 0;
    if (a > b) swap(a, b);
    if (G[a][b][m] != -1) return G[a][b][m];
    G[a][b][m] = 0;
    for (int i = 1; i < 1 << m; i++)
        G[a][b][m] = (G[a][b][m] + p(a, b, m, i)) % MOD;
    // printf ("%d %d %d %lld\n", a, b, m, G[a][b][m]);
    return G[a][b][m];
}
long long f(int n, int m)
{
    if (n <= 1 || m <= 0) return 0;
    if (F[n][m] != -1) return F[n][m];
    F[n][m] = 2 * f(n, m - 1) % MOD;
    for (int i = 1; i < n; i++)
        F[n][m] = (F[n][m] + C[n][i] * (pow2[(n - i) * (m - 1)] * f(i, m - 1) % MOD + pow2[i * (m - 1)] * f(n - i, m - 1) % MOD + \
                            g(i, n - i, m - 1) + pow2[(n + 1) * (m - 1)]) % MOD) % MOD;
    // printf ("%d %d %lld\n", n, m, F[n][m]);
    return F[n][m];
}
int main()
{
    int n = read(), m = read();
    C[0][0] = 1;
    pow2[0] = 1;
    for (int i = 1; i <= 499; i++) pow2[i] = pow2[i - 1] * 2 % MOD;
    for (int i = 1; i <= 50; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= 50; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
    memset (F, -1, sizeof (F)), memset (G, -1, sizeof (G)), memset (P, -1, sizeof (P));
    printf ("%lld\n", f(n, m) * pow_mod(pow_mod(1 << m, n), MOD - 2) % MOD);
    // while (1);
}