#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MOD = 1e9 + 7;
template<typename _Tp>
inline _Tp read()
{
    _Tp x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct Matrix
{
    long long a[5][5];
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
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= n; k++)
                    ans.a[i][j] = (ans.a[i][j] + a[i][k] * b.a[k][j] % MOD) % MOD;
        return ans;
    }
    Matrix operator^(long long b)
    {
        Matrix ans(n);
        for (int i = 1; i <= n; i++) ans.a[i][i] = 1;
        Matrix a = *this;
        while (b)
        {
            if (b & 1) ans = ans * a;
            b >>= 1;
            a = a * a;
        }
        return ans;
    }
}A, B;
int main()
{
    int t = read<int>();
    long long n, k;
    while (t--)
    {
        n = read<long long>(), k = read<long long>();
        if (n == 1) 
        {
            printf ("1\n");
            continue;
        }
        else if (n == 2)
        {
            B.a[1][1] = 1;
            B.a[1][2] = B.a[2][1] = 1;
            B.a[2][2] = 2;
        }
        else
        {
            A.n = 3;
            A.a[1][1] = A.a[2][1] = A.a[3][1] = 1;
            A.a[3][3] = A.a[1][2] = A.a[1][3] = 0;
            A.a[2][2] = A.a[3][2] = A.a[2][3] = 1;
            Matrix C = A ^ (n - 3);
            B.a[1][1] = (C.a[1][1] + C.a[2][1] + 1) % MOD;
            C = C * A;
            B.a[1][2] = B.a[2][1] = (C.a[1][1] + C.a[2][1]) % MOD;
            C = C * A;
            B.a[2][2] = (C.a[1][1] + C.a[2][1]) % MOD;
            // printf ("%lld\n", (A.a[1][1] % MOD + A.a[2][1]) % MOD);
        }
        B.n = 2;
        B = B ^ k;
        printf ("%lld\n", (B.a[1][1] + B.a[1][2]) % MOD);
    }
}