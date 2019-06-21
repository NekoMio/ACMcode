#pragma GCC optimize("O3")

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

const int N = 8e4 + 5, full = 16;

struct edge
{
    int END, next;
}v[N << 2];

int first[N], p;

void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}

struct Trie_Node
{
    int s;
    Trie_Node *ch[2];
    Trie_Node()
    {
        s = 0;
        ch[0] = ch[1] = NULL;
    }
}*root[N], *null;

Trie_Node *NewNode()
{
    Trie_Node *o = new Trie_Node();
    o->ch[0] = o->ch[1] = null;
    return o;
}

struct Trie
{
    void copy(Trie_Node *&rt1, Trie_Node *rt2)
    {
        if (rt2 == null)
            rt1 = null;
        else
        {
            rt1 = NewNode();
            *rt1 = *rt2;
        }
    }
    void remove(Trie_Node *&rt)
    {
        if (rt != null)
        {
            remove(rt->ch[0]);
            remove(rt->ch[1]);
            delete rt;
            rt = null;
        }
    }
    void Insert(int x, int a, int b)
    {
        // remove(root[a]);
        copy(root[a], root[b]);
        Trie_Node *rt1 = root[a], *rt2 = root[b];
        for (int i = full; i >= 0; i--)
        {
            int nxt = (x >> i) & 1;
            copy(rt1->ch[nxt], rt2->ch[nxt]);
            if (rt1->ch[nxt] == null) rt1->ch[nxt] = NewNode();
            rt1 = rt1->ch[nxt], rt2 = rt2->ch[nxt];
            rt1->s++;
        }
    }
    int Query(int k, int a, int b, int l, int fl)
    {
        Trie_Node *rt1 = root[a], *rt2 = root[b], *rt3 = root[l], *rt4 = root[fl];
        int res = 0;
        for (int i = full; i >= 0; i--)
        {
            if (k > rt1->ch[0]->s + rt2->ch[0]->s - rt3->ch[0]->s - rt4->ch[0]->s)
            {
                k -= rt1->ch[0]->s + rt2->ch[0]->s - rt3->ch[0]->s - rt4->ch[0]->s;
                res |= (1 << i);
                rt1 = rt1->ch[1], rt2 = rt2->ch[1], rt3 = rt3->ch[1], rt4 = rt4->ch[1];
            }
            else
                rt1 = rt1->ch[0], rt2 = rt2->ch[0], rt3 = rt3->ch[0], rt4 = rt4->ch[0];
        }
        return res;
    }
}op;

int val[N], id[N], Index, dep[N], size[N];

int f[N << 2][18];

void dfs(int x, int fa)
{
    if (!id[x]) id[x] = ++Index;
    dep[x] = dep[fa] + 1;
    size[x] = 1;
    op.Insert(val[x], id[x], id[fa]);
    f[x][0] = fa;
    for (int i = 1; i <= 17; i++) f[x][i] = f[f[x][i - 1]][i - 1];
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        dfs(v[i].END, x);
        size[x] += size[v[i].END];
    }
}

int LCA(int a, int b)
{
    if (dep[a] < dep[b]) swap(a, b);
    int d = dep[a] - dep[b];
    for (int i = 17; i >= 0; i--)
        if (d & (1 << i))
            d -= (1 << i), a = f[a][i];
    if (a == b) return a;
    for (int i = 17; i >= 0; i--)
        if (f[a][i] != f[b][i])
            a = f[a][i], b = f[b][i];
    return f[a][0];
}

int father[N], Size[N];

int find(int x)
{
    if (father[x] != x) father[x] = find(father[x]);
    return father[x];
}

void Merge(int a, int b)
{
    int x = find(a), y = find(b);
    Size[x] += Size[y];
    father[y] = x;
}

int Hash[N];

int main()
{
    // freopen("rforest0.in", "r", stdin);
    null = new Trie_Node();
    null->ch[0] = null->ch[1] = null;
    root[0] = NewNode();
    for (int i = 1; i < N; i++) root[i] = null;
    int tastcase = read();
    memset (first, -1, sizeof (first));
    int n, m, t, a, b, k;
    n = read(), m = read(), t = read();
    for (int i = 1; i <= n; i++) father[i] = i, Size[i] = 1;
    for (int i = 1; i <= n; i++) val[i] = read();
    for (int i = 1; i <= n; i++) Hash[i] = val[i];
    sort(Hash + 1, Hash + n + 1);
    int cnt = unique(Hash + 1, Hash + n + 1) - Hash - 1;
    for (int i = 1; i <= n; i++) val[i] = lower_bound(Hash + 1, Hash + cnt + 1, val[i]) - Hash;
    for (int i = 1; i <= m; i++)
    {
        a = read(), b = read();
        add(a, b);
        add(b, a);
        Merge(a, b);
    }
    for (int i = 1; i <= n; i++)
        if (!id[i])
            dfs(i, 0);
    char c[10];
    int lastans = 0;
    while (t--)
    {
        scanf ("%s", c);
        if (c[0] == 'Q')
        {
            a = read() ^ lastans, b = read() ^ lastans, k = read() ^ lastans;
            int lca = LCA(a, b);
            printf ("%d\n", lastans = Hash[op.Query(k, id[a], id[b], id[lca], id[f[lca][0]])]);
        }
        else if (c[0] == 'L')
        {
            a = read() ^ lastans, b = read() ^ lastans;
            add(a, b);
            add(b, a);
            if (Size[find(a)] < Size[find(b)]) dfs(a, b);
            else dfs(b, a);
            Merge(a, b);
        }
    }
}