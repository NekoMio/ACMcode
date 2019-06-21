#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long a[20005], c[20005];
const long long mod = 2147483647;
int main()
{
    int n;
    int t = 0;
    while (scanf("%d", &n) != EOF)
    {
        memset(a, 0, sizeof(a));
        for (int i = 1; i <= n; i++)
        {
            scanf("%lld", a + i);
            c[i] = a[i];
        }
        sort(a + 1, a + n + 1);
        int cnt = unique(a + 1, a + n + 1) - a - 1;
        if (cnt == 1) 
        {
            printf("Case #%d: %d\n", ++t, -1);
            continue;
        }
        for (int i = cnt + 1; i <= cnt << 1; i++) a[i] = a[i - cnt];
        int ans = 0;
        a[0] = a[cnt];
        for (int i = 1; i <= n; i++)
        {
            int d = lower_bound(a + 1, a + cnt + 1, c[i]) - a;
            if(((a[d - 1] + c[i]) % mod) == a[d + 1]) ans++;
        }
        printf("Case #%d: %d\n", ++t, ans);
    }
}