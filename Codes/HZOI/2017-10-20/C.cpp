#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <vector>
using namespace std;
int Num[10];
#define LL long long
LL C[20][20], g[20];
int c[20];
int f[7] = {0,1,2,3,5,8,13};
bool isf(int x)
{
    if (x == 0 || x == 1 || x == 2 || x == 3 || x == 5 || x == 8 || x == 13) return 1;
    return 0; 
}
vector<int> S;
map<vector<int>, LL> mp[20];
LL Query(int x, int y)
{
    if (x == 10)
    {
        if (y == 0) return 1;
        else return 0;
    }
    LL ans = 0;
    for (int i = 0; i <= 6; i++)
    {
        if (f[i] >= c[x])
        {
            if (f[i] - c[x] > y) break;
            ans += C[y][f[i] - c[x]] * Query(x + 1, y - (f[i] - c[x]));
        }
    }
    return ans;
}
LL Query(int x)
{
    for (int i = 0; i <= 13; i++) S[i] = 0;
    for (int i = 0; i <= 9; i++) S[c[i]]++;
    if (mp[x].count(S))
        return mp[x][S];
    return mp[x][S] = Query(0, x);
}
int a[20];
bool Check()
{
    for (int i = 0; i <= 9; i++) 
        if (!isf(c[i])) 
            return 0;
    return 1;
}
LL dfs(int x, int top)
{
    if (!top) return Query(x - 1);
    if (x == 1) return Check();
    LL ans = 0;
    for (int i = 0; i <= 9; i++)
    {
        if (top && a[x - 1] < i)
            break;
        c[i]++;
        ans += dfs(x - 1, top && (i == a[x - 1]));
        c[i]--;
    }
    return ans;
}
LL Q(LL x)
{
    if (!x) return 0;
    int len = 0;
    LL ans = 0;
    while (x) a[++len] = x % 10, x /= 10;
    for (int i = 1; i <= a[len]; i++) c[i]++, ans += dfs(len, i == a[len]), c[i]--;
    ans += g[len - 1];
    return ans;
}
int main()
{
    S.resize(14);
    C[0][0] = 1;
    for (int i = 1; i <= 19; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= 19; j++)
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
    for (int i = 1; i <= 18; i++)
    {
        g[i] = Query(i) + g[i - 1];
        c[0]++;
        g[i] -= Query(i - 1);
        c[0]--;
    }
    int t = 5;
    while (t--)
    {
        LL n;
        scanf ("%lld", &n);
        LL l = 0, r = 4 * n;
        LL ans = 0;
        while(l <= r)
        {
            LL mid = l + r >> 1;
            if (Q(mid) < n)
                l = mid + 1;
            else
                r = mid - 1;
        }
        printf ("%lld\n", l);
    }
}