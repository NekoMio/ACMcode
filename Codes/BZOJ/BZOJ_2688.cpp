#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int a[105];
double h[150];
double g[350][350], f[350][350];
int main()
{
    int n = read(), m = 0;
    for (int i = 1; i <= n; i++)
        a[i] = read(), m = max(m, a[i]);
    h[0] = 1;
    for (int i = 1; i <= m; i++)
        h[i] = h[i - 1] * (4 * i - 2) / (i + 1);
    g[1][0] = 1;
    for (int i = 2; i <= m; i++)
    {
        for (int j = 0; j <= 127; j++) g[i][j + 1] += h[i - 1] * 2 * g[i - 1][j];
        for (int j = 1; j < i - 1; j++)
        {
            int k = i - j - 1;
            for (int x = 0; x <= 127; x++)
                for (int y = 0; y <= 127; y++)
                    g[i][(x + 1) ^ (y + 1)] += h[j] * g[j][x] * h[k] * g[k][y];
        }
        for (int j = 0; j <= n - 1; j++) g[i][j] /= h[i];
    }
    for (int i = 0; i <= 127; i++) f[1][i] = g[a[1]][i];
    for (int i = 2; i <= n; i++)
        for (int j = 0; j <= 127; j++)
            for (int k = 0; k <= 127; k++)
                f[i][j ^ k] += f[i - 1][j] * g[a[i]][k];
    printf ("%.6f\n", 1.0 - f[n][0]);
}