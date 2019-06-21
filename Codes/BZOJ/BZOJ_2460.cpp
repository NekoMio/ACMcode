#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline long long read()
{
    long long x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1005;
struct data
{
    long long a, b;
    bool operator < (const data &c) const 
    {
        return b > c.b;
    }
}a[MAXN];
long long p[64];
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)    
        a[i].a = read(), a[i].b = read();
    sort(a + 1, a + n + 1);
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 63; j >= 0; j--)
        {
            if (a[i].a >> j)
            {
                if (!p[j])
                {
                    p[j] = a[i].a;
                    break;
                }
                else a[i].a ^= p[j];
            }
        }
        if (a[i].a) ans += a[i].b;
    }
    printf ("%lld\n", ans);
}