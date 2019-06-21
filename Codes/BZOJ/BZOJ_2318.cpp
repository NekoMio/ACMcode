#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
double f[200], g[200];
int main()
{
    int t = 0;
    scanf ("%d", &t);
    while (t--)
    {
        int n;
        double q, p;
        scanf ("%d%lf%lf", &n, &p, &q);
        n = min(n, 100);
        f[0] = 0, g[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            if (f[i - 1] > g[i - 1]) p = 1 - p, q = 1 - q;
            g[i] = (q * f[i - 1] + (1 - q) * p * g[i - 1]) / (q - q * p + p);
            f[i] = (p * g[i - 1] + (1 - p) * q * f[i - 1]) / (q - q * p + p);
            if (f[i - 1] > g[i - 1]) p = 1 - p, q = 1 - q;
        }
        printf ("%.6lf\n", f[n]);
    }
}