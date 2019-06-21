#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1005;
double p1[MAXN][MAXN], p2[MAXN][MAXN], p3[MAXN][MAXN];
// dp[i][j]=p2[i][j]*dp[i][j+1]/(1-p1[i][j])+p3[i][j]*dp[i+1][j]/(1-p1[i][j])+2/(1-p1[i][j]);
double f[MAXN][MAXN];
int main()
{
    int R, C;
    while (scanf ("%d%d", &R, &C) != EOF)
    {
        memset (f, 0, sizeof (f));
        for (int i = 1; i <= R; i++)
            for (int j = 1; j <= C; j++)
                scanf ("%lf%lf%lf", &p1[i][j], &p2[i][j], &p3[i][j]);
        f[R][C] = 0;
        for (int i = R; i >= 1; i--)
        {
            for (int j = C; j >= 1; j--)
            {
                if (i == R && j == C) continue;
                if (fabs(1 - p1[i][j]) < 1e-9) continue;
                f[i][j] = p2[i][j] * f[i][j + 1] / (1 - p1[i][j]) + p3[i][j] * f[i + 1][j] / (1 - p1[i][j]) + 2 / (1 - p1[i][j]);
            }
        }
        printf ("%.3f\n", f[1][1]);
    }
}
