#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;
struct data
{
    double p, q, pq;
}v[100005];
int n, a, b;
int UseA[100005], UseB[100005];
double f[100005];
double ans = 0;
bool OK(double m, double c)
{
    memset (f, 0xfe, sizeof (f));
    memset (UseA, 0, sizeof (UseA));
    memset (UseB, 0, sizeof (UseB));
    f[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        f[i] = f[i - 1];
        UseA[i] = UseA[i - 1];
        UseB[i] = UseB[i - 1];
        if (f[i] < f[i - 1] + v[i].p - m)
        {
            f[i] = f[i - 1] + v[i].p - m;
            UseA[i] = UseA[i - 1] + 1;
            UseB[i] = UseB[i - 1];
        }
        if (f[i] < f[i - 1] + v[i].q - c)
        {
            f[i] = f[i - 1] + v[i].q - c;
            UseA[i] = UseA[i - 1];
            UseB[i] = UseB[i - 1] + 1;
        }
        if (f[i] < f[i - 1] + v[i].pq - m - c)
        {
            f[i] = f[i - 1] + v[i].pq - m - c;
            UseA[i] = UseA[i - 1] + 1;
            UseB[i] = UseB[i - 1] + 1;
        }
    }
    return UseA[n] > a;
}
bool Judge(double m, double &t)
{
    double l = 0, r = 1;
    while (l + 1e-8 < r)
    {
        double mid = (l + r) / 2;
        if (OK(mid, m)) l = mid;
        else r = mid;
    }
    t = l;
    return UseB[n] >= b;
}
int main()
{
    // freopen ("red.in", "r", stdin);
    // freopen ("red.out", "w", stdout);
    // std::ios::sync_with_stdio(false);
    while (scanf ("%d%d%d", &n, &a, &b) == 3)
    {
        for (int i = 1; i <= n; i++)
            scanf ("%lf", &v[i].p);
        for (int i = 1; i <= n; i++)
            scanf ("%lf", &v[i].q);
        for (int i = 1; i <= n; i++)
            v[i].pq = v[i].p + v[i].q - v[i].p * v[i].q;
        a = min(a, n), b = min(b, n);
        double l = 0, r = 1;
        double t = 0;
        while (l + 1e-8 < r)
        {
            double m = (l + r) / 2;
            if (Judge(m, t)) l = m;
            else r = m;
        }
        printf ("%.3lf\n", f[n] + b * l + a * t);
    }
}