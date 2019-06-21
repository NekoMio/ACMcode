#pragma GCC optimize("O2")
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
int gcd[1005][1005];
const int MOD = 1e9 + 7;
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
long long Inv(long long x)
{
    return pow_mod(x % MOD, MOD - 2);
}
long long C(long long n, long long m)
{
    if (n < m) return 0;
    long long ans = 1;
    for (int i = 1; i <= m; i++) ans = ans * (n - i + 1) % MOD;
    for (int i = 1; i <= m; i++) ans = ans * Inv(i) % MOD;
    return ans;
}
long long Calc1(int n, int m)
{
    long long ans = C((n + 1) * (m + 1), 4);
    long long tmp = 0;
    for (int i = 0; i <= n; i++)
        for (int j = !i; j <= m; j++)
            tmp = (tmp + (j && i ? 2 : 1) * C(gcd[i][j] - 1, 1) * ((n + 1) * (m + 1) - 3) % MOD * (n + 1 - i) % MOD * (m + 1 - j) % MOD) % MOD;
    for (int i = 0; i <= n; i++)
        for (int j = !i; j <= m; j++)
            tmp = (tmp - 3 * (i && j ? 2 : 1) * C(gcd[i][j] - 1, 2) % MOD * (n + 1 - i) % MOD * (m + 1 - j) % MOD + MOD) % MOD;
    return (ans - tmp + MOD) % MOD;
}
struct Point
{
    long long x, y;
    Point(long long _x, long long _y): x(_x), y(_y) {}
    Point operator - (const Point &a) const { return Point(x - a.x, y - a.y); }
    long long operator * (const Point &a) { return x * a.y - y * a.x; }
};
long long Calc_3(const Point &a, const Point &b, const Point &c)
{
    long long ans = abs((b - a) * (c - a));
    int A = gcd[abs(a.x - b.x)][abs(a.y - b.y)], B = gcd[abs(b.x - c.x)][abs(b.y - c.y)], C = gcd[abs(a.x - c.x)][abs(a.y - c.y)];
    return (ans - (A + B + C) + 2) / 2;
}
long long Sum[1005][1005];
long long Sum1[1005][1005];
long long Sum2[1005][1005];
long long Sum3[1005][1005];
long long Sum4[1005];
long long f[1005][1005];
long long Calc2(int n, int m)
{
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (f[i][j])
            {
                ans = (ans + f[i][j] * (n - i + 1) * (m - j + 1)) % MOD;
                continue;
            }
            long long tmp = 0;
            for (int k = 0; k <= i; k++)
            {
                int l = (i - k) * j / i;
                if (i * l == j * (i - k)) --l;
                if (l == -1) continue;
                tmp = (tmp - 2 * Sum4[l] * i\
                + 2ll * (l + 1) * i * j\
                - 2ll * (l + 1) * k * j \
                + (l + 1) * 4\
                - 2ll * Sum1[i - k][l]\
                - (l == j ? 2ll * Sum1[k][j] : 2 * (Sum1[k][j] - Sum1[k][j - l - 1]))\
                - 2ll * (l + 1) * gcd[i][j]) % MOD; 
            }
            tmp = (tmp + 2ll * \
            (1ll * i * j * (i - 1) * (j - 1)\
             - (Sum2[i - 1][j - 1]) \
             - (i - 1) * (Sum1[i][j - 1] - Sum1[i][0]) \
             - (j - 1) * (Sum[i - 1][j] - Sum[0][j]) \
             + 2ll * (i - 1) * (j - 1) \
             - (Sum3[i - 1][j - 1] - Sum3[0][j - 1] - Sum3[i - 1][0] + Sum3[0][0]))) % MOD;
            tmp = (tmp + 1ll * i * (i - 1) * (j - 1) - 2 * (Sum[i - 1][j] - Sum[0][j]) + 2 * (i - 1)) % MOD;
            tmp = (tmp + 1ll * j * (i - 1) * (j - 1) - 2 * (Sum1[i][j - 1] - Sum1[i][0]) + 2 * (j - 1)) % MOD;
            tmp = (tmp % MOD + MOD) % MOD;
            f[i][j] = f[j][i] = tmp;
            ans = (ans + tmp * (n - i + 1) * (m - j + 1)) % MOD;
        }
    return ans;
}
int main()
{
    int n = read(), m = read();
    for (int i = 0; i <= 1000; i++)
        for (int j = 0; j <= 1000; j++)
            gcd[i][j] = [&]()->int{
                if(i && j)
                    return i < j ? gcd[i][j - i] : gcd[i - j][j];
                else
                    return i | j;
            }();
    for (int i = 1; i <= 1000; i++) Sum4[i] = (Sum4[i - 1] + i) % MOD;
    for (int i = 0; i <= 1000; i++)
        for (int j = 0; j <= 1000; j++)
            Sum[i][j] = ((i == 0 ? 0 : Sum[i - 1][j]) + gcd[i][j]) % MOD;
    for (int i = 0; i <= 1000; i++)
        for (int j = 0; j <= 1000; j++)
            Sum1[i][j] = ((j == 0 ? 0 : Sum1[i][j - 1]) + gcd[i][j]) % MOD;
    for (int i = 1; i <= 1000; i++)
        for (int j = 1; j <= 1000; j++)
            Sum2[i][j] = ((Sum2[i - 1][j] + Sum2[i][j - 1] - Sum2[i - 1][j - 1] + i * j % MOD) % MOD + MOD) % MOD;
    for (int i = 0; i <= 1000; i++)
        for (int j = 0; j <= 1000; j++)
            Sum3[i][j] = (((i == 0 ? 0 : Sum3[i - 1][j]) + (j == 0 ? 0 : Sum3[i][j - 1]) - ((j == 0 || i == 0) ? 0 : Sum3[i - 1][j - 1]) + gcd[i][j]) % MOD + MOD) % MOD;
    printf ("%lld", (Calc1(n, m) + 2 * Calc2(n, m)) % MOD);
    // while (1);
}