#include <cstdio>
#include <cstring>
#include <algorithm>
#include <deque>
using namespace std;
#define LL long long
LL f[55], Sum[55];
int a[55];
bool mark[55];
int main()
{
    LL n, k;
    scanf("%lld%lld", &n, &k);
    f[0] = f[1] = f[2] = 1;
    Sum[0] = 1, Sum[1] = 2, Sum[2] = 3;
    for (int i = 3; i <= n; i++)
    {
        f[i] = f[i - 1] + f[i - 2];
        Sum[i] = Sum[i - 1] + f[i];
    }
    for (int i = 1; i <= n; i++)
        a[i] = i;
    while (k > 1)
    {
        int j = lower_bound(Sum, Sum + n + 1, k) - Sum -1;
        k -= Sum[j];
        mark[n - j - 1] = mark[n - j] = 1;
    }
    for (int i = 1; i <= n; i++)
        if (mark[i] && mark[i + 1])
            mark[i] = mark[i + 1] = 0, swap(a[i], a[i + 1]);
    for (int i = 1; i <= n; i++)
        printf("%d ", a[i]);
    //while (1)
    ;
}
