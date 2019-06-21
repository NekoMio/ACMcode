#include <cstdio>
#include <algorithm>
#include <cstring>

#define int long long

using namespace std;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

const int N = 100005;

struct edge
{
    int END, next;
}v[N << 1];
int first[N], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}


int dep[N], size[N], fa[N], son[N], id[N], top[N], Index;
void DFS1(int rt, int Dep, int f)
{
    dep[rt] = Dep;
    size[rt] = 1;
    fa[rt] = f;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == f) continue;
        DFS1(v[i].END, Dep + 1, rt);
        size[rt] += size[v[i].END];
        if (size[v[i].END] > size[son[rt]]) son[rt] = v[i].END;
    }
}

void DFS2(int rt, int t)
{
    id[rt] = ++Index;
    top[rt] = t;
    if (son[rt]) DFS2(son[rt], t);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa[rt] || v[i].END == son[rt]) continue;
        DFS2(v[i].END, v[i].END);
    }
}

struct Chairman_Tree
{
    struct Node
    {
        int Sum, val, d;
        Node *ch[2];
        Node()
        {
            ch[0] = ch[1] = NULL;
            Sum = 0, val = 0, d = 0;
        }
    }*root[N << 1], *null;
    int Index, Last;
    Chairman_Tree()
    {
        null = new Node();
        null->ch[0] = null->ch[1] = null;
        root[0] = null;
        Index = Last = 0;
    }
    Node *NewNode()
    {
        Node *o = new Node();
        o->ch[0] = o->ch[1] = null;
        return o;
    }
    void copy(Node *&rt1, Node *rt2)
    {
        if (rt2 == null)
            rt1 = null;
        else
            rt1 = NewNode(), *rt1 = *rt2;
    }
    void Update(int L, int R, int val, int d, int l, int r, Node *&rt1, Node *rt2)
    {
        int len = r - l + 1;
        if (L == l && R == r)
        {
            rt1->val += val;
            rt1->d += d;
            rt1->Sum += len * val + len * (len - 1) / 2 * d;
            return;
        }
        int m = l + r >> 1;
        if (R <= m) 
        {
            if (rt1->ch[0] == rt2->ch[0]) copy(rt1->ch[0], rt2->ch[0]);
            if (rt1->ch[0] == null) rt1->ch[0] = NewNode();
            Update(L, R, val, d, l, m, rt1->ch[0], rt2->ch[0]);
        }
        else if (L > m)
        {
            if (rt1->ch[1] == rt2->ch[1]) copy(rt1->ch[1], rt2->ch[1]); 
            if (rt1->ch[1] == null) rt1->ch[1] = NewNode();
            Update(L, R, val, d, m + 1, r, rt1->ch[1], rt2->ch[1]);
        }
        else
        {
            if (rt1->ch[0] == rt2->ch[0]) copy(rt1->ch[0], rt2->ch[0]);
            if (rt1->ch[1] == rt2->ch[1]) copy(rt1->ch[1], rt2->ch[1]); 
            if (rt1->ch[0] == null) rt1->ch[0] = NewNode();
            if (rt1->ch[1] == null) rt1->ch[1] = NewNode();
            Update(L, m, val, d, l, m, rt1->ch[0], rt2->ch[0]);
            Update(m + 1, R, val + (m - L + 1) * d, d, m + 1, r, rt1->ch[1], rt2->ch[1]);
        }
        rt1->Sum = rt1->ch[0]->Sum + rt1->ch[1]->Sum + len * rt1->val + len * (len - 1) / 2 * rt1->d;
    }
    void Update(int L, int R, int val, int d)
    {
        Update(L, R, val, d, 1, ::Index, root[Index], root[Last]);
    }
    int Query(int L, int R, int l, int r, Node *rt)
    {
        if (L == l && R == r)
            return rt->Sum;
        if (rt == null) return 0;
        int ans = (rt->val + (L - l) * rt->d) * (R - L + 1) + (R - L + 1) * (R - L) / 2 * rt->d;
        int m = l + r >> 1;
        if (R <= m) return Query(L, R, l, m, rt->ch[0]) + ans;
        else if (L > m) return Query(L, R, m + 1, r, rt->ch[1]) + ans;
        else return Query(L, m, l, m, rt->ch[0]) + Query(m + 1, R, m + 1, r, rt->ch[1]) + ans;
    }
    int Query(int L, int R, int l, int r)
    {
        return Query(L, R, l, r, root[Last]);
    }
}root;

int Get_Lca(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    return x;
}

void Update(int x, int y, int lca, int val, int d)
{
    int len = dep[x] + dep[y] - 2 * dep[lca] + 1;
    int tmp = val;
    root.Index++;
    root.copy(root.root[root.Index], root.root[root.Last]);
    if (root.root[root.Index] == root.null) root.root[root.Index] = root.NewNode();
    while (top[x] != top[lca])
    {
        root.Update(id[top[x]], id[x], tmp += (dep[x] - dep[top[x]]) * d, -d);
        x = fa[top[x]];
        tmp += d;
    }
    root.Update(id[lca], id[x], tmp + (dep[x] - dep[lca]) * d, -d);
    tmp = val + (len - 1) * d;
    while (top[y] != top[lca])
    {
        root.Update(id[top[y]], id[y], tmp -= (dep[y] - dep[top[y]]) * d, d);
        y = fa[top[y]];
        tmp -= d;
    }
    root.Update(id[lca], id[y], tmp - (dep[y] - dep[lca]) * d, d);
    root.Update(id[lca], id[lca], -(tmp - (dep[y] - dep[lca]) * d), -d);
    root.Last = root.Index;
}

int Query(int x, int y)
{
    int ans = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        ans += root.Query(id[top[x]], id[x], 1, Index);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    ans += root.Query(id[x], id[y], 1, Index);
    return ans;
}

signed main()
{
    int n = read(), m = read();
    memset (first, -1, sizeof (first));
    int a, b;
    for (int i = 1; i < n; i++)
    {
        a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    DFS1(1, 0, 0);
    DFS2(1, 1);
    char c[10];
    int val, d;
    int lastans = 0;
    while (m--)
    {
        scanf ("%s", c);
        if (c[0] == 'c')
        {
            a = read() ^ lastans, b = read() ^ lastans, val = read(), d = read();
            int lca = Get_Lca(a, b);
            Update(a, b, lca, val, d);
        }
        else if (c[0] == 'q')
        {
            a = read() ^ lastans, b = read() ^ lastans;
            printf ("%lld\n", lastans = Query(a, b));
        }
        else
        {
            root.Last = read() ^ lastans;
        }
    }
    // while (1);
}