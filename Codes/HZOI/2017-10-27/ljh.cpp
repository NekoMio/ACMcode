#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <ctime>
#include <vector>
using namespace std;
int read()
{
    int x = 0, f = 1; char ch = getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1e5 + 5;
struct point
{
    int x, y;
    bool operator < (const point &a) const 
    {
        return x == a.x ? y < a.y : x < a.x;
    }
    bool operator > (const point &a) const
    {
        return y == a.y ? x < a.x : y < a.y;
    }
    bool operator == (const point &a) const
    {
        return x == a.x && y == a.y;
    }
};
long long ans = 0;
struct data
{
    point a, b;
    void Read()
    {
        a.x = read(); a.y = read();
        b.x = read(); b.y = read();
        ans += (long long)2 * (b.x - a.x) * (b.y - a.y);
    }
    bool operator < (const data &c) const
    {
        return a == c.a ? b < c.b : a < c.a;
    }
}a[MAXN];
int Calc(int a, int b, int c, int d, int op)
{
    if (a <= c && b >= d) return (d - c + 1) * 2 - (a == c) - (b == d);
    if (a >= c && b <= d) return (b - a + 1) * 2 - (a == c) - (b == d);
    if (c <= b) 
    {
        if (a <= c && b <= d) return (b - c + 1) * 2 - (a == c) - (b == d);
    }
    if (a <= d)
    {
        if (a >= c && b >= d) return (d - a + 1) * 2 - (a == c) - (b == d);
    }
    if (c == b + 1) return 1;
    if (a == d + 1) return 1;
    return 0;
}
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
        a[i].Read();
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (a[j].a.x - 1 > a[i].b.x) break;
            if (a[j].a.x == a[i].b.x + 1)
            {
                ans += Calc(a[i].a.y, a[i].b.y, a[j].a.y, a[j].b.y, 1);
            }
            else if (a[j].a.y == a[i].b.y + 1)
            {
                ans += Calc(a[i].a.x, a[i].b.x, a[j].a.x, a[j].b.x, 0);
            }
            else if (a[j].b.x + 1 == a[i].a.x)
            {
                ans += Calc(a[i].a.y, a[i].b.y, a[j].a.y, a[j].b.y, 1);
            }
            else if (a[j].b.y + 1 == a[i].a.y)
            {
                ans += Calc(a[i].a.x, a[i].b.x, a[j].a.x, a[j].b.x, 0);
            }
        }
    }
    printf ("%lld", ans);
}