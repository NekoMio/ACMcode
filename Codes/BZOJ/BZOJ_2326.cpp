#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
long long MOD = 0;
struct Matrix
{
    int n, m;
    long long a[5][5];
    Matrix(int x, int y)
    {
        n = x, m = y;
        memset(a, 0, sizeof(a));
    }
    void Init()
    {
        for (int i = 1; i <= n; i++)
            a[i][i] = 1;
    }
    Matrix operator*(const Matrix &b) const
    {
        Matrix ans(n, b.m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                for (int k = 1; k <= b.m; k++)
                {
                    ans.a[i][j] = (ans.a[i][j] + a[i][k] % MOD * b.a[k][j] % MOD) % MOD;
                }
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
long long pow(int a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans *= a;
        b >>= 1;
        a *= a;
    }
    return ans;
}

int main()
{
    //freopen("mathwork.in","r",stdin);
    //freopen("mathwork.out", "w", stdout);
    long long n;
    scanf("%lld%lld", &n, &MOD);
    Matrix A(3, 3);
    A.Init();
    long long M = 10;
    while (M <= n)
    {
        Matrix B(3, 3);
        B.a[1][1] = M % MOD;
        B.a[1][2] = B.a[1][3] = B.a[2][2] = B.a[2][3] = B.a[3][3] = 1;
       // printf("%lld\n",M - M / 10);
        B = B ^ (M - M / 10);
        A = B * A;
     //   printf("%lld\n",A.a[1][3]);
        M = M * 10;
    }
    //printf("%lld\n",A.a[1][3]);
    Matrix B(3, 3);
    B.a[1][1] = M % MOD;
    B.a[1][2] = B.a[1][3] = B.a[2][2] = B.a[2][3] = B.a[3][3] = 1;
    //printf("%lld\n",n - M / 10 + 1);
    B = B ^ (n - M / 10 + 1);
    A = B * A;
    printf("%lld", A.a[1][3]);
    //while (1) ;
}