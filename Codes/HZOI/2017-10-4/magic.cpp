#include <cstdio>
#include <cstring>
using namespace std;
#define int long long
int a[6], f[1000005][6], b[6];
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
int C(int n, int m, int p)
{
    if (m == 0 || n == m) return 1;
    if (n < m) return 0;
    return f[n][p] * pow_mod(f[m][p] * f[n - m][p] % a[p], a[p] - 2, a[p]) % a[p];
}
int lucas(int n, int m, int p)
{
    if (m == 0 || n == m) return 1;
    if (n < m) return 0;
    return C(n % a[p], m % a[p], p) * lucas(n / a[p], m / a[p], p) % a[p]; 
}
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}
int CRT(int *a, int *b, int n)
{
    int N = 1, Ni, now, ans = 0;
    for (int i = 1; i <= n; i++) N *= a[i];
    for (int i = 1; i <= n; i++)
    {
        Ni = N / a[i];
        now = pow_mod(Ni, a[i] - 2, a[i]);
        ans = (ans + (b[i] * now % N) * Ni % N) % N;    
    }
    return ans;
}
signed main()
{
    int N, G;
    a[1] = 2, a[2] = 3, a[3] = 5, a[4] = 7, a[5] = 129011;
    f[0][1] = f[0][2] = f[0][3] = f[0][4] = f[0][5] = 1;
    for (int i = 1; i <= 1000000; i++)
        for (int j = 1; j <= 5; j++)
            f[i][j] = f[i - 1][j] * i % a[j];
    scanf("%lld%lld", &N, &G);
    for (int i = 1; i <= N; i++)
        if(gcd(i, N) == 1)
            for (int j = 1; j <= 5; j++)
                b[j] = (b[j] + lucas(G, i, j)) % a[j];
    int tmp = CRT(a, b, 5);
    tmp += 27092310;
    int ans = pow_mod(N, tmp, 54184622);
    printf("%lld", ans);
    // while (1);
}
