#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[100005];
int last[100005];
void Update(int x, int id)
{
    if (x < 0) return;
    if (!x) return last[0] = id, void(0);
    for (int i = 1; i * i <= x; i++)
    {
        if (x % i == 0)
        {
            last[i] = id;
            if (i * i != x)
                last[x / i] = id;
        }
    }
}
int main()
{
    int n, K;
    scanf ("%d%d", &n, &K);
    long long ans = 0;
    int Last = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf ("%d", &a[i]);
        if (a[i] > K) Last = max(max(last[a[i]], last[0]), Last);
        ans += i - Last;
        Update(a[i] - K, i);
    }
    printf ("%lld", ans);
}