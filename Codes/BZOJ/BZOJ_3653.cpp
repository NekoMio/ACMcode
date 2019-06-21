/*  
    线段树套主席树？
    怎么跟闹着玩儿似的。
    还是离线树状数组+莫队吧
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
// #include <ctime>
using namespace std;
const int MAXN = 3e5 + 5;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct edge
{
    int END, next;
}v[MAXN << 1];
int first[MAXN], p;
inline void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int dep[MAXN], size[MAXN], Id[MAXN], Index;
int R[MAXN], Maxdep;
inline void dfs(int rt, int fa)
{
    Id[rt] = ++Index;
    dep[Id[rt]] = dep[Id[fa]] + 1;
    Maxdep = max(Maxdep, dep[Id[rt]]);
    size[Id[rt]] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        dfs(v[i].END, rt);
        size[Id[rt]] += size[Id[v[i].END]];
    }
    R[Id[rt]] = Index;
}
int a[MAXN];
bool cmp(const int &a, const int &b)
{
    return dep[a] < dep[b];
}
struct Node
{
    Node *ch[2];
    long long Sum;
    Node()
    {
        ch[0] = ch[1] = NULL;
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
    if (rt2 == null) rt1 = null;
    else rt1 = NewNode(), *rt1 = *rt2;
}
inline void Update(Node *&rt1, Node *rt2, int l, int r, int x, int val)
{
    copy(rt1, rt2);
    if (rt1 == null) rt1 = NewNode(); 
    rt1->Sum += val;
    if (l == r) return;
    int mid = l + r >> 1;
    if (x <= mid)
        Update(rt1->ch[0], rt2->ch[0], l, mid, x, val);
    else
        Update(rt1->ch[1], rt2->ch[1], mid + 1, r, x, val);
}
inline void Update(int x, int y, int val, int pos)
{
    Update(root[x], root[y], 1, Index, pos, val);
}
inline long long Query(Node *rt1, Node *rt2, int l, int r, int L, int R)
{
    if (L <= l && R >= r)
        return rt1->Sum - rt2->Sum;
    int mid = l + r >> 1;
    long long ans = 0;
    if (L <= mid) ans += Query(rt1->ch[0], rt2->ch[0], l, mid, L, R);
    if (R > mid) ans += Query(rt1->ch[1], rt2->ch[1], mid + 1, r, L, R);
    return ans;
}
int main()
{
	freopen ("laugh.in", "r", stdin);
    freopen ("laugh.out", "w", stdout);
	null = new Node();
    null->ch[0] = null->ch[1] = null;
    root[0] = null;
    memset (first, -1, sizeof (first));
    int n = read(), q = read();
    for (int i = 1; i < n; i++)
    {
        int a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) a[i] = i;
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++)
        Update(dep[a[i]], dep[a[i - 1]], size[a[i]] - 1, a[i]);
    for (int i = 1; i <= q; i++)
    {
        int p = read(), k = read();
        long long ans = 1ll * (size[Id[p]] - 1) * (dep[Id[p]] > k ? k : dep[Id[p]] - 1);
        ans += Query(root[dep[Id[p]] + k > Maxdep ? Maxdep : dep[Id[p]] + k], root[dep[Id[p]]], 1, Index, Id[p] + 1, R[Id[p]]);
        printf ("%lld\n", ans);
    }
    // printf ("%f\n", (double)clock() / CLOCKS_PER_SEC);
    // while (1);
}
