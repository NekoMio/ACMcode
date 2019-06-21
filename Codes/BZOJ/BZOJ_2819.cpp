#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 500005;
struct edge
{
    int next, END;
} v[N << 1];
int first[N], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int dep[N], size[N], fa[N], id[N], son[N], top[N], Index;
void dfs1(int x, int f, int Dep)
{
    dep[x] = Dep;
    size[x] = 1;
    fa[x] = f;
    son[x] = 0;
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (v[i].END == f) continue;
        dfs1(v[i].END, x, Dep + 1);
        size[x] += size[v[i].END];
        if (size[v[i].END] > size[son[x]])
            son[x] = v[i].END;
    }
}
void dfs2(int rt, int tp)
{
    top[rt] = tp;
    id[rt] = ++Index;
    if(son[rt]) dfs2(son[rt], tp);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if(v[i].END == fa[rt] || v[i].END == son[rt]) continue;
        dfs2(v[i].END, v[i].END);
    }
}
#define lowbit(_) ((_) & (-_))
int Xor[N], n;
void change(int x, int a)
{
    for (int i = x; i <= n; i+=lowbit(i))
        Xor[i] ^= a;
}
int Query(int x)
{
    int ans = 0;
    for (int i = x; i > 0; i-=lowbit(i))
        ans ^= Xor[i];
    return ans;
}
int Query(int a, int b)
{
    return Query(b) ^ Query(a - 1);
}
bool LCA(int x, int y)
{
    int now = 0;
    while (top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]])
            swap(x, y);
        now ^= Query(id[top[x]], id[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    now ^= Query(id[x], id[y]);
    return now;
}
int val[N];
int main()
{
    scanf("%d", &n);
    memset(first, -1, sizeof(first));
    int a, b;
    for (int i = 1; i <= n; i++) scanf("%d", &val[i]);
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &a, &b);
        add(a, b);
        add(b, a);
    }
    dfs1(1, 0, 0);
    dfs2(1, 1);
    for (int i = 1; i <= n; i++)
        change(id[i], val[i]);
    int Q;
    char s[5];
    scanf("%d", &Q);
    while(Q--)
    {
        scanf("%s", s);
        if (s[0] == 'C')
        {
            scanf("%d%d", &a, &b);
            change(id[a], b ^ val[a]);
            val[a] = b;
        }
        else 
        {
            scanf("%d%d", &a, &b);
            if (LCA(a, b))
                printf("Yes\n");
            else
                printf("No\n");
        }
    }
}