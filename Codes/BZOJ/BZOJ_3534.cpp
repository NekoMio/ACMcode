#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const double eps = 1e-10;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

int n;
double g[55][55], a[55][55];
double gauss()
{
    n--;
    double ans = 1;
    for (int i = 1; i <= n; i++)
    {
        int tmp = i;
        for (int j = i + 1; j <= n; j++)
            if (fabs(a[j][i]) > fabs(a[tmp][i])) 
                tmp = j;
        if (tmp != i)
        {
            for (int j = i; j <= n; j++)
                swap(a[tmp][j], a[i][j]);
            ans *= -1;
        }
        for (int j = i + 1; j <= n; j++)
        {
            double t = a[j][i] / a[i][i];
            for (int k = i; k <= n; k++)
                a[j][k] -= t * a[i][k];
        }
        ans *= a[i][i];
    }
    return ans;
}
int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf ("%lf", &g[i][j]);
    double tmp = 1;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
        {
            if (g[i][j] < eps) g[i][j] = eps;
            if (g[i][j] > 1 - eps) g[i][j] = 1 - eps;
            tmp *= (1 - g[i][j]);
            g[i][j] = g[i][j] / (1 - g[i][j]);
            a[i][i] += g[i][j], a[j][j] += g[i][j];
            a[i][j] = -g[i][j], a[j][i] = -g[i][j];
        }
    printf ("%.10f\n", tmp * gauss());
}