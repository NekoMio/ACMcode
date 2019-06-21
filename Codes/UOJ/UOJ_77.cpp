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
const int MAXN = 10005;
const int INF = 0x3f3f3f3f;
int Index;
int a[MAXN], b[MAXN], w[MAXN], L[MAXN], R[MAXN], P[MAXN];
int H[MAXN * 2], n;
struct Node
{
    Node *ch[2];
    int id;
    Node()
    {
        ch[0] = ch[1] = NULL;
        id = ++Index;
    }
}*root[MAXN], *null;
Node *NewNode()
{
    Node *o = new Node();
    o->ch[0] = o->ch[1] = null;
    return o;
}
struct edge
{
    int END, next, cap;
}v[200005];
int first[MAXN], p;
void add(int a, int b, int c)
{
    v[p].END = b, v[p].next = first[a], v[p].cap = c, first[a] = p++;
    v[p].END = a, v[p].next = first[b], v[p].cap = 0, first[b] = p++;
}
int dis[MAXN];
bool vis[MAXN];
bool BFS(int S, int E)
{
    queue<int> Q;
    memset (vis, 0, sizeof (vis));
    memset (dis, -1, sizeof (dis));
    vis[S] = 1;
    dis[S] = 0;
    Q.push(S);
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (!vis[v[i].END] && v[i].cap > 0)
            {
                vis[v[i].END] = 1;
                dis[v[i].END] = dis[k] + 1;
                Q.push(v[i].END);
            }
        }
    }
    return vis[E];
}
int DFS(int S, int E, int a)
{
    if (S == E || a == 0) return a;
    int flow = 0, f;
    for (int i = first[S]; i != -1; i = v[i].next)
    {
        if (dis[v[i].END] == dis[S] + 1 && (f = DFS(v[i].END, E, min(a, v[i].cap))) > 0)
        {
            a -= f;
            flow += f;
            v[i].cap -= f;
            v[i ^ 1].cap += f;
            if (a == 0) break;
        }
    }
    if (!flow) dis[S] = -1;
    return flow;
}
int Dinic(int S, int E)
{
    int ans = 0;
    while (BFS(S, E))
    {
        ans += DFS(S, E, INF);
    }
    return ans;
}
void Link(Node *rt, int l, int r, int i)
{
    if (L[i] > r || R[i] < l) return;
    if (L[i] <= l && R[i] >= r)
    {
        add(i + n, rt->id, INF);
        return;
    }
    int mid = (l + r) >> 1;
    if (rt->ch[0] != null) Link(rt->ch[0], l, mid, i);
    if (rt->ch[1] != null) Link(rt->ch[1], mid + 1, r, i); 
}
void Insert(Node *&rt1, Node *rt2, int l, int r, int i)
{
    rt1 = new Node();
    if (l == r)
    {
        add(rt1->id, i, INF);
        if (rt2 != null) add(rt1->id, rt2->id, INF);
        return;
    }
    int mid = (l + r) >> 1;
    if (a[i] <= mid) rt1->ch[1] = rt2->ch[1], Insert(rt1->ch[0], rt2->ch[0], l, mid, i);
    else rt1->ch[0] = rt2->ch[0], Insert(rt1->ch[1], rt2->ch[1], mid + 1, r, i);
    if (rt1->ch[0] != null) add(rt1->id, rt1->ch[0]->id, INF);
    if (rt1->ch[1] != null) add(rt1->id, rt1->ch[1]->id, INF);
}
int main()
{
    null = new Node();
    null->ch[0] = null->ch[1] = null;
    memset (first, -1, sizeof (first));
    n = read();
    int S = 0, T = n * 2 + 1;
    int ans = 0;
    Index = T;
    int tot = 0;
    for (int i = 1; i <= n; i++)
    {
        a[i] = read(), b[i] = read(), w[i] = read(), L[i] = read(), R[i] = read(), P[i] = read();
        add(S, i, b[i]);
        add(i, T, w[i]);
        add(i, i + n, P[i]);
        H[++tot] = a[i], H[++tot] = L[i], H[++tot] = R[i];
        ans += w[i] + b[i];
    }
    root[0] = null;
    sort(H + 1, H + tot + 1);
    int cnt = unique(H + 1, H + tot + 1) - H - 1;
    for (int i = 1; i <= n; i++)
    {
        a[i] = lower_bound(H + 1, H + cnt + 1, a[i]) - H;
        R[i] = lower_bound(H + 1, H + cnt + 1, R[i]) - H;
        L[i] = lower_bound(H + 1, H + cnt + 1, L[i]) - H;
        if (i > 1) Link(root[i - 1], 1, cnt, i);
        Insert(root[i], root[i - 1], 1, cnt, i);
    }
    printf ("%d\n", ans - Dinic(S, T));
    // while (1);
}
