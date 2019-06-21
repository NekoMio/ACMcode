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
const int MAXN = 105;
int a[MAXN], b[MAXN];
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
        b[i] = a[i] = read();
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;
    int Ans = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
        {
            swap(a[i], a[j]);
            int Sum = 0;
            for (int k = 1; k <= n; k++)
                for (int l = 1; l < k; l++)
                    if (a[l] > a[k])
                        Sum++;
            swap(a[i], a[j]);
            Ans = min(Ans, Sum + 1);
        }
    int Sum = 0;
    for (int k = 1; k <= n; k++)
        for (int l = 1; l < k; l++)
            if (a[l] > a[k])
                Sum++;
    Ans = min(Ans, Sum);
    printf ("%d\n", Ans);
}