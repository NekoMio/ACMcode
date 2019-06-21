#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <list>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
FILE *f1, *f2;
int Index;
const int INF = 0x3f3f3f3f;
struct Node
{
    int l, r;
    int m, t, tp, id;
    Node *ch[2];
    Node()
    {
        ch[0] = ch[1] = NULL;
        m = l = r = 0;
        id = ++Index;
    }
}*root;
const int MAXN = 4005;
list<Node*> ls[MAXN], s[MAXN];
struct edge
{
    int END, next, cap;
}v[2000005];
int first[MAXN * 30], p;
void add(int a, int b, int f)
{
    #ifdef Mine
    fprintf (stderr, "%d %d %d\n", a, b, f);
    #endif
    v[p].END = b, v[p].next = first[a], v[p].cap = f, first[a] = p++;
    v[p].END = a, v[p].next = first[b], v[p].cap = 0, first[b] = p++;
}
int dis[MAXN * 30];
bool vis[MAXN * 30];
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
#define ID(__, _) ((_) == 1 ? (__) << 1 | 1 : (__) << 1)
int S, T;
bool flag = 0;
bool DFS(int l, int r, Node *&rt, int tp)
{
	rt = new Node();
	if (rt != root)
	{
		if (!tp) ls[l].push_back(rt);
		s[l].push_back(rt);
		// return;
	}
	rt->tp = tp;
	rt->l = l, rt->r = r;
	rt->t = read();
	#ifdef Mine
	fprintf (f1, "%d %d %d: %d\n", l, r, rt->t, rt->id);
	#endif
	if (l == r)
	{
	    if (rt->t == 1)
	    {
		    add(ID(rt->id, 0), ID(rt->id, 1), INF);
	        add(ID(rt->id, 0), T, 1);
	        add(S, ID(rt->id, 1), 1);
	    }
	    return rt->t;
	}
	rt->m = read();
    int st = DFS(l, rt->m, rt->ch[0], 0);
    st |= DFS(rt->m + 1, r, rt->ch[1], 1);
    if (!st && rt->t == 1)
    {
	    add(ID(rt->id, 0), T, 1);
	    add(S, ID(rt->id, 1), 1);
    }
    if (rt->t == 1)
        add(ID(rt->id, 0), ID(rt->id, 1), INF);
    if (st && !rt->t) flag = 1;
    st |= rt->t;
    return st;
}
int ss = 2, tt = 3;
int sta[MAXN];
void dfs(int l, int r, Node *rt)
{
    if (rt->tp == 1)
    {
        /* for (auto x : s[r + 1])
            add(ID(rt->id, 1), ID(x->id, 0), INF);
        */
        if (s[r + 1].size()) 
            add(ID(rt->id, 1), sta[r + 1], INF);
    }
    else
    {
        for (auto x : ls[r + 1])
            add(ID(rt->id, 1), ID(x->id, 0), INF);
    }
    add(ss, ID(rt->id, 0), INF);
    add(ID(rt->id, 1), tt, INF);
    if (l == r) return;
    dfs(l, rt->m, rt->ch[0]);
    dfs(rt->m + 1, r, rt->ch[1]);
}
int main()
{
    #ifdef Mine
	freopen ("1.in", "r", stdin);
	freopen ("1.out", "w", stderr);
	f1 = fopen ("2.out", "w");
    #endif
    memset (first, -1, sizeof (first));
    int n = read();
    S = 0, T = 1;
    ss = 2, tt = 3;
    Index = 2;
    DFS(1, n, root, 0);
    if (flag) return printf ("OwO\n"), 0;
    Index = 2 * Index + 2;
    for (int i = 1; i <= n; i++)
        if (s[i].size())
            sta[i] = ++Index;
    dfs(1, n, root);
    for (int i = 1; i <= n; i++)
        for (auto x : s[i])
            add(sta[i], ID(x->id, 0), INF);
    Dinic(S, T);
    add(tt, ss, INF);
    Dinic(S, T);
    printf ("%d\n", v[p - 1].cap);
}
