#include <cstdio>
#include <cstring>
#include <algorithm>
#include <list>
#include <vector>
#include <set>
using namespace std;
const int MAXN = 300000;
const int MOD = 1e9 + 7;
struct edge
{
    int END, next;
}v[(MAXN + 5) << 1];
int first[MAXN + 5], p;
void add(int a, int c)
{
    v[p].END = c;
    v[p].next = first[a];
    first[a] = p++;
}
int b[MAXN + 5], Index;
long long F[MAXN + 5], Ans;
int du[MAXN + 5];
set<int> tmp[MAXN + 5];
long long pow_mod(long long a, long long b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return ans;
}
int Sum[MAXN + 5];
#define lowbit(_) ((_) & (-_))
void update(int x, int c)
{
    for (int i = x; i <= MAXN; i+=lowbit(i))
        Sum[i] += c;
}
int Query(int x)
{
    int ans = 0;
    for (int i = x; i >= 1; i-=lowbit(i))
        ans += Sum[i];
    return ans;
}
long long f[MAXN + 5];
int size[MAXN + 5], L[MAXN + 5], R[MAXN + 5], ID[MAXN + 5];
bool vis[MAXN + 5];
void dfs(int rt, int fa)
{
    size[rt] = 1, f[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        dfs(v[i].END, rt);
        f[rt] = f[v[i].END] * f[rt] % MOD;
        size[rt] += size[v[i].END];
        tmp[rt].insert(v[i].END);
    }
    f[rt] = f[rt] * F[fa ? du[rt] - 1 : du[rt]] % MOD;
    set<int>::iterator it;
    for (it = tmp[rt].begin(); it != tmp[rt].end(); it++)
        ID[*it] = ++Index, update(ID[*it], 1);
    update(Index + 1, -(int)tmp[rt].size());
    L[rt] = ID[*tmp[rt].begin()], R[rt] = Index;
}
bool Died;
void DFS(int rt, long long last, int pos)
{
    if (Died) return;
    long long rmp = 1;
    set<int>::iterator it;
    for (it = tmp[rt].begin(); it != tmp[rt].end(); it++)
        rmp = rmp * f[*it] % MOD;
    while (!tmp[rt].empty())
    {
        if (Died) return;
        it = tmp[rt].lower_bound(b[pos]);
        if (it == tmp[rt].end())
        {
            Ans = (Ans + rmp * F[tmp[rt].size() - 1] % MOD * last % MOD * tmp[rt].size() % MOD) % MOD;
            Died = 1;
            return;
        }
        if (*it > b[pos])
        {
            Ans = (Ans + rmp * F[tmp[rt].size() - 1] % MOD * last % MOD * (Query(ID[*it]) - 1) % MOD) % MOD;
            Died = 1;
            return;
        }
        else
        {
            Ans = (Ans + rmp * F[tmp[rt].size() - 1] % MOD * last % MOD * (Query(ID[*it]) - 1) % MOD) % MOD;
            rmp = rmp * pow_mod(f[*it], MOD - 2) % MOD;
            DFS(*it, last * rmp % MOD * F[tmp[rt].size() - 1] % MOD, pos + 1);
            if (Died) return;
            pos += size[*it];
            update(ID[*it], -1);
            update(R[rt] + 1, 1);
            tmp[rt].erase(it);
        }
    }
}
int main()
{
    memset (first, -1, sizeof (first));
    int n;
    F[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        F[i] = F[i - 1] * i % MOD;
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf ("%d", &b[i]);
    int a, c;
    for (int i = 1; i < n; i++)
    {
        scanf ("%d%d", &a, &c);
        add(a, c);
        add(c, a);
        du[a]++, du[c]++;
    }
    long long tot = 1;
    for (int i = 1; i <= n; i++)
        tot = tot * F[du[i] - 1] % MOD;
    for (int i = 1; i < b[1]; i++)
        Ans = (Ans + tot * du[i] % MOD) % MOD;
    dfs(b[1], 0), DFS(b[1], 1, 2);
    printf ("%lld", Ans);
    // while(1);
}