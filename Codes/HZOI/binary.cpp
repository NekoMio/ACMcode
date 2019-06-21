#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct Tree
{
    int ch[2];
    int v;
} Node[100005];
int a[100005], Ind, val[100005], c[100005];
void dfs(int rt)
{
    if (rt)
    {
        dfs(Node[rt].ch[0]);
        a[++Ind] = Node[rt].v;
        dfs(Node[rt].ch[1]);
    }
}
int f[100005], Max[100005];
int tot;
inline int lowbit(int x) { return x & (-x); }
void Update(int x, int val)
{
    for (int i = x; i <= tot; i += lowbit(i))
        Max[i] = max(Max[i], val);
    return;
}
int Query(int x)
{
    int ans = 0;
    for (int i = x; i; i -= lowbit(i))
        ans = max(ans, Max[i]);
    return ans;
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &Node[i].v);
    }
    int fa, d;
    for (int i = 2; i <= n; i++)
    {
        scanf("%d%d", &fa, &d);
        Node[fa].ch[d] = i;
    }
    dfs(1);
    //memset(f, 0x7f, sizeof(f));
    for (int i = 1; i <= n; i++)
    {
        a[i] = a[i] - i;
        c[i] = a[i];
    }
    int ans = 0;
    sort(a + 1, a + n + 1);
    tot = unique(a + 1, a + n + 1) - a - 1;
    for (int i = 1; i <= n; i++)
    {
        int now = lower_bound(a + 1, a + tot + 1, c[i]) - a;
        f[i] = Query(now) + 1;
        Update(now, f[i]);
        ans = max(ans, f[i]);
    }
    printf("%d", n - ans);
    //while(1);
}