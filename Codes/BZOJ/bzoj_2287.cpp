#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int f[2005];
int ans[2005][2005];
int w[2005];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i = 1; i <= n; i++)
        scanf("%d",w + i);
    f[0] = 1;
    for (int i = 1; i <= n; i++)
        for(int j = m; j >= w[i]; j--)
            f[j] = (f[j] + f[j - w[i]])%10;
    for (int i = 1; i <= n; i++)
    {
        ans[i][0] = 1;
        for (int j = 1; j <= m; j++)
        {
            if(j >= w[i])
                ans[i][j] = (f[j] - ans[i][j - w[i]] + 10 ) % 10;
            else
                ans[i][j] = f[j];
        }
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
            printf("%d",ans[i][j]);
        printf("\n");
    }
}