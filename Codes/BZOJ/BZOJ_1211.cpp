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
const int MAXN = 151;
int D[MAXN];
int cnt[MAXN];
int Update(int a, int c)
{
    int x = 2;
    while (a > 1)
    {
        while (a % x == 0) a /= x, cnt[x] += c;
        x++;
    }
}
int main()
{
    int n = read();
    if (n == 0) return printf ("1\n"), 0;
    int Sum = 0;
    for (int i = 1; i <= n; i++)
    {
        D[i] = read();
        Sum += D[i];
        if (D[i] == 0 && n > 1) return printf ("0\n"), 0;
    }
    if (Sum != 2 * n - 2)
        return printf ("0\n"), 0;
    if (n == 1) return printf ("1\n"), 0;
    for (int i = 1; i <= n - 2; i++)
        Update(i, 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= D[i] - 1; j++)
            Update(j, -1);
    long long ans = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= cnt[i]; j++)
            ans *= i;
    printf ("%lld\n", ans);
}