#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
char c[] = {0, 'e', 'r', 'e', 'w', 'r', 'w', 'e', 'r', 'w', 'e', 'r', '\0'};
char s[100005];
long long MOD = 1e9+7;
long long f[100005][15];
int m = 11, n;
int main()
{
    //freopen("ere.in","r",stdin);
   // freopen("ere.out","w",stdout);
    scanf("%s", s + 1);
    n = strlen(s + 1);
    f[0][0] = 1;
    for(int i = 1; i <= n; i++)
    {
        f[i][0] = 1;
        for(int j = 1; j <= m; j++)
            if(s[i] == c[j])
                f[i][j] = (f[i - 1][j] + f[i - 1][j - 1])%MOD;
            else
                f[i][j] = f[i - 1][j];
    }
    printf("%lld\n", f[n][m]);
    //while (1);
}