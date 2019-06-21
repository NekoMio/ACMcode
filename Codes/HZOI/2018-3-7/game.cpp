#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int INF = 0x3f3f3f3f;
const int MAXN = 2e5 + 5;
struct edge
{
    int END, next;
}v[MAXN * 6];
int first[MAXN], p;
int c[MAXN];
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
long long st[MAXN], top;
long long f[MAXN];
int son[MAXN];
void dfs(int rt, int fa)
{
    f[rt] = c[rt];
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        dfs(v[i].END, rt);
        if (f[rt] < c[rt] + f[v[i].END])
        {
            son[rt] = v[i].END;
            f[rt] = c[rt] + f[v[i].END];
        }
    }
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END != son[rt])
            st[++top] = f[v[i].END];
    }
}
bool cmp(const long long &a, const long long &b)
{
    return a > b;
}
int main()
{
    // freopen ("game.in", "r", stdin);
    // freopen ("game.out", "w", stdout);
    memset (first, -1, sizeof (first));
    int n = read(), k = read();
    for (int i = 1; i <= n; i++)
        c[i] = read();
    for (int i = 1; i < n; i++)
    {
        int a = read(), b = read();
        add(a, b);
    }
    dfs(1, 0);
    st[++top] = f[1];
    sort(st + 1, st + top + 1, cmp); 
    long long ans = 0;
    for (int i = 1; i <= k; i++)
        ans += st[i];
    printf ("%lld\n", ans);
}