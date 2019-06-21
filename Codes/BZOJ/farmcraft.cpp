#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;
struct edge
{
    int END, next;
} v[1000005];
int w[500005], first[500005], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int f[500005];
int dfs(int x, int fa)
{
    int t = 0;
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (v[i].END != fa)
        {
            f[v[i].END] = dfs(v[i].END, x);
            t += f[v[i].END] + 2;
        }
    }
    return t;
}
int t[500005];
int comp(const int &a, const int &b)
{
    return t[a] > t[b];
}
void DP(int x, int fa)
{
    vector<int> re;
    for (int i = first[x]; i != -1; i = v[i].next)
        if (v[i].END != fa)
        {
            DP(v[i].END, x);
            re.push_back(v[i].END);
        }
    sort(re.begin(), re.end(), comp);
    if (x != 1)
        t[x] = w[x] - f[x];
    int now = f[x];
    for (int i = 0; i < re.size(); i++)
    {
        now -= (f[re[i]] + 2);
        t[x] = max(t[x], t[re[i]] - now - 1);
    }
    t[x] = max(t[x], 0);
}
int main()
{
    freopen("farmcraft.in", "r", stdin);
    freopen("farmcraft.out", "w", stdout);
    //memset(f, -1, sizeof(f));
    memset(first, -1, sizeof(first));
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &w[i]);
    }
    int a, b;
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &a, &b);
        add(a, b);
        add(b, a);
    }
    f[1] = dfs(1, 0);
    //for (int i = 1; i <= n; i++)
    // printf("%d ", f[i]);
    //printf("\n======================\n");
    DP(1, 0);
    //while(1);
    printf("%d\n", f[1] + max(w[1], t[1]));
}