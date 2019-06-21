#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int f[300005][2][2], a[300005];
bool change[300005];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    a[0] = -1;
    int ans = 0;
    f[1][0][0] = 1;
    f[1][0][1] = 0;
    f[1][1][1] = 1;
    f[1][1][0] = 0;
    for (int i = 2; i <= n; i++)
    {
        f[i][0][0] = 1;
        f[i][0][1] = 1;
        f[i][1][1] = 1;
        f[i][1][0] = 0;
        if (a[i] > a[i - 1])
        {
            f[i][0][0] = f[i - 1][0][0] + 1;
            f[i][0][1] = f[i - 1][0][1] + 1;
        }
        if (f[i - 1][1][1] == f[i - 2][0][0] + 1)
        {
            if(a[i] > a[i - 2] + 1)
            {
                f[i][0][1] = max(f[i][0][1], f[i - 1][1][1] + 1);
            }
        }
        else
        {
            f[i][0][1] = max(f[i][0][1], f[i - 1][1][1]);
        }
        f[i][1][1] = max(f[i][1][1], f[i - 1][0][0] + 1);
        ans = max(ans,max(f[i][0][0],max(f[i][0][1],f[i][1][1])));
    }
    printf("%d",ans);
}
