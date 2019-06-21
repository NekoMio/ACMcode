#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 60005;
int buc[MAXN], wa[MAXN], wb[MAXN];
int r[MAXN], sa[MAXN], Rank[MAXN];
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
            if(sa[i] >= j)
                y[p++] = sa[i] - j;
        for (i = 0; i < m; i++) buc[i] = 0;
        for (i = 0; i < n; i++) buc[x[y[i]]]++;
        for (i = 1; i < m; i++) buc[i] += buc[i - 1];
        for (i = n - 1; ~i; i--) sa[--buc[x[y[i]]]] = y[i];
        for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1: p++;
    } 
    for (i = 0; i < n; i++) Rank[sa[i]] = i;
}
int main()
{
    // freopen("bclgold.in", "r", stdin);
    // freopen("bclgold.out", "w", stdout);
    int n; char c[2];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", c);
        r[i] = r[2 * n - i - 1] = c[0];
    }
    da(2 * n + 1);
    int l = 0, R = n;
    for (int i = 1; i <= n; i++)
    {
        if(Rank[l] > Rank[R])
            printf("%c", r[R++]);
        else 
            printf("%c", r[l++]);
        if(i % 80 == 0) putchar('\n');
    }
    //while(1);
}