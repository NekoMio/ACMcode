#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int mp[20][20];
int S;
long long F[20][20];
struct edge
{
    int END, next;
}v[20 * 20 * 2];
int first[20], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
long long tmp[20];
int Size(int x)
{
    int ans = 0;
    while (x)
    {
        ans += (x & 1);
        x >>= 1;
    }
    return ans;
}
int n, m;
int a[20], cnt;
void DFS(int rt, int fa)
{
    for (int i = 1; i <= n; i++) if ((1 << (i - 1)) & S) F[rt][i] = 1; else F[rt][i] = 0;
    for (int k = first[rt]; k != -1; k = v[k].next)
    {
        if (v[k].END == fa) continue;
        DFS(v[k].END, rt);
        memset (tmp, 0, sizeof (tmp));
        for (int i = 1; i <= cnt; i++)
            for (int j = 1; j <= cnt; j++)
                if (mp[a[i]][a[j]])
                    tmp[a[i]] += F[v[k].END][a[j]];
        for (int i = 1; i <= n; i++)
            F[rt][i] *= tmp[i];
    }
}
int main()
{
    memset (first, -1, sizeof (first));
    n = read(), m = read();
    for (int i = 1; i <= m; i++)
    {
        int a = read(), b = read();
        mp[a][b] = mp[b][a] = 1;
    }
    for (int i = 1; i < n; i++)
    {
        int a = read(), b = read();
        // G[a].push_back(b), G[b].push_back(a);
        add(a, b);
        add(b, a);
    }
    int N = (1 << n) - 1;
    long long ans = 0;
    for (S = 1; S <= N; S++)
    {
        cnt = 0;
        for (int i = 1; i <= n; i++) if ((1 << (i - 1)) & S) a[++cnt] = i;
        DFS(1, 0);
        int T = (Size(S ^ N) & 1) ? -1 : 1;
        for (int i = 1; i <= n; i++) ans += T * F[1][i];
    }
    printf ("%lld\n", ans);
    // while (1);
}