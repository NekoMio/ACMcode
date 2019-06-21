#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 20010;
int buc[MAXN], wa[MAXN], wb[MAXN], n;
int r[MAXN], sa[MAXN], Rank[MAXN], height[MAXN];
void getheight(int n)
{
    int i, j, k = 0;
    for (i = 0; i < n; i++)
        Rank[sa[i]] = i;
    for (i = 0; i < n; height[Rank[i++]] = k)
        for (k ? k-- : 0, j = sa[Rank[i] - 1]; r[i + k] == r[j + k]; k++)
            ;
    return;
}
bool cmp(int *c, int a, int b, int d)
{
    return c[a] == c[b] && c[a + d] == c[b + d];
}
void da(int n, int m = 320)
{
    // for(int i=0;i<n;i++)printf("%d  %d\n",i,r[i]);
    int i, j, p, *x = wa, *y = wb, *t;
    for (i = 0; i < m; i++)
        buc[i] = 0;
    for (i = 0; i < n; i++)
        buc[x[i] = r[i]]++;
    for (i = 1; i < m; i++)
        buc[i] += buc[i - 1];
    for (i = n - 1; ~i; i--)
        sa[--buc[x[i]]] = i;
    for (j = 1, p = 1; p < n; j *= 2, m = p)
    {
        for (i = n - j, p = 0; i < n; i++)
            y[p++] = i;
        for (i = 0; i < n; i++)
            if (sa[i] >= j)
                y[p++] = sa[i] - j;
        for (i = 0; i < m; i++)
            buc[i] = 0;
        for (i = 0; i < n; i++)
            buc[x[y[i]]]++;
        for (i = 1; i < m; i++)
            buc[i] += buc[i - 1];
        for (i = n - 1; ~i; i--)
            sa[--buc[x[y[i]]]] = y[i];
        for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
    }
    // for(int i=0;i<n;i++)
    //     printf("%d  %d\n",i,sa[i]);
    getheight(n);
    return;
}
bool Judge(int mid)
{
    int Min = 0x3f3f3f3f, Max = -0x3f3f3f3f;
    for (int i = 2; i <= n; i++)
    {
        if (height[i] < mid)
            Min = 0x3f3f3f3f, Max = -0x3f3f3f3f;
        else
        {
            Min = min(Min, min(sa[i - 1], sa[i]));
            Max = max(Max, max(sa[i - 1], sa[i]));
            if (Max - Min > mid)
                return 1;
        }
    }
    return 0;
}
int a[MAXN];
int main()
{
    while (~scanf("%d", &n) && n)
    {
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);
        n--;
        for (int i = 0; i < n; i++)
            r[i] = a[i + 1] - a[i] + 88;
        r[n] = 0;
        da(n + 1);
        int l = 0, r = (n >> 1) + 1, ans = 0;
        while (l < r)
        {
            int m = l + r >> 1;
            if(Judge(m))
                ans = m, l = m + 1;
            else
                r = m;
        }
        if (ans >= 4) printf("%d\n", ans + 1);
        else printf("0\n");
    }
}