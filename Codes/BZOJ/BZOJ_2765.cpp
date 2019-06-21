#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXN = 105;
double v1[MAXN], v2[MAXN];
int n, s;
pair<double, double> Get_k(double a, double b)
{
    if (a < 0) return pair<double, double>(0, b / a);
    else return pair<double, double>(b / a, s);
}
pair<double, double> Calc(int x, double t)
{
    pair<double, double> ans = pair<double, double>(0, s);
    for (int i = 1; i <= n; i++)
    {
        if (i == x) continue;
        pair<double, double> c = Get_k(1 / v1[i] - 1 / v2[i] - 1 / v1[x] + 1 / v2[x], -s * (1 / v2[i] - 1 / v2[x]) + t);
        ans.first = max(ans.first, c.first);
        ans.second = min(ans.second, c.second);
    }
    return ans;
}
bool Judge(int x, double t)
{
    pair<double, double> ans = Calc(x, t);
    return ans.first < ans.second;
}
int main()
{
    // int n, s;
    scanf ("%d%d", &s, &n);
    for (int i = 1; i <= n; i++)
        scanf ("%lf%lf", &v1[i], &v2[i]);
    if (n != 0)
    {
        if (!Judge(n, 0))
        {
            printf ("NO\n");
            return 0;
        }
        double l = 0, r = 1e10;
        while (r - l >= 1e-8)
        {
            double mid = (l + r) / 2;
            if (Judge(n, mid)) l = mid;
            else r = mid;
        }
        double k = Calc(n, l).first;
        printf ("%.2f %.2f %.0f\n", k, s - k, l * 3600);
    }
}