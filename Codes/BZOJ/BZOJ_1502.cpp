#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
double alpha;
int n, cnt;
const double eps = 1e-10;
const int MAXN = 505;
double s[MAXN], h[MAXN], r[MAXN];
double p2(double x)
{
    return x*x;
}
struct line
{
    double x1, x2, y1, y2;
}a[MAXN];
double Calc(double L, double R, double fl, double fr, double fm)
{
    return (R - L) / 6.0 * (fl + fr + 4 * fm);
}
double F(double x)
{
    double ans = 0;
    for (int i = 0; i < n; i++)
        if (fabs(s[i] - x) < r[i])
            ans = max(ans, sqrt(p2(r[i]) - p2(s[i] - x)));
    for (int i = 1; i <= cnt; i++)
        if (a[i].x1 < x && a[i].x2 > x)
            ans = max(ans, a[i].y1 + (a[i].y2 - a[i].y1) / (a[i].x2 - a[i].x1) * (x - a[i].x1));
    return ans;
}
double Simpson(double L, double R, double mid, double fl, double fr, double fm, double s)
{
    double m1 = (L + mid) / 2, m2 = (mid + R) / 2;
    double f1 = F(m1), f2 = F(m2);
    double s1 = Calc(L, mid, fl, fm, f1), s2 = Calc(mid, R, fm, fr, f2);
    if (fabs(s - s1 - s2) < eps) return s1 + s2;
    return Simpson(L, mid, (L + mid) / 2, fl, fm, f1, s1) + Simpson(mid, R, (mid + R) / 2, fm, fr, f2, s2);
}
int main()
{
    scanf ("%d%lf", &n, &alpha);
    alpha = 1./tan(alpha);
    for (int i = 0; i <= n; i++)
    {
        scanf ("%lf", &h[i]);
        if (i) h[i] += h[i - 1];
        s[i] = h[i] * alpha;
    }
    double L = 2000, R = -2000;
    for (int i = 0; i < n; i++)
    {
        scanf ("%lf", &r[i]);
        L = min(L, s[i] - r[i]);
        R = max(R, s[i] + r[i]);
    }
    R = max(R, s[n]);
    r[n] = 0;
    for (int i = 0; i < n; i++)
    {
        double d = s[i + 1] - s[i];
        if (d > fabs(r[i] - r[i + 1]))
        {
            a[++cnt].x1 = s[i] - r[i] * (r[i + 1] - r[i]) / d;
            a[cnt].y1 = sqrt(p2(r[i]) - p2(a[cnt].x1 - s[i]));
            a[cnt].x2 = s[i + 1] - r[i + 1] * (r[i + 1] - r[i]) / d;
            a[cnt].y2 = sqrt(p2(r[i + 1]) - p2(a[cnt].x2 - s[i + 1]));
        }
    }
    double fl = F(L), fr = F(R), fm = F((1.0 * L + R) / 2);
    printf ("%.2f\n", 2 * Simpson(L, R, (1.0 * L + R) / 2, fl, fr, fm, Calc(L, R, fl, fr, fm)));
}