#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const long long INF = 0x3f3f3f3f3f3f3f3f;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = (1e5 + 5) * 2;
int fa[MAXN];
int a[MAXN];
struct edge
{
    int END, next;
}v[MAXN];
int first[MAXN], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
struct Node
{
    Node *f, *ch[2];
    long long DP[2][2], Sum[2];
}*Q[MAXN], *null;
Node *NewNode(int x)
{
    Node *o = new Node();
    o->f = o->ch[0] = o->ch[1] = null;
    o->DP[0][1] = o->DP[1][0] = -INF;
    o->DP[0][0] = o->Sum[0] = 0;
    o->Sum[1] = o->DP[1][1] = x;
    return o;
}
void Pushup(Node *rt)
{
    if (rt == null) return;
    rt->DP[0][0] = rt->DP[1][1] = rt->DP[1][0] = rt->DP[0][1] = -INF;
    if (rt->ch[0] == null)
    {
        if (rt->ch[1] == null) rt->DP[1][1] = rt->Sum[1], rt->DP[0][0] = rt->Sum[0];
        else
        {
            for (int i = 0; i <= 1; i++) rt->DP[1][i] = max(rt->DP[1][i], rt->Sum[1] + rt->ch[1]->DP[0][i]);
            for (int i = 0; i <= 1; i++)
                for (int j = 0; j <= 1; j++)
                    rt->DP[0][i] = max(rt->DP[0][i], rt->Sum[0] + rt->ch[1]->DP[j][i]);
        }
    }
    else if (rt->ch[1] == null)
    {
        for (int i = 0; i <= 1; i++) rt->DP[i][1] = max(rt->DP[i][1], rt->Sum[1] + rt->ch[0]->DP[i][0]);
        for (int i = 0; i <= 1; i++)
            for (int j = 0; j <= 1; j++)
                rt->DP[i][0] = max(rt->DP[i][0], rt->Sum[0] + rt->ch[0]->DP[i][j]);
    }
    else
    {
        for (int i = 0; i <= 1; i++)
            for (int j = 0; j <= 1; j++)
            {
                rt->DP[i][j] = max(rt->DP[i][j], max(rt->Sum[1], rt->Sum[0]) + rt->ch[0]->DP[i][0] + rt->ch[1]->DP[0][j]);
                rt->DP[i][j] = max(rt->DP[i][j], rt->Sum[0] + rt->ch[0]->DP[i][1] + rt->ch[1]->DP[1][j]);
                rt->DP[i][j] = max(rt->DP[i][j], rt->Sum[0] + rt->ch[0]->DP[i][0] + rt->ch[1]->DP[1][j]);
                rt->DP[i][j] = max(rt->DP[i][j], rt->Sum[0] + rt->ch[0]->DP[i][1] + rt->ch[1]->DP[0][j]);
            }
    }
}
bool son(Node *rt)
{
    return rt->f->ch[1] == rt;
}
bool IsRoot(Node *rt)
{
    return rt->f->ch[0] != rt && rt->f->ch[1] != rt;
}
void rotate(Node *rt)
{
    if (IsRoot(rt)) return;
    Node *fa = rt->f, *Grand = fa->f;
    int tmp = IsRoot(fa);
    int k = son(rt), kk = son(fa);
    fa->ch[k] = rt->ch[k ^ 1];
    if (rt->ch[k ^ 1] != null) rt->ch[k ^ 1]->f = fa;
    rt->ch[k ^ 1] = fa, fa->f = rt, rt->f = Grand;
    if (!tmp) Grand->ch[kk] = rt;
    Pushup(fa), Pushup(rt);
}
void Splay(Node *rt)
{
    for (; !IsRoot(rt); rotate(rt))
        if (!IsRoot(rt->f))
            rotate(son(rt->f) == son(rt) ? rt->f : rt);
}
void Access(Node *rt)
{
    for (Node *pre = null; rt != null; pre = rt, rt = rt->f)
    {
        Splay(rt);
        if (rt->ch[1] != null) 
        {
            rt->Sum[1] += max(rt->ch[1]->DP[0][1], rt->ch[1]->DP[0][0]);
            rt->Sum[0] += max(max(rt->ch[1]->DP[0][0], rt->ch[1]->DP[0][1]), max(rt->ch[1]->DP[1][0], rt->ch[1]->DP[1][1]));
        }
        if (pre != null)
        {
            rt->Sum[1] -= max(pre->DP[0][1], pre->DP[0][0]);
            rt->Sum[0] -= max(max(pre->DP[0][0], pre->DP[0][1]), max(pre->DP[1][0], pre->DP[1][1]));
        }
        rt->ch[1] = pre;
        Pushup(rt);
    }
}
long long Query(Node *rt)
{
    Access(rt), Splay(rt);
    return max(rt->Sum[0], rt->Sum[1]);
}
void dfs(int rt)
{
    Q[rt]->Sum[1] = a[rt];
    Q[rt]->Sum[0] = 0;
    Q[rt]->f = Q[fa[rt]];
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        dfs(v[i].END);
        Q[rt]->Sum[1] += Q[v[i].END]->Sum[0];
        Q[rt]->Sum[0] += max(Q[v[i].END]->Sum[0], Q[v[i].END]->Sum[1]);
    }
    Q[rt]->DP[1][1] = Q[rt]->Sum[1];
    Q[rt]->DP[0][0] = Q[rt]->Sum[0];
}
int main()
{
    // freopen ("lily1.in", "r", stdin);
    // freopen ("lily1.out", "w", stdout);
    null = new Node();
    null->ch[0] = null->ch[1] = null->f = null;
    // null->Sum[0] = null->Sum[1] = 0;
    Q[0] = null;
    memset (first, -1, sizeof (first));
    int n = read(), m = read();
    for (int i = 1; i < n; i++)
    {
        fa[i + 1] = read();
        add(fa[i + 1], i + 1);
    }
    for (int i = 1; i <= n; i++)
        Q[i] = NewNode(a[i] = read());
    dfs(1);
    char s[10];
    while (m--)
    {
        scanf ("%s", s);
        if (s[0] == 'A')
        {
            n++;
            fa[n] = read();
            a[n] = read();
            Q[n] = NewNode(a[n]);
            Access(Q[fa[n]]);
            Splay(Q[fa[n]]);
            Q[n]->f = Q[fa[n]];
            Q[fa[n]]->Sum[0] += max(0, a[n]);
            Pushup(Q[fa[n]]);
        }
        else if (s[0] == 'C')
        {
            int x = read(), y = read();
            Access(Q[x]), Splay(Q[x]);
            Q[x]->Sum[1] += y - a[x], a[x] = y;
            Pushup(Q[x]);
        }
        else
            printf ("%lld\n", Query(Q[read()]));
    }
}