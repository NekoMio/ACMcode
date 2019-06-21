#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int N = 300005;
struct data
{
    int l, r, mid;
    bool operator < (const data &a) const
    {
        return l < a.l;
    }
}a[N];
set<int> st;
bool vis[N];
int Sum[N][2], pre[N];
int f[N], g[N];
int main()
{
    int n = read(), t = read();
    int N = 0;
    for (int i = 1; i <= n; i++)
    {
        a[i].l = read();
        a[i].r = read();
        a[i].mid = a[i].l + a[i].r >> 1;
        N = max(a[i].r, N);
        pre[a[i].r] = max(a[i].l, pre[a[i].r]);
    }
    for (int i = 1; i <= n; i++)
        Sum[a[i].mid][0] ++,
        Sum[a[i].mid][1] += a[i].mid;
    for (int i = 1; i <= N; i++)
        Sum[i][0] += Sum[i - 1][0],
        Sum[i][1] += Sum[i - 1][1];
    for (int i = 1; i <= N; i++)
        pre[i] = max(pre[i], pre[i - 1]);    
    f[0] = 0;
    for (int i = 1; i <= N; i++)
    {
        f[i] = f[pre[i - 1]] + 1;
        g[i] = 0x3f3f3f3f;
        for (int j = pre[i - 1]; j < i; j++)
            if (f[j] != f[i] - 1) break;
            else
            {
                int mid = j + i >> 1;
                g[i] = min(g[i], Sum[mid][1] - Sum[(j - 1) < 0 ? 0 : (j - 1)][1] - (Sum[mid][0] - Sum[(j - 1) < 0 ? 0 : (j - 1)][0]) * j \
                                + (Sum[i][0] - Sum[mid][0]) * i - Sum[i][1] + Sum[mid][1] + g[j]);
            }
    }
    printf ("%d\n", f[pre[N]]);
    if (!t) return 0;
    int ans = 0x3f3f3f3f;
    for (int j = pre[N]; j <= N; j++)
        if (f[j] > f[pre[N]]) break;
        else ans = min(ans, Sum[N][1] - Sum[j - 1][1] - (Sum[N][0] - Sum[j - 1][0]) * j + g[j]);
    printf ("%d", ans << 1);
}