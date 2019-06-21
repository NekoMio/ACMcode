#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
int comp(int a, int b)
{
    return a > b;
}
using namespace std;
int pre[10005], front[1000005];
int in[10005];
int a[10005], b[10005];
int n, block;
void build(int x)
{
    for (int i = (x - 1) * block + 1; i <= min(x * block, n); i++)
    {
        pre[i] = b[i];
    }
    sort(pre + (x - 1) * block + 1, pre + min(x * block + 1, n + 1));
}
void rebuild(int k, int x)
{
    for (int i = 1; i <= n; i++)
        front[a[i]] = 0;
    a[k] = x;
    for (int i = 1; i <= n; i++)
    {
        int ls = b[i];
        b[i] = front[a[i]];
        if (ls != b[i])
            build(in[i]);
        front[a[i]] = i;
    }
}
int query(int c, int x)
{
    int l = (x - 1) * block + 1, r = min(n, x * block);
    int head = l;
    while (l <= r)
    {
        int m = (l + r) >> 1;
        if (pre[m] < c)
            l = m + 1;
        else
            r = m - 1;
    }
    return l - head;
}
int Query(int l, int r)
{
    int ans = 0;
    if (in[l] == in[r])
    {
        for (int i = l; i <= r; i++)
            if (b[i] < l)
                ans++;
    }
    else
    {
        for (int i = l; i <= min(block * in[l], n); i++)
            if (b[i] < l)
                ans++;
        for (int i = block * (in[r] - 1) + 1; i <= r; i++)
            if (b[i] < l)
                ans++;
    }
    for (int i = in [l] + 1; i < in[r]; i++)
        ans += query(l, i);
    return ans;
}
int main()
{
    //freopen("nt2011_color.in","r",stdin);
    //freopen("nt2011_color.out","w",stdout);
    //freopen("1.in", "r", stdin);
    int m;
    scanf("%d%d", &n, &m);
    block = sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        b[i] = front[a[i]];
        front[a[i]] = i;
        in[i] = (i - 1) / block + 1;
    }
    int tot = in[n];
    for (int i = 1; i <= tot; i++)
        build(i);
    char s[10];
    int l, r;
    while (m--)
    {
        scanf("%s", s);
        if (s[0] == 'Q')
        {
            scanf("%d%d", &l, &r);
            printf("%d\n", Query(l, r));
        }
        else
        {
            scanf("%d%d", &l, &r);
            rebuild(l, r);
        }
    }
}