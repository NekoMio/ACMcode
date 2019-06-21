#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
template<typename _Tp>
inline _Tp read()
{
    _Tp x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 55;
// 1594324 -> 3^13 + 1
const int MX = 1594322, hed = 0;
long long f[2][MX + 2][2];
int a[MAXN], bin[15];
int XX[MX], Y[MX];
int id[8193][8193], cnt;
void pre()
{
    for (int i = 0; i <= 8191; i++)
    {
        int j = (~i) & 8191;
        for (int k = j; ; k = (k - 1) & j)
        {
            Y[cnt] = i, XX[cnt] = k;
            id[i][k] = cnt++;
            if (!k) break;
        }
    }
}
int main()
{
    int n = read<int>();
    for (int i = 1; i <= n; i++)
        a[i] = read<int>();
    pre();
    f[0][id[8191][0]][0] = 1;
    int now = 0;
    for (int i = 1; i <= n; i++)
    {
        now = now ^ 1;
        memset (f[now], 0, sizeof (f[now]));
        for (int j = 0; j < cnt; j++)
        {
            for (int k = 0; k <= 1; k++)
            {
                int y = Y[j], xx = XX[j];
                int x;
                if (k) x = xx | y;
                else x = xx;
                f[now][j][k] += f[now ^ 1][j][k];
                x = x ^ a[i], y = y & a[i];
                x = x & (~y);
                f[now][id[y][x]][k ^ 1] += f[now ^ 1][j][k];
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i <= 8191; i++)
        ans += f[now][id[i][0]][1];
    ans += f[now][id[0][0]][0];
    printf ("%lld\n", ans);
    // while (1);
}