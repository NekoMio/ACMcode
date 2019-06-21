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
const int MAXN = 705;
int n;
int a[MAXN], b[MAXN];
int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
        b[i] = a[i] = read();
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;
    int Sum = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < i; j++)
            if (a[j] > a[i])
                Sum++;
    int Ans = Sum;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
        {
            int t = 0;
            for (int k = 1; k < i; k++) if (a[k] > a[i]) t++;
            for (int k = i + 1; k <= n; k++) if (a[i] > a[k]) t++;
            for (int k = 1; k < j; k++) if (a[k] > a[j]) t++;
            for (int k = j + 1; k <= n; k++) if (a[j] > a[k]) t++;
            if (a[i] > a[j]) t--;
            int tmp = Sum - t;
            swap(a[i], a[j]);
            t = 0;
            for (int k = 1; k < i; k++) if (a[k] > a[i]) t++;
            for (int k = i + 1; k <= n; k++) if (a[i] > a[k]) t++;
            for (int k = 1; k < j; k++) if (a[k] > a[j]) t++;
            for (int k = j + 1; k <= n; k++) if (a[j] > a[k]) t++;
            if (a[i] > a[j]) t--;
            swap(a[i], a[j]);
            tmp = tmp + t;
            Ans = min(Ans, tmp + 1);
        }
    printf ("%d\n", Ans);
}