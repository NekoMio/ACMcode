#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
struct edge
{
    int next, END;
}v[6005];
int first[3005], p;
bool is_not_root[3005];
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
const int MOD = 1e9 + 7;
int size[3005], son[3005], n;
long long f[3005][3005], g[3005][3005], G[3005], F[3005];
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if(b&1)
            ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
void dfs(int rt)
{
    size[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
        dfs(v[i].END), size[rt]+=size[v[i].END];
    long long Inv = pow_mod(son[rt], MOD - 2);
    memset(F, 0, sizeof(F));
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        int now = v[i].END;
        for (int k = 0; k <= n; k++)
            G[k] = 1;
        for (int j = first[rt]; j != -1; j = v[j].next)
        {
            int x = v[j].END;
            for (int k = 0; k <= size[x] + 1; k++)
            {
                long long FF = G[k];
                if(k) FF -= G[k - 1];
                if(x == now) F[k] = ((f[x][k] * G[k] + g[x][k] * FF - f[x][k] * FF) % MOD + MOD) % MOD;
                else if (k) F[k] = ((f[x][k - 1] * G[k] + g[x][k - 1] * FF - f[x][k - 1] * FF) % MOD + MOD) % MOD;
            }
            G[0] = F[0], F[0] = 0;
            for (int k = 1; k <= size[x] + 1; k++)
                G[k] = (G[k - 1] + F[k]) % MOD, F[k] = 0;
        }
        for (int k = size[rt]; k > 0; k--)
            G[k] = (G[k] - G[k - 1] + MOD) % MOD;
        for (int k = 0; k <= size[rt]; k++)
            g[rt][k] = (G[k] * Inv % MOD + g[rt][k]) % MOD;
    }
    if(size[rt] == 1)
        g[rt][0] = 1;
    f[rt][0] = g[rt][0];
    for (int i = 1; i <= size[rt] + 1; i++)
        f[rt][i] = g[rt][i], g[rt][i] = (g[rt][i] + g[rt][i - 1]) % MOD;
}
int main()
{
    // freopen("tree.in", "r", stdin);
    // freopen("tree.out", "w", stdout); 
    memset(first, -1, sizeof(first));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int e;
        scanf("%d", &son[i]);
        for (int j = 1; j <= son[i]; j++)
        {
            scanf("%d", &e);
            add(i, e);
            is_not_root[e] = 1;
        }
    }
    int root = 1;
    for (int i = 1; i <= n; i++)
        if(!is_not_root[i])
            root = i;
    dfs(root);
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        (ans += f[root][i] * i) %= MOD;
    printf("%lld", ans);
    getchar(), getchar();
    return 0;
}