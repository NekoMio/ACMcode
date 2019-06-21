#include <cstdio>
#include <cstring>
#include <algorithm>
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 100005;
long long Sum[MAXN];
int k, n;
void Update(int x, int c)
{
    x++;
    for (int i = x; i <= k; i += (i & -i))
        Sum[i] += c;
}
void ADD(int l, int r)
{
    if (l == k) l = 0, r -= k;
    Update(l, 1);
    if (r == k - 1) return;
    if (r < k) 
    {
        Update(r + 1, -1);
        return;
    }
    r -= k;
    Update(0, r / k + 1);
    r %= k;
    if (r == k - 1) return;
    if (r < k) Update(r + 1, -1);
}
long long Query(int x)
{
    x++;
    long long ans = 0;
    for (int i = x; i > 0; i -= (i & -i))
        ans += Sum[i];
    return ans;
}
int main()
{
    // freopen ("exclaim.in", "r", stdin);
    // freopen ("exclaim.out", "w", stdout);
    int T = read();
    for (int t = 1; t <= T; t++)
    {
        n = read(), k = read();
        memset (Sum, 0, sizeof (Sum));
        long long ans = 0;
        for (int i = 1; i <= n; i++)
        {
            int t = 1ll * i * i % k;
            ADD(t + 1, t + i);
            ans += Query(1ll * t * i % k);
        }
        printf ("Case %d: %lld\n", t, ans);
    }
}