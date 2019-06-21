// 40 pts n^2log(n)  
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
const int MOD = 998244353;
int f[2005][2005], Sum[2005];
int main()
{
    int n = read(), m = read();
    for (int i = 1; i <= m; i++) f[1][i] = 1, Sum[1]++;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            f[i][j] = Sum[i - 1];
            for (int k = 2 * j; k <= m; k += j)
                f[i][j] = ((f[i][j] - f[i - 1][k]) % MOD + MOD) % MOD;
            Sum[i] = (Sum[i] + f[i][j]) % MOD;
        }
    }
    printf ("%d", Sum[n]);
}