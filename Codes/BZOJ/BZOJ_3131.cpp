#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define int long long
using namespace std;
const int MOD = 1e9 + 7;
int a[15], len, cnt;
long long Num[300005], size[300005];
long long f[15][300005][2];
void dfs(int now, int Dep, long long ans)
{
    if (Dep == len) 
    {
        Num[++cnt] = ans;
        return;
    }
    if (!ans) return;
    for (int i = now; i <= 9; i++)
        dfs(i, Dep + 1, ans * i);
}
struct Node
{
    int x, y;
    long long v;
    Node(int x1 = 0, int y1 = 0, long long v1 = 0)
    {
        x = x1, y = y1, v = v1;
    }
    bool operator < (const Node &a) const 
    {
        return v < a.v;
    }
};
priority_queue<Node> Q;
int cmp(const int &a, const int &b)
{
    return a > b;
}
signed main()
{
    int k;
    long long n;
    scanf ("%lld%lld", &n, &k);
    while (n) a[++len] = n % 10, n /= 10;
    Num[++cnt] = 0;
    dfs(0, 0, 1); 
    sort(Num + 1, Num + cnt + 1);
    cnt = unique(Num + 1, Num + cnt + 1) - Num - 1;
    f[0][2][0] = 1;
    // for (int i = 1; i <= cnt; i++)  
        // printf ("%d ", Num[i]);
    // while (1);
    for (int i = 0; i <= len; i++)
        for (int j = 1; j <= cnt; j++)
            for (int l = 0; l <= 1; l++)
                if (f[i][j][l])
                    for (int x = (i == 0 ? 0 : 1); x <= 9; x++)
                    {
                        int nxt = lower_bound(Num + 1, Num + cnt + 1, Num[j] * x) - Num;
                        f[i + 1][nxt][(x + l) > a[i + 1]] += f[i][j][l];
                    }
    for (int i = 1; i <= cnt; i++)
    {
        for (int j = 1; j <= len - 1; j++)
            size[i] += f[j][i][0] + f[j][i][1];
        size[i] += f[len][i][0];
    }
    // for (int i = 1; i <= cnt; i++)
        // printf ("%lld ", size[i]);
    // while (1);
    sort(size + 1, size + cnt + 1, cmp);
    Q.push(Node(2, 2, size[2] * size[2]));
    int ans = 0;
    while (!Q.empty() && k)
    {
        Node x = Q.top(); Q.pop();
        ans = (ans + x.v) % MOD;
        if (!(--k)) break;
        if (x.x != x.y)
        {
            ans = (ans + x.v) % MOD;
            if (!(--k)) break;
            Q.push(Node(x.x + 1, x.y, size[x.x + 1] * size[x.y]));
        }
        if (x.x == 2) Q.push(Node(x.x, x.y + 1, size[x.x] * size[x.y + 1]));
    }
    printf ("%lld", ans);
    // while (1);
}