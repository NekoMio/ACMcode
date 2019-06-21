#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
template<typename _Tp>
inline _Tp read()
{
    _Tp x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int C[2334][2334];
int S[2334][2334];
const int MOD = 2333;
inline int c(long long n, long long m)
{
    if (n < m) return 0;
    return C[n][m];
}
inline int lucas(long long n, long long m)
{
    if (m == 0) return 1;
    // if (n < m) return 0;
    return c(n % MOD, m % MOD) * lucas(n / MOD, m / MOD) % MOD;
}
int Solve(long long n, long long k)
{
    if (k == 0) return 1;
    if (k < 0) return 0;
    int Sum1 = Solve(n / MOD, k / MOD - 1);
    int Sum2 = (Sum1 + lucas(n / MOD, k / MOD)) % MOD;
    return (Sum2 * S[n % MOD][k % MOD] % MOD + ((S[n % MOD][MOD - 1] - S[n % MOD][k % MOD]) % MOD + MOD) % MOD * Sum1 % MOD) % MOD;
}
int main()
{
    C[0][0] = 1;
    for (int i = 1; i <= MOD; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= MOD; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
    //S[0][0] = 1;
    for (int i = 0; i <= MOD; i++)
    {
        S[i][0] = 1;
        for (int j = 1; j <= MOD; j++)
            S[i][j] = (S[i][j - 1] + C[i][j]) % MOD;
    }
    int t = read<int>();
    while (t--)
    {
        long long n = read<long long>(), k = read<long long>();
        int ans = Solve(n, k);
        printf ("%d\n", ans);
    }
    // while (1);
}