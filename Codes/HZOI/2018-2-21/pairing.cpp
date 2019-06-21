#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 200005;
int pos[MAXN];

map<int, int> a[MAXN << 1];
int fa[MAXN << 1], Max[MAXN << 1], last, cnt, val[MAXN << 1];
void extend(int c, int x)
{
    int p = last, np = last = ++cnt;
    Max[np] = Max[p] + 1, val[np] = x;
    while (!a[p].count(c)) a[p][c] = np, p = fa[p];
    if (!p) fa[np] = 1;
    else
    {
        int q = a[p][c];
        if (Max[q] == Max[p] + 1) fa[np] = q;
        else
        {
            int nq = ++cnt;
            Max[nq] = Max[p] + 1;
            a[nq] = a[q];
            fa[nq] = fa[q];
            fa[q] = fa[np] = nq;
            while (a[p][c] == q) a[p][c] = nq, p = fa[p];
        }
    }
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
int f[MAXN << 1][20];
int ID[MAXN << 1], Index, R[MAXN << 1];
void dfs(int rt)
{
    ID[rt] = ++Index;
    f[rt][0] = fa[rt];
    for (int i = 1; i <= 19; i++) f[rt][i] = f[f[rt][i - 1]][i - 1];
    for (int i = first[rt]; i != -1; i = v[i].next)
        dfs(v[i].END);
    R[rt] = Index;
}
struct Node
{
    Node *ch[2];
    int Sum;
    Node()
    {
        Sum = 0;
    }
}*root[MAXN], *null;
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
void Update(Node *rt1, Node *rt2, int l, int r, int pos, int c)
{
    rt1->Sum += c;
    if (l == r) return;
    int mid = l + r >> 1;
    if (pos <= mid)
    {
        copy(rt1->ch[0], rt2->ch[0]);
        if (rt1->ch[0] == null) rt1->ch[0] = NewNode();
        Update(rt1->ch[0], rt2->ch[0], l, mid, pos, c);
    }
    else
    {
        copy(rt1->ch[1], rt2->ch[1]);
        if (rt1->ch[1] == null) rt1->ch[1] = NewNode();
        Update(rt1->ch[1], rt2->ch[1], mid + 1, r, pos, c);
    }
}
int Query(Node *rt1, Node *rt2, int L, int R, int l, int r)
{
    if (L > R) return 0;
    if (L <= l && R >= r)
        return rt2->Sum - rt1->Sum;
    int mid = l + r >> 1;
    int ans = 0;
    if (L <= mid) ans += Query(rt1->ch[0], rt2->ch[0], L, R, l, mid);
    if (R > mid) ans += Query(rt1->ch[1], rt2->ch[1], L, R, mid + 1, r);
    return ans;
}
inline int Query(int L, int R, int l, int r)
{
    if (L > R) return 0;
    return Query(root[L], root[R], l, r, 1, Index);
}
int s[MAXN], b[MAXN];
int main()
{
    memset (first, -1, sizeof (first));
    null = new Node();
    null->ch[0] = null->ch[1] = null;
    last = ++cnt;
    root[0] = null;
    int n = read();
    for (int i = 1; i <= n; i++) s[i] = read();
    for (int i = 1; i < n; i++) b[i] = s[i + 1] - s[i];
    for (int i = n - 1; i >= 1; i--) 
    {
        extend(b[i], 1);
        pos[i] = last;
    }
    last = 1;
    for (int i = n - 1; i >= 1; i--)
    {
        extend(-b[i], 0);
        pos[i + n] = last;
    }
    for (int i = 2; i <= cnt; i++)
        add(fa[i], i);
    dfs(1);
    n--;
    for (int i = 1; i <= n; i++)
    {
        copy(root[i], root[i - 1]);
        if (root[i] == null) root[i] = NewNode();
        Update(root[i], root[i - 1], 1, Index, ID[pos[i]], 1);
    }
    int m = read();
    Max[0] = -1;
    for (int i = 1; i <= m; i++)
    {
        int l = read(), r = read() - 1;
        if (l > r)
        {
            printf ("%d\n", n);
            continue;
        }
        int len = r - l + 1;
        int t = pos[l + n + 1];
        for (int j = 19; j >= 0; j--)
            if (Max[f[t][j]] >= len)
                t = f[t][j];
        int ans = Query(0, l - len - 1, ID[t], R[t]);
        ans += Query(r + 1, n, ID[t], R[t]);
        printf ("%d\n", ans);
    }
    // while (1);
}