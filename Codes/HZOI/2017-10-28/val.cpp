#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
long long f[5005][5005][2];
int MOD = 1e9 + 7;
int main()
{
    // freopen("val.in", "r", stdin);
    // freopen("val.out", "w", stdout);
    int n = read(), k = read();
    for (int i = 0; i <= k; i++) f[0][i][i == 0] = 1;
    for (int i = 1; i <= n; i++)
    {
        (f[i][0][1] += f[i - 1][1][0] + f[i - 1][1][1]) %= MOD;
        for (int j = 1; j <= k; j++)
        {
            if (j >= 2) (f[i][j][0] += f[i - 1][j - 2][0]) %= MOD;
            if (j >= 2) (f[i][j][1] += f[i - 1][j - 2][1]) %= MOD;
            if (j >= 1) (f[i][j][0] += f[i - 1][j - 1][0]) %= MOD;
            if (j >= 1) (f[i][j][1] += f[i - 1][j - 1][1]) %= MOD;
            if (j + 1 <= k) (f[i][j][0] += f[i - 1][j + 1][0]) %= MOD;
            if (j + 1 <= k) (f[i][j][1] += f[i - 1][j + 1][1]) %= MOD;
        }
    }
    int Ans = 0;
    for (int i = 0; i <= k; i++) (Ans += f[n][i][1]) %= MOD;
    printf ("%d", Ans);
    // fclose(stdin), fclose(stdout);
}