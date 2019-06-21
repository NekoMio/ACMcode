#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
inline long long read()
{
    long long x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1005;
long long a[MAXN], bc[MAXN], d[MAXN], r[MAXN];
int c[MAXN];
int m;
bool vis[MAXN];
int C[MAXN], top;
void dfs(int rt)
{
    if (vis[rt]) return void();
    vis[rt] = 1;
    C[++top] = rt;
    dfs(d[rt]);
}
long long k;
int main()
{
    // freopen ("frog.in", "r", stdin);
    // freopen ("frog.out", "w", stdout);
    int n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    for (int i = 1; i < n; i++)
        bc[i] = a[i + 1] - a[i];
    for (int i = 1; i < n; i++)
        d[i] = i;
    m = read(), k = read();
    for (int i = 1; i <= m; i++)
    {
        c[i] = read();
        swap(d[c[i] - 1], d[c[i]]);
    }
    for (int i = 1; i < n; i++)
        if (!vis[i])
        {
            top = 0;
            dfs(i);
            int t = k % top;
            for (int i = 1; i <= top; i++)
                r[C[i]] = bc[C[(i + k - 1) % top + 1]];
        }
    for (int i = 1; i <= n; i++)
    {
        if (i != 1) a[i] = a[i - 1] + r[i - 1];
        printf ("%lld\n", a[i]);
    }
    // while (1);
}