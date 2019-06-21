#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 620005;
const int MOD = 1e9 + 9;
int a[N];
int main()
{
    int n, d;
    scanf ("%d%d", &n, &d);
    for (int i = 1; i <= n; i++)
        scanf ("%d", &a[i]);
    sort(a + 1, a + n + 1);
    long long ans = 1;
    for (int i = 1, j = 1; i <= n; i++)
    {
        while (j <= n && a[j] < a[i] - d) j++;
        ans = ans * (i - j + 1) % MOD;
    }
    printf ("%lld", ans);
}