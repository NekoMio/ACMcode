#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const double eps = 1e-12;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
double a, b;
double F(double x)
{
    return b * sqrt(1 - (x * x) / (a * a));
}
double Calc(double l, double r, double fl, double fr, double fm)
{
    return (r - l) / 6.0 * (fl + fr + 4 * fm);
}
double Simpson(double l, double r, double mid, double fl, double fr, double fm, double s)
{
    double m1 = (l + mid) / 2, m2 = (mid + r) / 2;
    double f1 = F(m1), f2 = F(m2);
    double s1 = Calc(l, mid, fl, fm, f1), s2 = Calc(mid, r, fm, fr, f2);
    if (fabs(s - s1 - s2) < eps) return s1 + s2;
    return Simpson(l, mid, m1, fl, fm, f1, s1) + Simpson(mid, r, m2, fm, fr, f2, s2);
}
int main()
{
    int T = read();
    while (T--)
    {
        a = read(); b = read();
        int l = read(), r = read();
        double fl = F(l), fr = F(r), fm = F((1.0 * l + r) / 2);
        printf ("%.3f\n", 2 * Simpson(l, r, (1.0 * l + r) / 2, fl, fr, fm, Calc(l, r, fl, fr, fm)));
    }
}