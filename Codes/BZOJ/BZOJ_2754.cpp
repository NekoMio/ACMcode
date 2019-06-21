#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int _ = 10000;
const int MAXN = 301005;
int buc[MAXN], wa[MAXN], wb[MAXN], N;
int r[MAXN], sa[MAXN], Rank[MAXN], height[MAXN];
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
void da(int n, int m = 100000)
{
    int i, j, p, *x = wa, *y = wb, *t;
    for (i = 0; i < m; i++) buc[i] = 0;
    for (i = 0; i < n; i++) buc[x[i] = r[i]]++;
    for (i = 1; i < m; i++) buc[i] += buc[i - 1];
    for (int i = n - 1; ~i; i--)
        sa[--buc[x[i]]] = i;
    for (j = 1, p = 1; p < n; j *= 2, m = p)
    {
        for (i = n - j, p = 0; i < n; i++) y[p++] = i;
        for (i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
        for (i = 0; i < m; i++) buc[i] = 0;
        for (i = 0; i < n; i++) buc[x[y[i]]]++;
        for (i = 1; i < m; i++) buc[i] += buc[i - 1];
        for (i = n - 1; ~i; i--) sa[--buc[x[y[i]]]] = y[i];
        for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
    }
    GetHeight(n);
    return;
}
struct data
{
    int p, l;
}a[50005];
int vis[MAXN];
int ans[MAXN];
int cat[MAXN];
int main()
{
    int n = read(), m = read();
    for (int i = 1; i <= n; i++)
    {
        int l = read();
        for (int j = 0; j < l; j++)
            r[N++] = read(), cat[N - 1] = i;
        r[N++] = ++_;
        l = read();
        for (int j = 0; j < l; j++)
            r[N++] = read(), cat[N - 1] = i;
        r[N++] = ++_;
    }
    for (int i = 1; i <= m; i++)
    {
        a[i].p = N;
        a[i].l = read();
        for (int j = 0; j < a[i].l; j++)
            r[N++] = read();
        if (i != m) r[N++] = ++_;
    }
    da(N + 1, _ + 1);
    for (int i = 1; i <= m; i++)
    {
        int Sum = 0, p = Rank[a[i].p];
        for (int j = p; j > 1 && height[j] >= a[i].l; j--)
            if (cat[sa[j - 1]] && vis[cat[sa[j - 1]]] != i)
                Sum++, ans[cat[sa[j - 1]]]++, vis[cat[sa[j - 1]]] = i;
        p = Rank[a[i].p];
        for (int j = p + 1; j <= N && height[j] >= a[i].l; j++)
            if (cat[sa[j]] && vis[cat[sa[j]]] != i)
                Sum++, ans[cat[sa[j]]]++, vis[cat[sa[j]]] = i;
        printf ("%d\n", Sum);
    }
    for (int i = 1; i <= n; i++)
        printf ("%d%c", ans[i], " \n"[i == n]);
    // while (1);
}