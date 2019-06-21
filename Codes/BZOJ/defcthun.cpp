#include <cstdio>
#include <cstring>
using namespace std;
double f[55][8][8][8];
int main(int argc, char const *argv[])
{
    int T, a, b, c, k;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d%d", &k, &a, &b, &c);
        memset(f, 0, sizeof(f));
        f[1][a][b][c] = 1;
        double ans = 0;
        for (int i = 1; i <= k; i++)
        {
            for (int j = 0; j <= 7; j++)
                for (int l = 0; l <= 7; l++)
                    for (int m = 0; m <= 7; m++)
                    {
                        if (l + j + m <= 7)
                        {
                            if (j > 0)
                                f[i + 1][j - 1][l][m] += f[i][j][l][m] * j * 1.0 / (l + j + m + 1);
                            if (l > 0)
                            {
                                if (l + j + m <= 6)
                                    f[i + 1][j + 1][l - 1][m + 1] += f[i][j][l][m] * l * 1.0 / (l + j + m + 1);
                                else
                                    f[i + 1][j + 1][l - 1][m] += f[i][j][l][m] * l * 1.0 / (l + j + m + 1);
                            }
                            if (m > 0)
                            {
                                if (l + j + m <= 6)
                                    f[i + 1][j][l + 1][m] += f[i][j][l][m] * m * 1.0 / (l + j + m + 1);
                                else
                                    f[i + 1][j][l + 1][m - 1] += f[i][j][l][m] * m * 1.0 / (l + j + m + 1);
                            }
                            f[i + 1][j][l][m] += f[i][j][l][m] * 1.0 / (l + j + m + 1);
                            ans += f[i][j][l][m] * 1.0 / (l + j + m + 1);
                        }
                    }
        }
        printf("%.2lf\n", ans);
    }
    //while (1)
        ;
    return 0;
}
