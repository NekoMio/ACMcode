#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <climits>
#include <ctime>
using namespace std;
const double pi = acos(-1.);
const double eps = 1e-10;
const int seed = time(0);
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
double Rand()
{
    return 1.0 * rand() / RAND_MAX;
}
struct Point
{
    double x, y, k;
    Point(double _x = 0, double _y = 0): x(_x), y(_y) {
        k = atan2(y, x);
    }
    Point operator - (const Point &_x)
    {
        return Point(x - _x.x, y - _x.y);
    }
    double operator * (const Point &_x)
    {
        return x * _x.y - y * _x.x;
    }
    bool operator < (const Point &_x) const
    {
        return k > _x.k;
    }
}a[10], tmp[10];
int cnt = 0;
double area(Point *x, int n)
{
    double ans = 0;
    cnt++;
    sort(x + 1, x + n + 1);
    Point t(0, 0);
    for (int i = 1; i <= n - 1; i++)
        ans += (x[i] - t) * (x[i + 1] - t);
    ans += (x[n] - t) * (x[1] - t);
    return fabs(ans);
}
int r[10];
bool cmp(const int &a, const int &b)
{
    return a > b;
}
double dis(Point &x, Point &y)
{
    return (x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y);
}
bool cmp1(Point x, Point y)
{
    double s = (x - tmp[1]) * (y - tmp[1]);
    if (fabs(s) <= eps) return dis(x, tmp[1]) < dis(y, tmp[1]);
    return s > 0;
}
int st[10], top;
double Calc(Point *x, int n)
{
	memcpy(tmp, x, sizeof (tmp));
    int k = 0;
    for (int i = 1; i <= n; i++)
        if (tmp[i].x < tmp[k].x && tmp[i].y < tmp[k].y || !k)
            k = i;
    swap(tmp[1], tmp[k]);
    sort(tmp + 2, tmp + n + 1, cmp1);
    top = 0;
    st[++top] = 1;
    for (int i = 2; i <= n; i++)
    {
        while (top > 1 && (tmp[st[top]] - tmp[st[top - 1]]) * (tmp[i] - tmp[st[top]]) < 0) top--;
        st[++top] = i;
    }
    for (int i = 1; i <= top; i++)
        tmp[i] = tmp[st[i]];
    return area(tmp, top);
}
double T = 1e9, mint = 1e-9, delta = 1 - 1e-2;
int loop = 50;
double w[10];
int main()
{
    // freopen ("1.out", "w", stdout);
    srand(seed);
    int n = read();
    for (int i = 1; i <= n; i++) r[i] = read();
    for (int i = 1; i <= n; i++) w[i] = Rand() * 2 * pi;
    for (int i = 1; i <= n; i++) a[i].x = cos(w[i]) * r[i], a[i].y = sin(w[i]) * r[i];
    double ans = Calc(a, n);
    while (T > mint)
    {
        for (int i = 1; i <= loop; i++)
        {
            int t = rand() % n + 1;
            double tmp_w = w[t];
            w[t] = w[t] + Rand() * 2 * pi * T;
            // if (w[t] > 2 * pi) w[t] -= 2 * pi;
            a[t].x = cos(w[t]) * r[t], a[t].y = sin(w[t]) * r[t];
            double tmp = Calc(a, n);
            // printf ("%.2f\n", (tmp - ans) / T);
            // printf ("%.2f\n", exp((tmp - ans) / T));
            if (tmp > ans || exp((tmp - ans) / T) > Rand()) 
                ans = tmp;
            else
            {
                w[t] = tmp_w;
                a[t].x = cos(w[t]) * r[t], a[t].y = sin(w[t]) * r[t];
            }
        }
        T *= delta;
    }
    printf ("%.10f\n", ans / 2);
    // while (1);
}