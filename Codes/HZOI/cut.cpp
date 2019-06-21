#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
int a[105];
long long Sum[105];
int main()
{
    int n;
    long long k;
    scanf("%d%lld", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        Sum[i] = Sum[i - 1] + a[i];
    }
    k += Sum[n];
    long long ans = 0;
    for (long long i = 1, pos; i <= k / 2 + 1; i = pos + 1)
    {
        pos = k / (k / i);
        long long now = 0;
        for (int j = 1; j <= n; j++)
            now += (a[j] / pos) + (a[j] % pos > 0);
        if (now <= k / pos)
            ans = pos;
    }
    printf("%lld", ans);
}