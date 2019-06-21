#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = (5e4 + 5) * 2;
int MOD;
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
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int a[MAXN];
int Q[MAXN], Index, Dep[MAXN];
void DFS(int rt, int fa)
{
    Dep[rt] = Dep[fa] + 1;
    Q[++Index] = rt;
    // LNum[rt] = ++Index;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        DFS(v[i].END, rt);
    }
    // RNum[rt] = ++Index;
}
struct Node
{
    Node *ch[2], *fa;
    int s, v, dep, key;
    int SG[2], Min;
    Node(int x, int d, Node *f)
    {
        s = 1, v = x % MOD;
        dep = d, fa = f;
        SG[0] = SG[1] = 0;
        Min = d;
        key = rand();
        SG[dep & 1] = v;
        ch[0] = ch[1] = NULL;
    }
    void Pushup()
    {
        SG[0] = SG[1] = 0;
        Min = dep;
        SG[dep & 1] = v;
        s = 1;
        if (ch[0])
        {
            Min = min(Min, ch[0]->Min);
            SG[0] ^= ch[0]->SG[0];
            SG[1] ^= ch[0]->SG[1];
            // SG[0] %= MOD;
            // SG[1] %= MOD;
            s += ch[0]->s;
        }
        if (ch[1])
        {
            Min = min(Min, ch[1]->Min);
            SG[0] ^= ch[1]->SG[0];
            SG[1] ^= ch[1]->SG[1];
            // SG[0] %= MOD;
            // SG[1] %= MOD;
            s += ch[1]->s;
        }
    }
}*root, *id[MAXN];
#define size(_) ((_)?(_)->s:0)
#define MIN(_) ((_)?(_)->Min:0x3f3f3f3f)
Node *Build(int l, int r, Node *f)
{
    if (l > r) return NULL;
    int mid = l + r >> 1;
    Node *o = new Node(a[Q[mid]], Dep[Q[mid]], f);
    id[Q[mid]] = o;
    o->ch[0] = Build(l, mid - 1, o);
    o->ch[1] = Build(mid + 1, r, o);
    o->Pushup();
    return o;
}
Node *Merge(Node *A, Node *B)
{
    if (!A) return B;
    if (!B) return A;
    if (A->key > B->key)
    {
        A->ch[1] = Merge(A->ch[1], B);
        if (A->ch[1]) A->ch[1]->fa = A;
        A->Pushup();
        return A;
    }
    else
    {
        B->ch[0] = Merge(A, B->ch[0]);
        if (B->ch[0]) B->ch[0]->fa = B;
        B->Pushup();
        return B;
    }
}
typedef pair<Node*, Node*> DNode;
DNode Split(Node *rt, int k)
{
    if (!rt) return DNode(NULL, NULL);
    DNode o;
    if (size(rt->ch[0]) >= k)
    {
        o = Split(rt->ch[0], k);
        rt->ch[0] = o.second;
        if (o.second) o.second->fa = rt;
        rt->Pushup();
        rt->fa = NULL;
        o.second = rt;
    }
    else
    {
        o = Split(rt->ch[1], k - size(rt->ch[0]) - 1);
        rt->ch[1] = o.first;
        if (o.first) o.first->fa = rt;
        rt->Pushup();
        rt->fa = NULL;
        o.first = rt;
    }
    return o;
}
void Insert(int i, int x, int d, int k)
{
    DNode y = Split(root, k);
    Node *o = new Node(x, d, NULL);
    id[i] = o;
    root = Merge(y.first, Merge(o, y.second));
    if (root) root->fa = NULL;
}
int Qrank(Node *rt)
{
    int Sum = size(rt->ch[0]);
    Node *pre = rt;
    while (rt)
    {
        rt = rt->fa;
        if (rt && rt->ch[1] == pre) Sum += size(rt->ch[0]) + 1;
        pre = rt;
    }
    return Sum;
}
Node *QDep(Node *rt, int dep)
{
    if (!rt) return NULL;
    if (min(rt->dep, MIN(rt->ch[0])) > dep)
        return QDep(rt->ch[1], dep);
    else if (MIN(rt->ch[0]) > dep) return rt;
    else return QDep(rt->ch[0], dep);
}
int Query(int x)
{
    int L = Qrank(id[x]);
    DNode y = Split(root, L);
    DNode tmp = Split(y.second, 1);
    int R = Qrank(QDep(tmp.second, id[x]->dep));
    DNode z = Split(tmp.second, R);
    Node *ans = Merge(tmp.first, z.first);
    int ret = ans->SG[(id[x]->dep & 1) ^ 1] > 0;
    root = Merge(y.first, Merge(ans, z.second));
    if (root) root->fa = NULL;
    return ret;
}
int main()
{
    // freopen("Wildrage.in", "r", stdin);
    // freopen(".out", "w", stdout);
    memset (first, -1, sizeof (first));
    int n = read();
    MOD = read() + 1;
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i < n; i++)
    {
        int a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    Q[++Index] = 5e4 + 1;
    DFS(1, 0);
    Q[++Index] = 5e4 + 2;
    root = Build(1, Index, NULL);
    int ID = n, last = 0;
    int m = read();
    for (int i = 1; i <= m; i++)
    {
        // last = 0;
        int op = read();
        if (op == 1)
        {
            int ans = Query(read() ^ last);
            last += ans;
            puts (ans ? "MeiZ" : "GTY");
        }
        else if (op == 2)
        {
            int x = read() ^ last, y = read() ^ last;
            int tmp = id[x]->v;
            id[x]->v = y % MOD;
            for (Node *i = id[x]; i; i = i->fa) //Update(i, y % MOD, tmp, id[x]->dep & 1);
                i->Pushup();
        }
        else if (op == 3)
        {
            int u = read() ^ last, x = read() ^ last, y = read() ^ last;
            Dep[x] = Dep[u] + 1;
            int k = Qrank(id[u]);
            Insert(x, y, Dep[x], k + 1);
        }
    }
}