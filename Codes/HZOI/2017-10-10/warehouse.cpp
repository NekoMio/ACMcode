#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int END, next, v;
}v[200005];
int first[100005], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
int dis[100005], size[100005];
int cnt[100005][32], f[32], b[32], Q[32], n, M;
void DFS1(int rt, int fa, int Dep)
{
    size[rt] = 1;
    cnt[rt][0] += 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        DFS1(v[i].END, rt, Dep + v[i].v);
        dis[rt] += dis[v[i].END] + v[i].v * size[v[i].END];
        size[rt] += size[v[i].END];
        for (int j = 0; j <= 15; j++) cnt[rt][(j + v[i].v) & 15] += cnt[v[i].END][j];
    }
    
}
int ans[100005];
void Calc(int rt, int S)
{
    ans[rt] += S;
    for (int i = 0; i <= 15; i++)
        ans[rt] = ans[rt] - f[i] * i + f[i] * (i ^ M);
    ans[rt] -= M;
}
void DFS(int rt, int fa, int S)
{
    Calc(rt, S);
    int q[16];
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        memcpy(q, f, sizeof (q));
        memset(b, 0, sizeof (b));
        memset(Q, 0, sizeof (Q));
        for (int j = 0; j <= 15; j++) b[(j + v[i].v) & 15] += cnt[v[i].END][j];
        for (int j = 0; j <= 15; j++) f[j] -= b[j];
        for (int j = 0; j <= 15; j++) Q[(j + v[i].v) & 15] += f[j];
        for (int j = 0; j <= 15; j++) f[j] = Q[j] + cnt[v[i].END][j];
        DFS(v[i].END, rt, S + (n - size[v[i].END] - size[v[i].END]) * v[i].v);
        memcpy(f, q, sizeof (f));
    }
}
int main()
{
    memset(first, -1, sizeof (first));
    scanf ("%d%d", &n, &M);
    int a, b, c;
    for (int i = 1; i < n; i++)
    {
        scanf ("%d%d%d", &a, &b, &c);
        add(a, b, c);
        add(b, a, c);
    }
    DFS1(1, 0, 0);
    for (int i = 0; i <= 15; i++) f[i] = cnt[1][i];
    DFS(1, 0, dis[1]);
    for (int i = 1; i <= n; i++)
        printf ("%d\n", ans[i]);
    while (1);
}