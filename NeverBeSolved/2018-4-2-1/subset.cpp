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
const int MAXN = 2e5 + 5;
int a[MAXN];
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    sort(a + 1, a + n + 1);
    double ans = 0;
    for (int i = 1; i <= n; i++)
    {
        double lastans = -1e60;
        double Sum = a[i];
        for (int len = 1; len <= i - 1; len++)
        {
            Sum += a[n - len + 1];
            Sum += a[i - len];
            if (1.0 * Sum / (len * 2 + 1) - a[i] < lastans) break;
            else
            {
                lastans = (1.0 * Sum / (len * 2 + 1) - a[i]);
                ans = max(ans, lastans);
            }
        }
    }
    printf ("%.5f\n", ans);
}