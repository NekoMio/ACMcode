#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
#define LL long long
map<LL, set<int> > mp;
LL Pow[1005][65];
LL f[100005][18];
LL a[100005];
LL RMQ(int l, int r)
{
    int len = r - l + 1;
    int k = 0;
    while((1 << k) <= len) k++;
    k--;
    return min(f[l][k], f[r - (1 << k) + 1][k]);
}
bool OK(int l, int r)
{
    LL Min = RMQ(l, r);
    int j = 0;
    for (j = l; j <= r; j++)
        if(a[j] != a[l])
            break;
    if(j == r + 1) return 1;
    set<LL> Q;
    int now = 1;
    for (int i = l; i <= r; i++)
    {
        if(a[i] % Min || !mp[a[i] / Min].size()) return 0;
        if(Q.count(a[i])) return 0;
        Q.insert(a[i]);
        if(a[i] != Min && now == 1) now = *mp[a[i] / Min].begin();
        if(!mp[a[i] / Min].count(now)) return 0;
    } 
    return 1;
}
int n;
bool Judge(int mid)
{
    for (int i = 1; i <= n - mid + 1; i++)
        if(OK(i, i + mid - 1)) return 1;
    return 0;
}
int main()
{
    // freopen("seq.in", "r", stdin);
    // freopen("seq.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    Pow[1][0] = Pow[1][1] = 1;
    mp[1].insert(1);
    for (int i = 2; i <= 1000; i++)
    {
        LL now = 1;
        Pow[i][0] = 1;
        mp[1].insert(i);
        for (int j = 1; j < 64; j++)
        {
            if((long double)now * i > 1e18) break;
            else
            { 
                Pow[i][j] = now = now * i;
                mp[now].insert(i);
            }
        }
    }
    for (int i = 1; i <= n; i++) f[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    int l = 1, r = 200, ans = 0;
    while (l < r)
    {
        int mid = l + r >> 1;
        if(Judge(mid)) 
            ans = mid, l = mid + 1;
        else 
            r = mid;
    }
    printf("%d\n", ans);
    // while(1);
}