// 10 pts n^3  
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
int f[2005][2005];
int main()
{
    int n = read(), m = read();
    for (int i = 1; i <= m; i++) f[1][i] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int k = 1; k <= m; k++)
                if (j <= k || j % k > 0)
                    f[i][k] = (f[i][k] + f[i - 1][j]) % MOD;
    int ans = 0;
    for (int i = 1; i <= m; i++)
        ans = (ans + f[n][i]) % MOD;
    printf ("%d\n", ans);
}