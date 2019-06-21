#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
int a[500005], b[500005];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    int i = 1, l, r;
    int ans = 0;
    while (i <= n)
    {
        while (i <= n && a[i] == a[i + 1])
        {
            b[i] = a[i];
            i++;
        }
        l = i;
        while (i <= n && a[i] != a[i + 1])
            i++;
        r = i;
        int len = (r - l + 1);
        if (len & 1)
            for (int j = l; j <= r; j++)
                b[j] = a[l];
        else
            for (int j = 1; j * 2 <= len; j++)
                b[l + j - 1] = a[l], b[r - j + 1] = a[r];
        ans = max(ans, (len - 1) / 2);
    }
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++)
        printf("%d ", b[i]);
    //while(1);
}
