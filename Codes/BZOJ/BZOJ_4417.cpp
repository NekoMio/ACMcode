#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MOD = 30011;
struct Matrix
{
    int n, m;
    long long a[205][205];
    Matrix(int x, int y)
    {
        n = x, m = y;
        memset(a, 0, sizeof(a));
    }
    void Init()
    {
        for (int i = 0; i <= n; i++)
            a[i][i] = 1;
    }
    long long *operator [](const int c)
    {
        return a[c];
    }
    Matrix operator*(const Matrix &b) const
    {
        Matrix ans(n, b.m);
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++)
                for (int k = 0; k <= b.m; k++)
                    ans.a[i][j] = (ans.a[i][j] + a[i][k] * b.a[k][j]) % MOD;
        return ans;
    }
    Matrix operator^(const long long &b) const
    {
        Matrix ans(n, m);
        ans.Init();
        Matrix c = *this;
        long long k = b;
        while (k)
        {
            if (k & 1)
                ans = c * ans;
            k >>= 1;
            c = c * c;
        }
        return ans;
    }
    void print()
    {
        printf("\n{n,m} = {%d,%d}\n", n, m);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
                printf("%lld ", a[i][j]);
            printf("\n");
        }
        printf("\n");
    }
};
int main()
{
    int n, m;
    scanf ("%d%d", &n, &m);
    static Matrix T1(n + n, n + n), T2(n + n, n + n);
    for (int i = 1; i <= n; i++)
    {
        T1[i][i] = 1;
        T2[i][i] = 1;
        T1[i + n][i] = 1;
        T2[i][i + n] = 1;
        if (i != 1)
        {
            T1[i - 1 + n][i] = 1;
            T2[i - 1][i + n] = 1;
        }
        if (i != n)
        {
            T1[i + 1 + n][i] = 1;
            T2[i + 1][i + n] = 1;
        }
        T1[i + n][i + n] = 1;
        T2[i + n][i + n] = 1;
    }   
    // T1.print(), T2.print();
    Matrix T = T1 * T2;
    // T.print();
    // while(1);
    Matrix A(1, n + n);
    A[1][1] = 1;
    A[1][n + 1] = 1;
    if (n != 1) A[1][n + 2] = 1;
    int t = (m - 1) / 2;
    if (t == 0)
    {
        if (m == 1) printf ("%lld", A[1][n]);
        else printf ("%lld", A[1][n + n]);
        return 0;
    }
    t--;
    A = A * (T ^ t);
    Matrix B = A * T;
    if (m & 1) printf ("%lld", ((B[1][n] - A[1][n]) % MOD + MOD) % MOD);
    else printf ("%lld", ((B[1][n + n] - A[1][n + n]) % MOD + MOD) % MOD);
}