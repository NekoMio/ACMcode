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
const int MAXN = 1e5 + 5;
long long a[MAXN];
int n;
long long f[(1 << 18) + 1], S[(1 << 18) + 1];
int cnt[(1 << 18) + 1];
int main()
{
    n = read();
    long long SAME = (1 << 18) - 1;
    for (int i = 1; i <= n; i++) a[i] = read(), SAME = (SAME & a[i]);
    int N = (1 << 18) - 1;
    for (int i = 1; i <= n; i++) a[i] ^= SAME;
    for (int i = 1; i <= n; i++)
    {
        long long t = N ^ a[i];
        for (int j = t; j; j = (j - 1) & t)
            cnt[j] = 1;
    }
    memset (f, 0x3f, sizeof (f));
    for (int i = 1; i <= n; i++) f[a[i]] = a[i];
    for (int i = N; i >= 1; i--) 
        if (f[i] < 0x3f3f3f3f3f3f3f3f)
            for (int j = i; j > 0; j = (j - 1) & i)
                if (cnt[j])
                    f[i ^ j] = min(f[i ^ j], f[i] + (i ^ j));
    printf ("%lld\n", 1ll * SAME * n + f[0]);
}