#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline long long read()
{
    long long x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MOD = 998244353;
struct Matrix
{
    int a[200][200];
    int n, m;
    Matrix(int _n = 0, int _m = 0)
    {
        n = _n, m = _m;
        memset (a, 0, sizeof (a));
    }
    Matrix operator * (const Matrix &b) const 
    {
        Matrix ans(n, b.m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                for (int k = 1; k <= b.m; k++)
                    ans.a[i][k] = (ans.a[i][k] + 1ll * a[i][j] * b.a[j][k]) % MOD;
        return ans;
    }
}A[64];
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
int cnt[10][10][10], Index, IDans;
int main()
{
    int T = read(), m = read(), k = read();
    for (int i = 0; i <= k; i++)
        for (int j = 0; j <= (m == 1 ? 0 : k); j++)
            for (int l = 0; l <= ((m == 1 || m == 2) ? 0 : k); l++) if (i + j + l <= k)
                cnt[i][j][l] = ++Index;
    IDans = ++Index;
    if (m == 1)
    {
        for (int i = 0; i <= k; i++)
        {
            if (i > 0) (A[0].a[cnt[i][0][0]][cnt[i - 1][0][0]] += i * pow_mod(i + 1, MOD - 2) % MOD) %= MOD;
            (A[0].a[cnt[i][0][0]][cnt[i][0][0]] += pow_mod(i + 1, MOD - 2)) %= MOD;
            (A[0].a[cnt[i][0][0]][IDans] += pow_mod(i + 1, MOD - 2)) %= MOD;
        }
        A[0].a[IDans][IDans] = 1;
    }
    else if (m == 2)
    {
        for (int j = 0; j <= k; j++)
            for (int l = 0; l <= k; l++) if (l + j <= k)
            {
                if (l >= 1 && j + l + 1 <= k) 
                    (A[0].a[cnt[j][l][0]][cnt[j + 1][l][0]] += pow_mod(j + l + 1, MOD - 2) * l % MOD) %= MOD;
                if (l >= 1 && j + l + 1 > k)
                    (A[0].a[cnt[j][l][0]][cnt[j + 1][l - 1][0]] += pow_mod(j + l + 1, MOD - 2) * l % MOD) %= MOD;
                if (j >= 1)
                    (A[0].a[cnt[j][l][0]][cnt[j - 1][l][0]] += pow_mod(j + l + 1, MOD - 2) * j % MOD) %= MOD;
                (A[0].a[cnt[j][l][0]][cnt[j][l][0]] += pow_mod(j + l + 1, MOD - 2)) %= MOD;
                (A[0].a[cnt[j][l][0]][IDans] += pow_mod(j + l + 1, MOD - 2)) %= MOD;
            }
        A[0].a[IDans][IDans] = 1;
    }
    else
    {
        for (int i = 0; i <= k; i++)
            for (int j = 0; j <= k; j++)
                for (int l = 0; l <= k; l++) if (i + j + l <= k)
                {
                    if (i > 0)
                        (A[0].a[cnt[i][j][l]][cnt[i - 1][j][l]] += i * pow_mod(i + j + l + 1, MOD - 2) % MOD) %= MOD;
                    if (j > 0)
                    {
                        if (i + j + l + 1 <= k) 
                            (A[0].a[cnt[i][j][l]][cnt[i + 1][j - 1][l + 1]] += j * pow_mod(i + j + l + 1, MOD - 2) % MOD) %= MOD;
                        else 
                            (A[0].a[cnt[i][j][l]][cnt[i + 1][j - 1][l]] += j * pow_mod(i + j + l + 1, MOD - 2) % MOD) %= MOD;
                    }
                    if (l > 0)
                    {
                        if (i + j + l + 1 <= k) 
                            (A[0].a[cnt[i][j][l]][cnt[i][j + 1][l]] += l * pow_mod(i + j + l + 1, MOD - 2) % MOD) %= MOD;
                        else 
                            (A[0].a[cnt[i][j][l]][cnt[i][j + 1][l - 1]] += l * pow_mod(i + j + l + 1, MOD - 2) % MOD) %= MOD;
                    }
                    (A[0].a[cnt[i][j][l]][cnt[i][j][l]] += pow_mod(i + j + l + 1, MOD - 2)) %= MOD;
                    (A[0].a[cnt[i][j][l]][IDans] += pow_mod(i + j + l + 1, MOD - 2)) %= MOD;
                }
        A[0].a[IDans][IDans] = 1;
    }
    A[0].n = A[0].m = Index;
    for (int i = 1; i <= 63; i++)
        A[i] = A[i - 1] * A[i - 1];
    while (T--)
    {
        Matrix B(1, Index);
        B.a[1][cnt[m == 1][m == 2][m == 3]] = 1;
        long long n = read();
        for (int i = 0; i <= 63; i++)
            if (n & (1ll << i))
                B = B * A[i];
        printf ("%d\n", B.a[1][IDans]);
    }
}