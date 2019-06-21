#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
int n, m, block, tot;
int a[40005], Index, v[40005];
int in[40005];
int f[4000][4000], num[40005];
map<int, int> mp;
vector<int> x[40005];
void Init(int u)
{
    memset(num, 0, sizeof(num));
    int Max = 0, ans = 0;
    for (int i = (u - 1) * block + 1; i <= n; i++)
    {
        num[a[i]]++;
        if (num[a[i]] > Max || (num[a[i]] == Max && v[a[i]] < v[ans]))
            ans = a[i], Max = num[a[i]];
        f[u][in[i]] = ans;
    }
}
int Query(int l, int r, int u)
{
    return upper_bound(x[u].begin(), x[u].end(), r) - lower_bound(x[u].begin(), x[u].end(), l);
}
int Query(int l, int r)
{
    int ans, Max;
    ans = f[in[l] + 1][in[r] - 1];
    Max = Query(l, r, ans);
    for (int i = l; i <= min(in[l] * block, r); i++)
    {
        int now = Query(l, r, a[i]);
        if (now > Max || (now == Max && v[a[i]] < v[ans]))
            ans = a[i], Max = now;
    }
    if (in[l] != in[r])
    {
        for (int i = (in[r] - 1) * block + 1; i <= r; i++)
        {
            int now = Query(l, r, a[i]);
            if (now > Max || (now == Max && v[a[i]] < v[ans]))
                ans = a[i], Max = now;
        }
    }
    return ans;
}
int main()
{
    //freopen("input.in", "r", stdin);
    scanf("%d%d", &n, &m);
    block = 200;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        if (!mp[a[i]])
        {
            mp[a[i]] = ++Index;
            v[Index] = a[i];
        }
        a[i] = mp[a[i]];
        x[a[i]].push_back(i);
        in[i] = (i - 1) / block + 1;
    }
    tot = in[n];
    for (int i = 1; i <= tot; i++)
        Init(i);
    int l, r, ans = 0;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &l, &r);
        l = (l + ans - 1) % n + 1, r = (r + ans - 1) % n + 1;
        if (l > r)
            swap(l, r);
        ans = v[Query(l, r)];
        printf("%d\n", ans);
    }
    //while (1)
    ;
}