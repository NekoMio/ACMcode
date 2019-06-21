#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int a[2005], n, size;
int f[2005][2005];
int Hash[2005];
inline void Hash_init()
{
    sort(Hash + 1, Hash + n + 1);
    size = unique(Hash + 1, Hash + n + 1) - Hash - 1;
}
int main()
{
    // freopen("grading.in","r",stdin);
    // freopen("grading.out","w",stdout);
    scanf("%d\n", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        Hash[i] = a[i];
    }
    Hash_init();
    int minn = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
    {   
        minn = 0x3f3f3f3f;
        for (int j = 1; j <= size; j++)
        {
            minn = min(minn, f[i - 1][j]);
            f[i][j] = minn +abs(Hash[j] - a[i]);
        }
    }
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= size; i++)
        ans = min(ans, f[n][i]);
    memset(f,0,sizeof(f));
    // for (int i = n; i >= 1; i++)
    // {   
    //     minn = 0x3f3f3f3f;
    //     for (int j = 1; j <= size; j++)
    //     {
    //         minn = min(minn, f[i + 1][j]);
    //         f[i][j] = minn +abs(Hash[j] - a[i]);
    //     }
    // }
    // for (int i = 1; i <= size; i++)
    //     ans = min(ans, f[1][i]);
    printf("%d\n", ans);
}