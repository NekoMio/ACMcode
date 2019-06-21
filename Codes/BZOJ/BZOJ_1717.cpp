#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 2000005;
int buc[MAXN], wa[MAXN], wb[MAXN], n, K;
int r[MAXN], sa[MAXN], Rank[MAXN], height[MAXN];
void GetHeight(int n)
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
void da(int n, int m = 1000000)
{
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
    GetHeight(n);
    return;
}
bool Judge(int mid)
{
    int l = 0;
    for (int i = 2; i <= n; i++)
    {
        if (height[i] < mid)
            l = 0;
        else
        {
            l++;
            if(l + 1 >= K) return 1;
        }
    }
    return 0;
}
int main()
{
    scanf("%d%d", &n, &K);
    for (int i = 0; i < n; i++)
        scanf("%d", &r[i]);
    da(n + 1);
    int l = 0, r = (n >> 1) + 1, ans = 0;
    while (l < r)
    {
        int mid = l + r >> 1;
        if (Judge(mid))
            ans = mid, l = mid + 1;
        else
            r = mid;
    }
    printf("%d", ans);
}