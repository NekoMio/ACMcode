#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long extgcd(long long a, long long b, long long &x, long long &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    long long gcd = extgcd(b, a % b, x, y);
    long long tmp = x;
    x = y;
    y = tmp - a / b * y;
    return gcd;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        long long a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);
        if (c < 0)
            a = -a, b = -b, c = -c;
        if (a == 0)
        {
            if (b == 0)
            {
                if (c == 0)
                    printf("ZenMeZheMeDuo\n");
                else
                    printf("0\n");
                continue;
            }
            else
            {
                if (c % b == 0 && c / b > 0)
                    printf("ZenMeZheMeDuo\n");
                else
                    printf("0\n");
                continue;
            }
        }
        if (b == 0)
        {
            if (c % a == 0 && c / a > 0)
                printf("ZenMeZheMeDuo\n");
            else
                printf("0\n");
            continue;
        }
        if (c == 0)
        {
            if (a * b < 0)
            {
                printf("ZenMeZheMeDuo\n");
                continue;
            }
            else
            {
                printf("0\n");
                continue;
            }
        }
        if (a < 0 && b < 0)
        {
            printf("0\n");
            continue;
        }
        long long x, y;
        long long gcd = extgcd(abs(a), abs(b), x, y);
        //printf("%d\n", gcd);
        if (c % gcd != 0)
        {
            printf("0\n");
            continue;
        }
        if (a * b < 0)
        {
            printf("ZenMeZheMeDuo\n");
            continue;
        }
        long long t1 = b / gcd;
        x = x * c / gcd;
        y = y * c / gcd;
        long long x1 = (x % t1 + t1) % t1;
        if (x1 == 0)
            x1 += t1;
        //printf("x1 := %d\n", x1);
        long long t2 = a / gcd;
        long long y2 = (y % t2 + t2) % t2;
        //printf("y := %d\n", y);
        if (y2 == 0)
            y2 += t2;
        //printf("y2 := %d\n", y2);
        long long x2 = (c - y2 * b) / a;
        //printf("x2 := %d\n", x2);
        long long ans = (x2 - x1) / t1 + 1;
        if (ans < 0)
            printf("0\n");
        else if (ans > 65535)
            printf("ZenMeZheMeDuo\n");
        else
            printf("%lld\n", ans);
        //printf("\n");
    }
    //while (1);
}