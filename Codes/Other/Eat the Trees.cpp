#include <cstdio>
#include <cstring>
using namespace std;
const int Max = (1 << 12) + 10;
int n, m;
int mp[12][12];
long long DP[12][12][Max];

void dp()
{
    memset(DP, 0, sizeof(DP));
    DP[0][m][0] = 1;
    int bit = 1 << (m + 1);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < (bit >> 1); j++)
        {
            DP[i][0][j << 1] = DP[i - 1][m][j];
        }
        for (int j = 1; j <= m; j++)
        {
            for (int k = 0; k < bit; k++)
            {
                int x = 1 << (j - 1);
                int y = 1 << j;
                if (mp[i][j])
                {
                    DP[i][j][k] += DP[i][j - 1][k ^ x ^ y];
                    if ((k & x) && (k & y))
                        continue;
                    if (!(k & x) && !(k & y))
                        continue;
                    DP[i][j][k] += DP[i][j - 1][k];
                }
                else
                {
                    if (!(k & x) && !(k & y))
                        DP[i][j][k] = DP[i][j - 1][k];
                    else
                        DP[i][j][k] = 0;
                }
            }
        }
    }
}
int main()
{
    int t, num = 0;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                scanf("%d", &mp[i][j]);
            }
        }
        dp();
        printf("Case %d: There are %lld ways to eat the trees.\n", ++num, DP[n][m][0]);
    }
    //while(1);
}