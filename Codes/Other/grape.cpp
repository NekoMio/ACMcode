#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long a[10005];
long long f[10005][(1 << 10) + 1];
int Get_Num(int x)
{
    int ans = 0;
    while (x)
    {
        if (x & 1)
            ans++;
        x >>= 1;
    }
    return ans;
}
long long all;
int main()
{
    //freopen("1.in","r",stdin);
    int n, k, Min, Max;
    scanf("%d%d%d%d", &n, &k, &Min, &Max);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        all += a[i];
    }
    //printf("%lld\n",all);
    memset(f, 0xF0, sizeof(f));
    int N = (1 << k) - 1;
    for (int i = 0; i <= N; i++)
    {
        int Num = Get_Num(i);
        if (Num >= Min && Num <= Max)
        {
            f[k][i] = 0;
            for (int j = 1; j <= k; j++)
            {
                if (i & (1 << (j - 1)))
                    f[k][i] += a[k - j + 1];
            }
        }
    }
    for (int i = k + 1; i <= n; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            int Num = Get_Num(j);
            if (Num >= Min && Num <= Max)
            {
                f[i][j] = f[i - 1][j >> 1] + ((j & 1) ? a[i] : 0);
                f[i][j] = max(f[i][j], f[i - 1][(j >> 1) | (1 << (k - 1))] + ((j & 1) ? a[i] : 0));
            }
        }
    }
    long long Maxans = 0xf0f0f0f0f0f0f0f0ll;
    for (int i = 0; i <= N; i++)
        if(Get_Num(i) >= Min && Get_Num(i) <= Max)
            Maxans = max(Maxans, f[n][i]);
    printf("%lld", Maxans - (all - Maxans));
    //while(1);
}
