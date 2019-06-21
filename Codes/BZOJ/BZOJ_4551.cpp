#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 100005;
struct edge
{
    int END, next;
}v[MAXN << 1];
int first[MAXN], p;
int C[MAXN];
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int f[MAXN], fa[MAXN];
int find(int x)
{
    if (f[x] != x) f[x] = find(f[x]);
    return f[x];
}
void dfs(int rt)
{
    f[rt] = C[rt] ? rt : fa[rt];
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa[rt]) continue;
        fa[v[i].END] = rt;
        dfs(v[i].END);
    }
}
char op[MAXN];
int num[MAXN];
int ans[MAXN];
int main()
{
    // freopen ("heoi2016_tree.in", "r", stdin);
    // freopen ("heoi2016_tree.out", "w", stdout);
    memset (first, -1, sizeof (first));
    int n = read(), m = read();
    for (int i = 1; i < n; i++)
    {
        int a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    C[1] = 1;
    for (int i = 1; i <= m; i++)
    {
        op[i] = getchar();
        while (op[i] != 'C' && op[i] != 'Q') op[i] = getchar(); 
        num[i] = read();
        if (op[i] == 'C') C[num[i]]++;
    }
    dfs(1);
    for (int i = m; i >= 1; i--)
    {
        if (op[i] == 'Q') ans[i] = find(num[i]); 
        else 
        {
            C[num[i]]--;
            if (!C[num[i]]) f[num[i]] = f[fa[num[i]]];
        }
    }
    for (int i = 1; i <= m; i++)
        if (op[i] == 'Q')
            printf ("%d\n", ans[i]);
}