#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct data
{
    int a, b;
}c[200005];
int n;
int a[100005], b[100005];
bool vis[100005];
void dfs(int rt)
{
    if (vis[rt]) return;
    vis[rt] = 1;
    dfs(b[rt]);
}
bool Judge(int mid)
{
    memcpy (b, a, sizeof (b));
    memset (vis, 0, sizeof (vis));
    for (int i = 1; i <= mid; i++)
        swap(b[c[i].a], b[c[i].b]);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            dfs(i), ans++;
    return n - ans > mid;
}
int main()
{
    // freopen("c.in", "r", stdin);
    // freopen("c.out", "w", stdout);
    n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read() + 1;
    for (int i = 1; i <= 2 * n; i++)
        c[i].a = read() + 1, c[i].b = read() + 1;
    int l = 0, r = n + 1;
    int ans = 0;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (Judge(mid)) l = mid + 1;
        else ans = mid, r = mid - 1;
    }
    printf ("%d\n", ans);
    // while (1);
}