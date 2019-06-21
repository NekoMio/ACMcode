#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100005;
#define P(_) ((_ & 1) ? (_ + 1) : (_ - 1))
int n, m, Col[MAXN], Ans[MAXN], first[MAXN], p, cnt;
struct edge
{
    int END, next, S;
}v[MAXN << 1];
void add(int a, int b)
{
    v[p].END = b;
    v[p].S = a;
    v[p].next = first[a];
    first[a] = p++;
}
bool dfs(int rt)
{
    if (Col[rt]) return Col[rt] & 1;
    Col[rt] = 1; Col[P(rt)] = 2;
    Ans[++cnt] = rt;
    for (int i = first[rt]; i != -1; i = v[i].next)
        if (!dfs(v[i].END)) return 0;
    return 1;
}
bool Work()
{
    for (int i = 1; i <= n << 1; i++)
    {
        if (Col[i]) continue;
        cnt = 0;
        if (!dfs(i))
        {
            for (int j = 1; j <= cnt; j++)
                Col[Ans[j]] = Col[P(Ans[j])] = 0;
            if (!dfs(P(i))) return 0;
        }
    }
    return 1;
}
int main()
{
    freopen("spo.in","r",stdin);
    freopen("spo.out","w",stdout);
    memset (first, -1, sizeof (first));
    scanf ("%d%d", &n, &m);
    int a, b;
    for (int i = 1; i <= m; i++)
    {
        scanf ("%d%d", &a, &b);
        add(a, P(b));
        add(b, P(a));
    }
    if (Work())
    {
        for (int i = 1; i <= n << 1; i++)
            if (Col[i] == 1) printf ("%d\n", i);
    }
    else puts("NIE");
    return 0;
}