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
const int MAXN = 6005;
int n;
int a[MAXN], b[MAXN];
int mp[MAXN][MAXN];
int Calc(int x1, int y1, int x2, int y2)
{
    return mp[x2][y2] - mp[x1 - 1][y2] - mp[x2][y1 - 1] + mp[x1 - 1][y1 - 1] - 2;
}
int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
        b[i] = a[i] = read();
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;
    for (int i = 1; i <= n; i++)
        mp[i][n - a[i] + 1] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            mp[i][j] += mp[i][j - 1];
    for (int j = 1; j <= n; j++)
        for (int i = 1; i <= n; i++)
            mp[i][j] += mp[i - 1][j];
    int Sum = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < i; j++)
            if (a[j] > a[i])
                Sum++;
    int Ans = Sum;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
        {
            if (a[i] < a[j]) continue;
            Ans = min(Ans, Sum - 2 * Calc(i, n - a[i] + 1, j, n - a[j] + 1));
        }
    printf ("%d\n", Ans);
}