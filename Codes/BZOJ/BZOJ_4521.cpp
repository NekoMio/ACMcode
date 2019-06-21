#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
long long f[15][2][10][10][4][2];
int g(int a, int b)
{
    return (((a == 8) << 1)|(b == 4))|(((b == 8) << 1) | (a == 4));
}
long long DP(long long x)
{
    int a[15];
    int len = 0;
    memset(f, 0, sizeof (f));
    while (x) a[11 - (len++)] = x % 10, x /= 10;
    int fe = g(a[1], a[2]), fg = 0;
    f[2][0][a[1]][a[2]][fe][0] = 1;
    for (int i = 1; i <= a[1]; i++)
        for (int j = 0; j <= 9; j++)
        {
            if (i == a[1] && j >= a[2]) continue;
            f[2][1][i][j][g(i, j)][0] = 1;
        }
    for (int i = 3; i <= 11; i++)
    {
        fe |= g(a[i], a[i]), fg |= (a[i] == a[i - 1] && a[i] == a[i - 2]);
        if (fe != 3) f[i][0][a[i - 1]][a[i]][fe][fg] = 1;
        for (int j = 0; j <= 9; j++)
        {
            for (int k = 0; k <= 9; k++)
            {
                for (int fo = 0; fo <= 2; fo++)
                {
                    for (int ne = 0; ne <= 9; ne++)
                    {
                        int fe1 = fo | g(ne, ne), fg1 = (j == k) && (k == ne);
                        if (fe1 == 3) continue;
                        f[i][1][k][ne][fe1][1] += f[i - 1][1][j][k][fo][1] + f[i - 1][0][j][k][fo][1] * (ne < a[i]);
                        f[i][1][k][ne][fe1][fg1] += f[i - 1][1][j][k][fo][0] + f[i - 1][0][j][k][fo][0] * (ne < a[i]);
                    }
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i <= 9; i++)
    {
        for (int j = 0; j <= 9; j++)
        {
            for (int k = 0; k <= 2; k++)
            {
                for (int g = 0; g <= 1; g++)
                    ans += f[11][g][i][j][k][1];
            }
        }
    }
    return ans;
}
int main()
{
    long long L, R;
    scanf ("%lld%lld", &L, &R);
    if (L == 10000000000ll) 
        printf ("%lld", DP(R) - DP(L) + 1);
    else printf ("%lld", DP(R) - DP(L - 1));
}