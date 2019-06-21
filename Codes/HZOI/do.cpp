#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int Dis(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}
void change(int &dx, int &dy)
{
    int x1 = 2 * (dx + dy) - 2, x2 = 4 * dx - 4, x3 = 4 * dy - 4;
    int Max = max(x1, max(x2, x3));
    if (x1 == Max)
        dx--, dy--;
    else if (x2 == Max)
        dx -= 2;
    else
        dy -= 2;
    return;
}
int main()
{
    int T;
    int a, b;
    scanf("%d", &T);
    scanf("%d%d", &a, &b);
    while (T--)
    {
        int x1, x2, y1, y2, c, d;
        scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &c, &d);
        int dis = Dis(x1, y1, x2, y2);
        int dx = abs(x2 - x1), dy = abs(y1 - y2);
        int flag = 0;
        for (; dis > 0; dis -= 2)
        {
            if (c >= a)
            {
                d -= dx * dx + dy * dy;
                c -= a;
            }
            else
                c += b;
            change(dx, dy);
            if (d <= 0)
            {
                flag = 1;
                break;
            }
        }
        if (flag)
            printf("NAIVE\n");
        else
            printf("SIMPLE\n");
    }
}