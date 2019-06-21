#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
const int MAXN = 1000205;
int a[MAXN], size[MAXN], len[MAXN];
char s[MAXN];
signed main()
{
    int n;
    scanf("%lld", &n);
    scanf ("%s", s + 1);
    int cnt = 2;
    for (int i = 1; i <= n; i++)
    {
        a[(i << 1) - 1] = (s[i] - '0') ^ (i & 1);
        a[i << 1] = cnt;
    }
    n <<= 1;
    for (int i = 1; i <= n; i++) size[i] = size[i - 1] + (a[i] <= 1 && a[i] >= 0);
    len[1] = 1;
    int Max = 1;
    for (int i = 2; i <= n; i++)
    {
        len[i] = 1;
        if (Max + len[Max] - 1 >= i) len[i] = min(max(1ll, len[(Max << 1) - i]), Max + len[Max] - i);
        while (i - len[i] > 0 && i + len[i] <= n && a[i - len[i]] == a[i + len[i]]) len[i]++;
        if (Max + len[Max] < i + len[i]) Max = i;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (a[i] == 2)
            ans += size[i] - size[i - len[i]];
    printf ("%lld\n", ans);
}