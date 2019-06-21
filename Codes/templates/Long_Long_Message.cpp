#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 222222;
int buc[MAXN], wa[MAXN], wb[MAXN];
int sa[MAXN], r[MAXN], height[MAXN], Rank[MAXN];
void GetHeight(int n)
{
    int i, j, k = 0;
    for (i = 0; i < n; i++)
        Rank[sa[i]] = i;
    for (i = 0; i < n; height[Rank[i++]] = k)
        for (k ? k-- : 0, j = sa[Rank[i] - 1]; r[i + k] == r[j + k]; k++);
    return;
}
bool cmp(int *c, int a, int b, int d)
{
    return c[a] == c[b] && c[a + d] == c[b + d];
}
void da(int n, int m = 130)
{
    int i, j, p, *x = wa, *y = wb, *t;
    for (i = 0; i < m; i++) buc[i] = 0;
    for (i = 0; i < n; i++) buc[x[i] = r[i]]++;
    for (i = 1; i < m; i++) buc[i] += buc[i - 1];
    for (i = n - 1; ~i; i--) sa[--buc[x[i]]] = i;
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
char s[100005];
int main()
{
    scanf("%s", s);
    int l1 = strlen(s);
    for (int i = 0; i < l1; i++)
        r[i] = s[i];
    r[l1] = '$';
    scanf("%s", s);
    int l2 = strlen(s);
    for (int i = 0; i < l2; i++)
        r[i + l1 + 1] = s[i];
    int n = l1 + l2 + 1;
    da(n + 1);
    // for (int i = 1; i <= n; i++)
    //     printf("%d ", sa[i]);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if((sa[i] > l1 && sa[i - 1] < l1) || (sa[i] < l1 && sa[i - 1] > l1))
            ans = max(ans, height[i]);
    }
    printf("%d", ans);
    // while(1);
}