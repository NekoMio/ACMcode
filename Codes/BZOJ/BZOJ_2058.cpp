#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int c[100005], n;
#define lowbit(_) ((_) & (-_))
void add(int x, int add)
{
    for (int i = x; i <= n; i += lowbit(i))
        c[i] += add;
}
int Query(int x)
{
    int ans = 0;
    for (int i = x; i >= 1; i -= lowbit(i))
        ans += c[i];
    return ans;
}
int a[100005], pos[100005];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        pos[a[i]] = i;
    }
    long long Sum = 0;
    for (int i = n; i >= 1; i--)
    {
        Sum += Query(a[i] - 1);
        add(a[i], 1);
    }
    long long ans = Sum;
    for (int i = 1; i < n; i++)
    {
        Sum = Sum - pos[i] + 1 + n - pos[i];
        ans = min(ans, Sum);
    }
    printf("%lld", ans);
}