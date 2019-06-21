#pragma GCC optimize("O3")
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 200005;
const int MAXM = 500000;
int prime[MAXN], isnprime[MAXM + 1], mu[MAXM + 1], cnt;
void Get_mu()
{
    mu[1] = 1;
    for (int i = 2; i <= MAXM; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > MAXM) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
            mu[i * prime[j]] = -mu[i]; 
        }
    }
}
struct edge
{
    int v, next;
}v[MAXM << 6];
int first[MAXN], p;
void add(int a, int b)
{
    v[p].v = b;
    v[p].next = first[a];
    first[a] = p++;
}
bool vis[MAXN];
long long Ans, Sum[MAXM + 2];
int main()
{
    memset(first, -1, sizeof(first));
    int n, m, val;
    Get_mu();
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &val);
        for (int j = 1; j * j <= val; j++)
        {
            if(val % j) continue;
            add(i, j);
            if(val / j != j) add(i, val / j);
        }
    }
    while (m--)
    {
        scanf("%d", &val);
        if(vis[val]) 
            for (int i = first[val]; i != -1; i = v[i].next) Sum[v[i].v]--, Ans -= Sum[v[i].v] * mu[v[i].v];
        else
            for (int i = first[val]; i != -1; i = v[i].next) Ans += Sum[v[i].v] * mu[v[i].v], Sum[v[i].v]++;
        vis[val] ^= 1;
        printf("%lld\n", Ans);
    }
}