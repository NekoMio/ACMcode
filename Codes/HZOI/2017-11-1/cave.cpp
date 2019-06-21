#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MOD = 1e9 + 7;
struct Matrix
{
    long long a[1005];
    int n;
    Matrix(int x = 0)
    {
        n = x;
        memset (a, 0, sizeof (a));
    }
    inline long long &operator[](int x)
    {
        return a[x];
    }
    inline const long long operator[](int x) const
    {
        return a[x];
    }
    Matrix operator * (const Matrix &b)
    {
        Matrix ans(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                (ans[i] += a[j] * b[(i - j + n) % n] % MOD) %= MOD;
        return ans;
    }
    Matrix operator ^ (int b)
    {
        Matrix ans(n), a = *this;
        ans[0] = 1;
        while (b)
        {
            if (b & 1) ans = ans * a;
            b >>= 1;
            a = a * a;
        }
        return ans;
    }
}F[1005];
signed main()
{
    int n, m;
    scanf ("%d%d", &n, &m);
    F[0][0] = 1;
    for (int i = 0; i < n; i++)
    {
        F[i + 1].n = n;
        for (int j = 0; j < n; j++)
        {
            (F[i + 1][(j + i + 1) % n] += F[i][j]) %= MOD;
            if ((j + i + 1) % n != (j - i - 1 + n) % n)
                (F[i + 1][(j - i - 1 + n) % n] += F[i][j]) %= MOD;
        }
    }
    return printf ("%lld", ((F[n] ^ (m / n)) * F[m % n])[0]), 0;
}