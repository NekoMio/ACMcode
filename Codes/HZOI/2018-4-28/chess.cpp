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
int Calc(long long x)
{
    if (x < 0) return 0;
    int ans = 0;
    while (x)
    {
        if (!(x & 1))
        {
            ans++;
            x--;
        }
        x >>= 1;
    }
    return ans;
}
long long a[100];
int main()
{
    long long n = read(), m = read();
    for (int i = 1; i <= m; i++)
        a[i] = read();
    sort(a + 1, a + m + 1);
    if (m)
    {
        int ans = 0;
        if (a[1] != 1) ans++;
        if (a[m] != n) ans++;
        a[0] = 1;
        a[++m] = n;
        for (int i = 1; i <= m; i++)
            ans = ans + Calc(a[i] - a[i - 1] - 1);
        printf ("%d\n", ans);
    }
    else
    {
        if (n == 0) printf ("%d\n", 0);
        else if (n == 1) printf ("%d\n", 1);
        else printf ("%d\n", Calc(n - 2) + 2);
    }
}
