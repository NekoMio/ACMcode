// #pragma GCC optimize("O2")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 100005;
struct Point
{
    long long x, y;
}a[MAXN];
struct cmp1
{
    bool operator () (const Point &a, const Point &b)
    {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    }
};
struct cmp2
{
    bool operator () (const Point &a, const Point &b)
    {
        return a.y == b.y ? a.x < b.x : a.y < b.y;
    }
};
long long MinX, MinY, MaxX, MaxY;
multiset<Point, cmp1> nu1;
multiset<Point, cmp2> nu2;
int main()
{
    // freopen ("mst1.in", "r", stdin);
    // freopen ("mst.out", "w", stdout);
    int n = read();
    for (int i = 1; i <= n; i++)
    {
        int x = read(), y = read();
        a[i].x = x + y, a[i].y = x - y;
    }
    MinX = MaxX = a[1].x;
    MinY = MaxY = a[1].y;
    for (int i = 2; i <= n; i++)
    {
        nu1.insert(a[i]);
        nu2.insert(a[i]);
    }
    long long ans = 0;
    while (!nu1.empty())
    {
        // fprintf (stderr, "%d\n", nu1.size());
        long long Mx = max(MaxX - nu1.begin()->x, max(MaxY - nu2.begin()->y, max(nu1.rbegin()->x - MinX, nu2.rbegin()->y - MinY)));
        if (Mx == MaxX - nu1.begin()->x)
        {
            Point z = *nu1.begin();
            MinX = min(z.x, MinX);
            MaxX = max(z.x, MaxX);
            MinY = min(z.y, MinY);
            MaxY = max(z.y, MaxY);
            nu1.erase(nu1.find(z));
            nu2.erase(nu2.find(z));
        }
        else if (Mx == MaxY - nu2.begin()->y)
        {
            Point z = *nu2.begin();
            MinX = min(z.x, MinX);
            MaxX = max(z.x, MaxX);
            MinY = min(z.y, MinY);
            MaxY = max(z.y, MaxY);
            nu1.erase(nu1.find(z));
            nu2.erase(nu2.find(z));
        }
        else if (Mx == nu1.rbegin()->x - MinX)
        {
            Point z = *nu1.rbegin();
            MinX = min(z.x, MinX);
            MaxX = max(z.x, MaxX);
            MinY = min(z.y, MinY);
            MaxY = max(z.y, MaxY);
            nu1.erase(nu1.find(z));
            nu2.erase(nu2.find(z));
        }
        else if (Mx == nu2.rbegin()->y - MinY)
        {
            Point z = *nu2.rbegin();
            MinX = min(z.x, MinX);
            MaxX = max(z.x, MaxX);
            MinY = min(z.y, MinY);
            MaxY = max(z.y, MaxY);
            nu1.erase(nu1.find(z));
            nu2.erase(nu2.find(z));
        }
        ans += Mx;
    }
    printf ("%lld\n", ans);
}