#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int a[5][5], b[5][5];
int Index;
int dis[20][20];
void find(int x, int y)
{
    int k = b[x][y];
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            if (a[i][j])
                dis[k][a[i][j]] = abs(i - x) + abs(j - y);
}
int get_num(int x)
{
    int ans = 0;
    while (x)
    {
        ans += (x & 1);
        x >>= 1;
    }
    return ans;
}
int f[17][(1 << 16) + 1];
int main()
{
    freopen("movea.in","r",stdin);
    freopen("movea.out","w",stdout);
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
        {
            scanf("%1d", &a[i][j]);
            if (a[i][j])
                a[i][j] = ++Index;
        }
    Index = 0;
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
        {
            scanf("%1d", &b[i][j]);
            if (b[i][j])
                b[i][j] = ++Index;
        }
    memset(f,0x3f,sizeof(f));
    f[0][0]=0;
    int N = (1 << Index) - 1;
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            if (b[i][j])
                find(i, j);
    for (int i = 1; i <= Index; i++)
    {
        for (int S = 0; S <= N; S++)
        {
            if (get_num(S) == i - 1)
            {
                for (int j = 1; j <= Index; j++)
                {
                    if (!(S & (1 << (j - 1))))
                    {
                        f[i][S|(1<<(j-1))]=min(f[i][S|(1<<(j-1))],f[i-1][S]+dis[j][i]);
                    }
                }
            }
        }
    }
    printf("%d\n",f[Index][N]);
}