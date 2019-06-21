#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
bool type[1005][1005];
int a[1005][1005];
struct Point
{
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};
vector<Point> c[1005];
int dx[4] = {0, 0, 1, -1},
    dy[4] = {-1, 1, 0, 0};
#define id(_) ((_).x * m + (_).y + 1)
int father[10000105];
bool s[10000105];
int find(int x)
{
    if (father[x] != x)
        father[x] = find(father[x]);
    return father[x];
}
void merge(int a, int b)
{
    int x = find(a), y = find(b);
    if (x != y)
    {
        father[x] = y;
        s[y] |= s[x];
    }
}
int main()
{
    int n, m;
    int b;
    scanf("%d%d", &n, &m);
    int h = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &b);
            if (b >= 0)
                type[i][j] = 1;
            a[i][j] = (b > 0 ? b : -b);
            c[a[i][j]].push_back(Point(i, j));
            h = max(h, a[i][j]);
        }
    for (int i = 1; i <= (n + 1) * m; i++)
        father[i] = i, s[i] = 0;
    int ans = 0;
    for (int i = 0; i <= h; i++)
    {
        for (int j = 0; j < c[i].size(); j++)
        {
            Point now = c[i][j];
            for (int k = 0; k < 4; k++)
            {
                Point nex(now.x + dx[k], now.y + dy[k]);
                if (nex.x > 0 && nex.y > 0 && nex.x <= n && nex.y <= m)
                {
                    if (a[nex.x][nex.y] <= a[now.x][now.y])
                    {
                        merge(id(now), id(nex));
                    }
                }
            }
        }
        for (int j = 0; j < c[i].size(); j++)
        {
            Point now = c[i][j];
            if (type[now.x][now.y])
            {
                if (!s[find(id(now))])
                {
                    s[find(id(now))] = 1;
                    ans++;
                }
            }
        }
    }
    printf("%d\n",ans);
}
