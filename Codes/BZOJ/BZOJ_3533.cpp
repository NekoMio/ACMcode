#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 4e5 + 5;
const long long INF = 0x3f3f3f3f3f3f3f3f;
struct Point
{
    long long x, y;
    Point(long long _x, long long _y) : x(_x), y(_y) {;}
    long long operator * (const Point &a) const 
    {
        return x * a.x + y * a.y;
    }
    long long operator ^ (const Point &a) const 
    {
        return x * a.y - a.x * y;
    }
    Point operator + (const Point &a) const 
    {
        return Point(x + a.x, y + a.y);
    }
    Point operator - (const Point &a) const 
    {
        return Point(x - a.x, y - a.y);
    }
    bool operator < (const Point &a) const 
    {
        return x == a.x ? y < a.y : x < a.x;
    }
};
vector<Point> t[MAXN << 2], Cvx1[MAXN << 2], Cvx2[MAXN << 2];
void Insert(int x, const Point &c, int l, int r, int rt)
{
    t[rt].push_back(c);
    if (x == r)
    {
        sort(t[rt].begin(), t[rt].end());
        int n = t[rt].size();
        for (int i = 0; i < n; i++)
        {
            while (Cvx1[rt].size() >= 2 && ((t[rt][i] - Cvx1[rt][Cvx1[rt].size() - 1]) ^ (Cvx1[rt][Cvx1[rt].size() - 2] - Cvx1[rt][Cvx1[rt].size() - 1])) >= 0) Cvx1[rt].pop_back(); 
            Cvx1[rt].push_back(t[rt][i]);
            while (Cvx2[rt].size() >= 2 && ((t[rt][i] - Cvx2[rt][Cvx2[rt].size() - 1]) ^ (Cvx2[rt][Cvx2[rt].size() - 2] - Cvx2[rt][Cvx2[rt].size() - 1])) <= 0) Cvx2[rt].pop_back(); 
            Cvx2[rt].push_back(t[rt][i]);
        }
    }
    if (l == r) return;
    int mid = l + r >> 1;
    if (x <= mid) Insert(x, c, l, mid, rt << 1);
    else if (x > mid) Insert(x, c, mid + 1, r, rt << 1 | 1);
}
long long Query(Point x, vector<Point> &v)
{
    int L = 1, R = v.size() - 1;
    int ans = 0;
    while (L <= R)
    {
        int mid = L + R >> 1;
        if (x * v[mid] > x * v[mid - 1]) ans = mid, L = mid + 1;
        else R = mid - 1;
    }
    return x * v[ans];
}
long long Query1(int L, int R, const Point &x, int l, int r, int rt)
{
    if (L <= l && R >= r)
        return Query(x, Cvx1[rt]);
    int mid = l + r >> 1;
    long long ans = -INF;
    if (L <= mid) ans = max(ans, Query1(L, R, x, l, mid, rt << 1));
    if (R > mid) ans = max(ans, Query1(L, R, x, mid + 1, r, rt << 1 | 1));
    return ans;
}
long long Query2(int L, int R, const Point &x, int l, int r, int rt)
{
    if (L <= l && R >= r)
        return Query(x, Cvx2[rt]);
    int mid = l + r >> 1;
    long long ans = -INF;
    if (L <= mid) ans = max(ans, Query2(L, R, x, l, mid, rt << 1));
    if (R > mid) ans = max(ans, Query2(L, R, x, mid + 1, r, rt << 1 | 1));
    return ans;
}
int main()
{
    int n = read(), cnt = 0;
    long long lastans = 0;
    char op[5], str[5];
    scanf ("%s", op);
    Point o(0, 0);
    for (int i = 1; i <= n; i++)
    {
        scanf ("%s", str);
        o.x = read() ^ lastans, o.y = read() ^ lastans;
        if (str[0] == 'A') Insert(++cnt, o, 1, n, 1);
        else
        {
            int l = read() ^ lastans, r = read() ^ lastans;
            if (o.y > 0) lastans = Query1(l, r, o, 1, n, 1);
            else lastans = Query2(l, r, o, 1, n, 1);
            printf ("%lld\n", lastans);
            lastans &= 0x7fffffff;
            if (op[0] == 'E') lastans = 0;
        }
    }
}