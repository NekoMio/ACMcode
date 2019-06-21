#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long Sum[2][300005];
#define lowbit(_) ((_) & (-_))
int n;
void add(int p, int x, int w)
{
    for (int i = x; i <= n; i += lowbit(i))
        Sum[p][i] += w;
}
long long Gsum(int p, int x)
{
    long long ans = 0;
    for (int i = x; i; i -= lowbit(i))
        ans += Sum[p][i];
    return ans;
}
int a[300005], Hash[300005];
int main()
{
    scanf("%d", &n);
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        Hash[i] = a[i];
    }
    sort(Hash + 1, Hash + n + 1);
    int tot = unique(Hash + 1, Hash + n + 1) - Hash - 1;
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(Hash + 1, Hash + tot + 1,a[i]) - Hash;
    for (int i = 1; i <= n; i++)
    {
        int x = Gsum(0, a[i] - 1);
        add(0, a[i], 1);
        ans += Gsum(1, a[i] - 1);
        add(1, a[i], x);
    }
    printf("%lld\n", ans);
}