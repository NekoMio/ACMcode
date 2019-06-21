#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 200000;
int f[2 * N + 5][20];
int w[N + 5];
int father[2 * N + 5];
struct data
{
    int a, b;
};
vector<int> ch[2 * N + 2];
vector<data> ls[2 * N + 2];
int find(int x)
{
    if (father[x] != x)
        father[x] = find(father[x]);
    return father[x];
}
int Dep[2 * N + 5];
void Init(int rt, int dep)
{
    Dep[rt] = dep;
    for (int i = 1; i <= 18; i++)
        f[rt][i] = f[f[rt][i - 1]][i - 1];
    for (int i = 0; i < ch[rt].size(); i++)
        Init(ch[rt][i], dep + 1);
}
int LCA(int a, int b)
{
    if (Dep[a] < Dep[b])
        swap(a, b);
    int l = Dep[a] - Dep[b];
    for (int i = 18; i >= 0; i--)
        if (l >= (1 << i))
        {
            a = f[a][i];
            l -= (1 << i);
        }
    if (a == b)
        return a;
    for (int i = 18; i >= 0; i--)
        if (f[a][i] != f[b][i])
            a = f[a][i], b = f[b][i];
    return f[a][0];
}
int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n + m + 1; i++)
        father[i] = i;
    for (int i = 1; i <= n; i++)
        scanf("%d", &w[i]);
    int a, b;
    int Id = n;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        int x = find(a), y = find(b);
        father[x] = ++Id, father[y] = Id;
        f[x][0] = Id, f[y][0] = Id;
        ch[Id].push_back(x), ch[Id].push_back(y);
    }
    for (int i = 1; i <= Id; i++)
        if (!Dep[i])
            Init(find(i), 0);
    for (int i = 1; i <= k; i++)
    {
        scanf("%d%d", &a, &b);
        if (find(a) == find(b))
        {
            int lca = LCA(a, b);
            //printf("%d ", lca);
            ls[lca].push_back((data){a, b});
        }
    }
    long long ans = 0;
    for (int i = n + 1; i <= Id; i++)
    {
        for (int j = 0; j < ls[i].size(); j++)
        {
            a = min(w[ls[i][j].a], w[ls[i][j].b]);
            w[ls[i][j].a] -= a, w[ls[i][j].b] -= a;
            ans += a;
        }
    }
    printf("%lld\n", ans << 1);
}