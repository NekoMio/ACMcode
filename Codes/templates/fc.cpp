#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
int st[10005], top ,n;

template <typename _Tp>
struct Point
{
    _Tp x, y;
    _Tp operator*(const Point &a)
    {
        return x * a.y - a.x * y;
    }
    Point operator-(const Point &a)
    {
        return (Point){x - a.x, y - a.y};
    }
};
Point<double> P[10005];
template <typename _Tp>
_Tp dis(Point<_Tp> a, Point<_Tp> b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
template <typename _Tp>
bool operator<(Point<_Tp> a, Point<_Tp> b)
{
    _Tp s = (a - P[1]) * (b - P[1]);
    if (s == 0)
        return dis(a, P[1]) < dis(b, P[1]);
    return s > 0;
}
void Graham()
{
    st[++top] = 1;
    for (int i = 2; i <= n; i++)
    {
        while (top > 1 && (P[st[top]] - P[st[top - 1]]) * (P[i] - P[st[top]]) < 0)
            top--;
        st[++top] = i;
    }
}
int main(int argc, char const *argv[])
{
    freopen("fc.in","r",stdin);
    freopen("fc.out","w",stdout);
    scanf("%d", &n);
    int k = 1;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lf%lf", &P[i].x, &P[i].y);
        if (P[i].x < P[k].x && P[i].y < P[k].y)
            k = i;
    }
    swap(P[k], P[1]);
    sort(P + 2, P + n + 1);
    Graham();
    double ans = 0;
    for (int i = 1; i < top; i++)
    {
        ans += dis(P[st[i]], P[st[i + 1]]);
    }
    ans += dis(P[st[1]], P[st[top]]);
    printf("%.2f", ans);
    return 0;
}
