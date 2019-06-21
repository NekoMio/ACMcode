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
const int MAXN = 1005;
int Weight[105][MAXN], value[105][MAXN];
int p[35], w[35];
int f[105][MAXN];
int len = 0;
int main()
{
    while (1)
    {
        int n = read(), W = read();
        if (n == -1 && W == -1) break;
        memset (f, 0, sizeof (f));
        memset (p, 0, sizeof (p));
        memset (w, 0, sizeof (w));
        memset (Weight, 0, sizeof (Weight));
        memset (value, 0, sizeof (value));
        len = 0;
        for (int i = 1; i <= n; i++)
        {
            int x = read();
            int j = 0;
            while (!(x & 1)){j++, x >>= 1;}
            Weight[j][++p[j]] = x;
            w[j] += x;
            len = max(len, j);
            value[j][p[j]] = read();
        }
        for (int i = 0; i <= len; i++)
            for (int j = 1; j <= p[i]; j++)
                for (int k = w[i]; k >= Weight[i][j]; k--)
                    f[i][k] = max(f[i][k], f[i][k - Weight[i][j]] + value[i][j]);
        while (W >> len) len++; 
        len--;
        for (int i = 1; i <= len; i++)
        {
            w[i] += w[i - 1] + 1 >> 1;
            for (int j = w[i]; j >= 0; j--)
                for (int k = 0; k <= j; k++)
                {
                    f[i][j] = max(f[i][j], f[i][j - k] + f[i - 1][min(w[i - 1], (k << 1) | ((W >> (i - 1)) & 1))]);
                }
        }
        printf ("%d\n", f[len][1]);
    }
}