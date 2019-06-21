#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100005;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int a[MAXN];
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    sort(a + 1, a + n + 1);
    long long ans = 0;
    for (int i = 1; i + 2 <= n; i += 2)
        ans = ans + 1ll * (a[i] - a[i + 2]) * (a[i] - a[i + 2]);
    ans = ans + 1ll * (a[1] - a[2]) * (a[1] - a[2]);
    ans = ans + 1ll * (a[n] - a[n - 1]) * (a[n] - a[n - 1]);
    for (int i = 2; i + 2 <= n; i += 2)
        ans = ans + 1ll * (a[i] - a[i + 2]) * (a[i] - a[i + 2]);
    printf ("%lld\n", ans);
}