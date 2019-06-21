#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
struct data
{
    int a, b, c, d;
} a[20];
int main()
{
    freopen("week.in", "r", stdin);
    freopen("week.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d%d%d", &a[i].a, &a[i].b, &a[i].c, &a[i].d);
    int N = (1 << n) - 1;
    long long ans = 0;
    for (int i = 0; i <= N; i++)
    {
        long long LevelOI = 0;
        long long LevelWHK = 0;
        for (int j = 0; j < n; j++)
        {
            if(i & (1 << j))
            {
                LevelOI += a[j].c;
                LevelWHK -= a[j].d;
                if(LevelWHK < 0) LevelWHK = 0;
            }
            else
            {
                LevelWHK += a[j].a;
                LevelOI -= a[j].b;
                if(LevelOI < 0) LevelOI = 0;
            }
        }
        ans = max(ans, LevelOI * LevelWHK);
    }
    printf("%lld", ans);
}