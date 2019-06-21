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
const int MAXN = 1e6 + 5;
struct Point
{
    double x, y;
}a[MAXN], Cvx[MAXN];
double K(Point &b, Point &c)
{
    return b.x == c.x ? 1e300 : (b.y - c.y) / (b.x - c.x);
}
bool cmp(const Point &c, const Point &d){return c.x == d.x ? c.y < d.y : c.x < d.x;}
int Get_Cvx(int n)
{
    int t = 0;
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++)
    {
        while (t >= 2 && K(a[i], Cvx[t]) > K(Cvx[t], Cvx[t - 1])) t--;
        Cvx[++t] = a[i];
    }
    return t;
}
double Calc(Point &a, double k)
{
    if (k >= 0) return 1e60;
    return a.x + a.y - a.x * k - a.y / k;
}
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
        a[i].x = read(), a[i].y = read();
    n = Get_Cvx(n);
    if (n == 1) return printf ("%.4f\n", Calc(Cvx[1], -sqrt(Cvx[1].x / Cvx[1].y)));
    double ans = 1e80;
    for (int i = 2; i <= n; i++)
    {
        double k = -sqrt(Cvx[i].x / Cvx[i].y);
        double k1 = K(Cvx[i - 1], Cvx[i]), k2 = (i == n) ? -1e80 : K(Cvx[i], Cvx[i + 1]);
        ans = min(ans, Calc(Cvx[i], k1));
        if (k1 >= k && k >= k2) ans = min(ans, Calc(Cvx[i], k));
    }
    double k = -sqrt(Cvx[1].x / Cvx[1].y);
    double k1 = K(Cvx[1], Cvx[2]);
    if (k > k1) ans = min(ans, Calc(Cvx[1], k));
    printf ("%.4f\n", ans);
}