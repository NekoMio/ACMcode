#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1e9 + 7;
char s[1000005];
long long f[1000005][4][4];
inline int Get(char x)
{
    if (x == '0')
        return 0;
    if (x == '1')
        return 1;
    if (x == '2')
        return 2;
    if (x == '*')
        return 3;
    else return 5;
}
int main()
{
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    int l = Get(s[1]);
    if(l == 1 || l == 5)
        f[1][1][0] = 1;
    if(l == 3 || l == 5)
        f[1][3][0] = 1;
    if(l == 0 || l == 5)
        f[1][0][0] = 1;
    for (int i = 2; i <= n; i++)
    {
        int now = Get(s[i]);
        if (now == 0 || now == 5) 
        {
            f[i][0][1] = f[i - 1][1][3];
            f[i][0][0] = (f[i - 1][0][0] + f[i - 1][0][1]) % MOD;
        }
        if (now == 1 || now == 5)
        {
            f[i][1][0] = (f[i - 1][0][1] + f[i - 1][0][0]) % MOD;
            f[i][1][1] = f[i - 1][1][3];
            f[i][1][3] = (f[i - 1][3][1] + f[i - 1][3][2] + f[i - 1][3][3] + f[i - 1][3][0]) % MOD;
        }
        if (now == 2 || now == 5)
        {
            f[i][2][3] = (f[i - 1][3][1] + f[i - 1][3][2] + f[i - 1][3][3] + f[i - 1][3][0]) % MOD;
        }
        if (now == 3 || now == 5)
        {
            f[i][3][1] = (f[i - 1][1][0] + f[i - 1][1][1]) % MOD;
            f[i][3][2] = f[i - 1][2][3];
            f[i][3][3] = (f[i - 1][3][1] + f[i - 1][3][2] + f[i - 1][3][3] + f[i - 1][3][0]) % MOD; 
        }
    }
    long long ans = 0;
    ans = f[n][1][3] + f[n][0][1] + f[n][0][0] + f[n][3][1] + f[n][3][2] + f[n][3][3];
    printf("%d", (int)(ans % MOD));
    // while(1);
}