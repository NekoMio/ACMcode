#include <cstdio>
#include <cstring>
#include <algorithm>
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
#define size(_) ((_)?(_)->s : 0)
#define Sum(_) ((_)?(_)->Sum : 0)
const int MAXN = 2e5 + 5;
int n, K;
struct Node
{
    Node *ch[2];
    int s, fs, Sum;
    Node()
    {
        ch[0] = ch[1] = NULL;
        s = fs = Sum = 0;
    }
    void Pushup()
    {
        s = size(ch[0]) + size(ch[1]) + fs;
        Sum = Sum(ch[0]) + Sum(ch[1]);
    }
};
void Update(int x, int l, int r, Node *rt)
{
    // rt->s++;
    if (l == r)
    {
        rt->s = 1;
        rt->fs = 1;
        rt->Sum++;
        return;
    }
    int mid = l + r >> 1;
    if (x <= mid)
    {
        if (rt->ch[0] == NULL) rt->ch[0] = new Node();
        Update(x, l, mid, rt->ch[0]);
    }
    else
    {
        if (rt->ch[1] == NULL) rt->ch[1] = new Node();
        Update(x, mid + 1, r, rt->ch[1]);
    }
    rt->Pushup();
}
Node *Merge(Node *rt1, Node *rt2, int l, int r)
{
    if (!rt2) return rt1;
    if (!rt1) return rt2;
    Node *o = new Node();
    if (l == r)
    {
        rt1->Sum += rt2->Sum;
        return rt1;
    }
    int mid = l + r >> 1;
    o->ch[0] = Merge(rt1->ch[0], rt2->ch[0], l, mid);
    o->ch[1] = Merge(rt1->ch[1], rt2->ch[1], mid + 1, r);
    o->Pushup();
    return o;
}
long long ans[MAXN];
void DFS(Node *rt, int l, int r, int x)
{
    if (l == r)
    {
        ans[l] += 1ll * rt->Sum * x;
        return;
    }
    int mid = l + r >> 1;
    if (rt->ch[0]) DFS(rt->ch[0], l, mid, x);
    if (rt->ch[1]) DFS(rt->ch[1], mid + 1, r, x);
}
struct edge
{
    int END, next;
}v[MAXN << 2];
int first[MAXN << 1], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
struct SAM
{
    int last, cnt;
    int trans[MAXN << 1][26], fa[MAXN << 1], Max[MAXN << 1];
    Node *root[MAXN];
    SAM()
    {
        last = ++cnt;
    }
    void extend(int c, int x)
    {
        int p = last, np = last = ++cnt;
        if (root[np] == NULL) root[np] = new Node();
        Update(x, 1, n, root[np]);
        Max[np] = Max[p] + 1;
        while (!trans[p][c] && p) trans[p][c] = np, p = fa[p];
        if (!p) fa[np] = 1;
        else
        {
            int q = trans[p][c];
            if (Max[q] == Max[p] + 1) fa[np] = q;
            else
            {
                int nq = ++cnt;
                Max[nq] = Max[p] + 1;
                memcpy(trans[nq], trans[q], sizeof (trans[nq]));
                fa[nq] = fa[q];
                fa[q] = fa[np] = nq;
                while (trans[p][c] == q) trans[p][c] = nq, p = fa[p];
            }
        }
    }
    void ADD()
    {
        for (int i = 1; i <= cnt; i++)
            add(fa[i], i);
    }
    void dfs(int rt = 1)
    {
        for (int i = first[rt]; i != -1; i = v[i].next)
        {
            dfs(v[i].END);
            root[rt] = Merge(root[rt], root[v[i].END], 1, n);
        }
        if (size(root[rt]) >= K)
        {
            DFS(root[rt], 1, n, Max[rt] - Max[fa[rt]]);
        }
    }
}sam;
char s[MAXN];
int main()
{
    memset (first, -1, sizeof (first));
    n = read(), K = read();
    int len = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf ("%s", s + 1);
        sam.last = 1;
        int m = strlen(s + 1);
        for (int j = 1; j <= m; j++)
            sam.extend(s[j] - 'a', i);
    }
    sam.ADD();
    sam.dfs();
    // sam.dfs();
    for (int i = 1; i <= n; i++)
        printf ("%lld\n", ans[i]);
}