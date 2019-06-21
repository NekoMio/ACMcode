#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long Get_Num(long long x)
{
    long long t = 1;
    while (t <= x) t <<= 1;
    return t >>= 1;
}
double Sum(long long a, long long b)
{
    return 1.0 * (a + b) * (b - a + 1) / 2;
}
double Get_Ans(long long x)
{
    if (x <= 1) return 0;
    double next = 1.0 * Get_Num(x);
    return Sum(0, next - 1) * next + Sum(next, next + next - 1) * (x - next) * 2 + Get_Ans(x - next);
}
double Get_ans(long long x, long long y, long long s)
{
    if (x == 0 || y == 0) return 0;
    if (y == 1) return s;
    double next = Get_Num(y - 1);
    if (x > next) return (1.0 * s + 2 * next - 1) * (1.0 * y - next) + Get_ans(x - next, next, s + next);
    else return Get_ans(x, next, s) * 2 + 1.0 * next * next;
}
int main()
{
    long long n;
    double p;
    scanf ("%lld", &n);
    scanf ("%lf", &p);
    // printf ("%lld\n", Get_ans(n, n, 0));
    // printf ("%lld", Get_Ans(n));
    printf ("%.6lf", Get_ans(n, n, 0) * (p) / n + Get_Ans(n) * ((double)1 - p) / n / n);
    // while (1);
}