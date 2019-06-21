#include <cstdio>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;
struct Seg_Node *null;
struct Seg_Node
{
    Seg_Node *ch[2];
    int cnt;
    //#define cnt(_) ((_) ? (_)->cnt : 0)
    Seg_Node(Seg_Node *l, Seg_Node *r)
    {
        ch[0] = l, ch[1] = r;
        cnt = ch[0]->cnt + ch[1]->cnt;
    }
    Seg_Node(Seg_Node *l, Seg_Node *r, int _cnt)
    {
        ch[0] = l, ch[1] = r;
        cnt = _cnt;
    }
    Seg_Node *insert(int l, int r, int x)
    {
        if (l == r)
            return new Seg_Node(null, null, cnt + 1);
        else
        {
            int m = l + (r - l) / 2;
            if (x <= m)
                return new Seg_Node(ch[0]->insert(l, m, x), ch[1]);
            else
                return new Seg_Node(ch[0], ch[1]->insert(m + 1, r, x));
        }
    }
};
struct Node
{
    vector<Node *> ch;
    Node *fa;
    int dep, w;
    bool vis;
    Seg_Node *Seg;
} v[100005];

void addedge(int a, int b)
{
    v[a].ch.push_back(&v[b]);
    v[b].ch.push_back(&v[a]);
}
void init()
{
    null = new Seg_Node(NULL, NULL, 0);
    null->ch[0] = null->ch[1] = null;
}
int n, f[100005][20], logn;
void build()
{
    v[0].vis = 1;
    v[0].Seg = null;
    queue<Node *> Q;
    Q.push(&v[1]);
    v[1].vis = 1;
    v[1].dep = 1;
    v[1].fa = &v[0];
    while (!Q.empty())
    {
        Node *e = Q.front();
        Q.pop();
        e->Seg = e->fa->Seg->insert(0, INT_MAX, e->w);
        for (Node **p = &e->ch.front(), *u = *p; p <= &e->ch.back(); u = *++p)
        {
            if (!u->vis)
            {
                u->vis = 1;
                u->dep = e->dep + 1;
                u->fa = e;
                Q.push(u);
            }
        }
    }
    while ((1 << (logn + 1)) <= n)
        logn++;
    f[1][0] = 1;
    for (int i = 2; i <= n; i++)
        f[i][0] = v[i].fa - v;
    for (int j = 1; j <= logn; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            f[i][j] = f[f[i][j - 1]][j - 1];
        }
    }
}
int lca(int s, int e)
{
    if (v[s].dep < v[e].dep)
        swap(s, e);
    if (v[s].dep > v[e].dep)
    {
        for (int i = logn; i >= 0; i--)
        {
            if (v[f[s][i]].dep >= v[e].dep)
                s = f[s][i];
        }
    }
    if (s != e)
    {
        for (int i = logn; i >= 0; i--)
        {
            if (f[s][i] != f[e][i])
            {
                s = f[s][i];
                e = f[e][i];
            }
        }
        return f[s][0];
    }
    return s;
}
int Query(int s, int e, int k)
{
    int p = lca(s, e);
    Seg_Node *Su = v[s].Seg, *Sv = v[e].Seg, *Sp = v[p].Seg, *Sf = v[p].fa->Seg;
    int l = 0, r = INT_MAX;
    while (l < r)
    {
        int m = l + (r - l) / 2;
        int S = Su->ch[0]->cnt + Sv->ch[0]->cnt - Sp->ch[0]->cnt - Sf->ch[0]->cnt;
        if (k > S)
        {
            k -= S;
            l = m + 1;
            Su = Su->ch[1];
            Sv = Sv->ch[1];
            Sp = Sp->ch[1];
            Sf = Sf->ch[1];
        }
        else
        {
            r = m;
            Su = Su->ch[0];
            Sv = Sv->ch[0];
            Sp = Sp->ch[0];
            Sf = Sf->ch[0];
        }
    }
    return l;
}
int main()
{
    int m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &v[i].w);
    for (int i = 1; i <= n - 1; i++)
    {
        int s, e;
        scanf("%d%d", &s, &e);
        addedge(s, e);
    }
    init();
    build();
    int ans = 0;
    while (m--)
    {
        int s, e, k;
        scanf("%d%d%d", &s, &e, &k);
        s ^= ans;
        printf(m ? "%d\n" : "%d", ans = Query(s, e, k));
    }
}