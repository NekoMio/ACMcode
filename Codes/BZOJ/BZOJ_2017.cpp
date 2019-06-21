#include <cstdio>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int a[2005];
int f[2005][2005];
int main()
{
    int n = read();
    for (int i = n; i >= 1; i--) a[i] = read();
    for (int i = 1; i <= n; i++) a[i] += a[i - 1];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            f[i][j] = max(f[i][j - 1], a[i] - f[i - j][min(i - j, j * 2)]);
    printf ("%d\n", f[n][2]);
}