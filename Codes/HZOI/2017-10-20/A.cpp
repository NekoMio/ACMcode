#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int read()
{
    int a = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9') {a = a * 10 + ch - '0'; ch = getchar();}
    return a * f;
}
struct data
{
    int yn, ym, zn, zm;
    data()
    {
        yn = 0, ym = 0x3f3f3f3f;
        zn = 0, zm = 0x3f3f3f3f;
    }
}a[100005], st[400005][18];
void Merge(data &ans, data a, data b)
{
    ans.yn = max(a.yn, b.yn);
    ans.ym = min(a.ym, b.ym);
    ans.zn = max(a.zn, b.zn);
    ans.zm = min(a.zm, b.zm);
}
int x, y, z;
data Query(int l, int r)
{
    int len = r - l + 1;
    int k = 0;
    while ((1 << k) <= len) k++;
    k--;
    data ans;
    Merge(ans, st[l][k], st[r - (1 << k) + 1][k]);
    return ans;
}
bool Judge(int mid)
{
    for (int i = 1; i <= x - mid + 1; i++)
    {
        data now = Query(i, i + mid - 1);
        if (now.zm - now.zn + 1 >= mid && now.ym - now.yn + 1 >= mid) return 1;
    }
    return 0;
}
int main()
{
    x = read(), y = read(), z = read();
    for (int i = 1; i <= x; i++)
    {
        a[i].yn = read(), a[i].zn = read(), a[i].ym = read(), a[i].zm = read();
        st[i][0] = a[i];
    }
    for (int i = 1; i <= 17; i++)
        for (int j = 1; j <= x; j++)
            Merge(st[j][i], st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
    int l = 0, r = min(x, min(z, y)) + 1;
    int ans = 0;
    while (l < r)
    {
        int mid = l + r >> 1;
        if (Judge(mid))
            ans = mid, l = mid + 1;
        else 
            r = mid;
    }
    printf ("%d", ans);
}