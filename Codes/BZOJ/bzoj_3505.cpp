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
long long C[1000005][4];
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}
int main()
{
    int n = read() + 1, m = read() + 1;
    C[0][0] = 1;
    for (int i = 1; i <= n * m; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= 3; j++)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    long long ans = C[n * m][3];
    ans -= C[n][3] * m;
    ans -= C[m][3] * n;
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++)
        {
            int Gcd = gcd(i, j);
            if (Gcd > 1)
                ans -= 2 * (Gcd - 1) * (n - i) * (m - j);
        }
    printf ("%lld\n", ans);
}