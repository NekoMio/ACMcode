#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
int c[105];
int a[105][105], map[105][105], link[105][105];
bool flag[105];
int t, ans = 0x3f3f3f3f, n;
stack<int> Q;
void dfs(int x, int len)
{
    if(x == t)
    {
        ans = min(ans, len);
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        if(link[x][i] && !flag[c[i]] && map[x][i] + len < ans && !a[c[i]][c[i]])
        {
            flag[c[i]] = 1;
            int t = 0;
            for (int j = 1; j <= n; j++)
                if(a[c[j]][c[i]] && !flag[c[j]])
                    Q.push(c[j]), t++, flag[c[j]] = 1;
            dfs(i, len + map[x][i]);
            while(t--)
                flag[Q.top()] = 0, Q.pop();
        }
    }
}
int main()
{
    freopen("culture.in", "r", stdin);
    freopen("culture.out", "w", stdout);
    int k, m, S;
    scanf("%d%d%d%d%d", &n, &k, &m, &S, &t);
    for (int i = 1; i <= n; i++)
        scanf("%d", &c[i]);
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= k; j++)
            scanf("%d", &a[i][j]);
    int s, e;
    memset(map, 0x3f, sizeof(map));
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &s, &e);
        scanf("%d", &map[s][e]);
        map[e][s] = map[s][e];
        link[s][e] = link[e][s] = 1;
    }
    for (int i = 1; i <= n; i++)
        map[i][i] = 0;
    for (int l = 1; l <= n; l++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                map[i][j] = min(map[i][j], map[i][l] + map[l][j]);
    flag[c[S]] = 1;
    for (int i = 1; i <= n; i++)
        if(a[c[i]][c[S]])
            flag[c[i]] = 1;
    dfs(S, 0);
    if(ans > 10000000)
        ans = -1;
    printf("%d\n", ans);
}