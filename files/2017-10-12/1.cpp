#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct data
{
    int l, r;
    bool operator < (const data &a) const 
    {
        return l == a.l ? r < a.r : l < a.l;
    }
}a[2005];
int ans = 0;
int cnt[50];
int main()
{
    int n;
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf ("%d%d", &a[i].l, &a[i].r);
    sort(a + 1, a + n + 1);
    int N = (1 << n) - 1;
    printf ("%d", ans);
    while (1);
}