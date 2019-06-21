/**
******************************************************************************
* @file	Function
* @author 	WildRage
* @version v 1.0
* @date 2017-8-10 10:57:28
* @brief 
******************************************************************************
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define LL long long
LL a[1005], b[1005], c[1005];
LL Max[200005];
int fix = 100001;
int main()
{
    memset(Max, 0x80, sizeof(Max));
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
    }
    LL u;
    for (int i = -100000; i <= 100000; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            Max[i + fix] = max(Max[i + fix], a[j] * i * i + b[j] * i + c[j]);
        }
    }
    while (q--)
    {
        scanf("%lld", &u);
        printf("%lld\n", Max[u + fix]);
    }
    return 0;
}
