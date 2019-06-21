#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
using namespace std;
#define LL long long
LL Sum[1000005];
LL x;
int ans[1000005];
int main()
{
    int n;
    scanf("%d%lld", &n, &x);
    for (int i = n - 2; i >= 0; i--)
        Sum[i] = Sum[i + 1] + i;
    if (Sum[0] < x)
    {
        puts("-1");
        return 0;
    }
    int k, i, j;
    for (k = 1; k <= n - 2; k++)
        if (x > Sum[k])
            break;
    x = x - Sum[k];
    for (i = n - k, j = 1; i <= n - 1; i++, j++)
        ans[j] = i;
    for (i = 1; i <= n - k - 1; i++, j++)
        ans[j] = i;
    ans[n] = n;
    i = 1;
    while (x--)
    {
        swap(ans[i], ans[i + 1]);
        i++;
    }
    for (i = 1; i < n; i++)
        printf("%d ", ans[i]);
    printf("%d\n", ans[n]);
    printf("%lf\n",(double)clock()/CLOCKS_PER_SEC);
    //while(1);
}