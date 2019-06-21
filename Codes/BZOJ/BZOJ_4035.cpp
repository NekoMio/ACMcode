#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int N = 100005;
int c[2][N], f[N];
int n, m;
#define nxt(i, j) ((i == j) ? j + 1 : j / (j / (i + 1)))
void Pre()
{
    for (int i = 1; i <= n; i = nxt(i, n))
    {
        int now = 0, cnt = 0;
        for (int j = 2; j <= i; j = nxt(j, i))
        {
            int x = i / j;
            int t = (x > m) ? c[1][n / x] : c[0][x];
            f[now ^ t] = i;
            if ((i / x - i / (x + 1)) & 1) now ^= t;
        }
        now = 1;
        while (f[now] == i) now++;
        if (i > m) c[1][n / i] = now;
        else c[0][i] = now;
    }
}
int main()
{
    n = read(), m = sqrt(n);
    int t = read();
    Pre();
    while (t--)
    {
        int cnt = read(), ans = 0;
        for (int i = 1; i <= cnt; i++)
        {
            int x = n / read();
            ans ^= ((x > m) ? c[1][n / x] : c[0][x]);
        }
        puts(ans ? "Yes" : "No");
    }
}