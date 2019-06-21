#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 2e5 + 5;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

struct edge
{
    int END, next, v;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].v = c;
    v[p].next = first[a];
    first[a] = p++;
}
int size[MAXN], Max[MAXN], root, sum;
bool vis[MAXN];
void Get_root(int rt, int fa)
{
    size[rt] = 1; Max[rt] = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END != fa && !vis[v[i].END])
        {
            Get_root(v[i].END, rt);
            size[rt] += size[v[i].END];
            Max[rt] = max(Max[rt], size[v[i].END]);
        }
    }
    Max[rt] = max(Max[rt], sum - size[rt]);
    if (Max[rt] < Max[root]) root = rt;
}
int d[MAXN];
long long t[4];
void dfs(int rt, int fa)
{
    t[d[rt]]++;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (!vis[v[i].END] && v[i].END != fa)
        {
            d[v[i].END] = (d[rt] + v[i].v) % 4;
            dfs(v[i].END, rt);
        }
    }
}

long long Calc(int rt, int S)
{
    t[0] = t[1] = t[2] = t[3] = 0;
    d[rt] = S;
    dfs(rt, 0);
    return t[0] * t[0] + t[1] * t[3] * 2 + t[2] * t[2];
}
long long ans = 0;
void Solve(int rt)
{
    ans += Calc(rt, 0);
    vis[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (!vis[v[i].END])
        {
            ans -= Calc(v[i].END, v[i].v);
            root = 0, sum = size[v[i].END];
            Get_root(v[i].END, 0);
            Solve(root);
        }
    }
}
long long gcd(long long a, long long b)
{
    return b == 0 ? a : gcd(b, a % b);
}
void Ans(int n)
{
    ans = 0;
    long long b = 1ll * n * n;
    root = 0, Max[0] = sum = n;
    Get_root(1, 0);
    Solve(root);
    long long g = gcd(ans, b);
    printf ("%lld/%lld\n", ans / g, b / g);
}
int main()
{
    while (1)
    {
        memset (first, -1, sizeof (first));
        p = 0;
        memset (vis, 0, sizeof (vis));
        int n = read();
        if (n == 0) break;
        for (int i = 1; i < n; i++)
        {
            int a = read(), b = read(), c = read() % 4;
            add(a, b, c);
            add(b, a, c);
        }
        Ans(n);
    }
}