#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}

const int INF = 0x3f3f3f3f;
const double alpha = 0.755;
const int MAXN = 100005;


int now;
struct Point
{
    int d[2], v;
    int &operator[](const int &x)
    {
        return d[x];
    }
    bool operator < (const Point &a) const 
    {
        return d[now] == a.d[now] ? d[now ^ 1] < a.d[now ^ 1] : d[now] < a.d[now];
    }
}cur, cur1;

struct Node
{
    Node *ch[2];
    Point v;
    int Max[2], Min[2], s, d;
    Node(Point x)
    {
        ch[0] = ch[1] = NULL;
        v = x;
        s = 1;
        d = now;
        Max[0] = Min[0] = x[0];
        Min[1] = Max[1] = x[1];
    }
    #define size(_) ((_)?(_)->s : 0)
    bool IsBad()
    {
        return ((size(ch[0]) > s * alpha) || (size(ch[1]) > s * alpha));
    }
    void Pushup(Node *x)
    {
        if (!x) return;
        s += x->s;
        for (int i = 0; i <= 1; i++) Max[i] = max(Max[i], x->Max[i]);
        for (int i = 0; i <= 1; i++) Min[i] = min(Min[i], x->Min[i]);
    }
};

Node **res;

inline void Insert(Node *&rt)
{
    if (rt == NULL)
    {
        now ^= 1;
        rt = new Node(cur);
        res = NULL;
        return;
    }
    now = rt->d;
    if (cur < rt->v) Insert(rt->ch[0]);
    else Insert(rt->ch[1]);
    rt->s = 1;
    rt->Pushup(rt->ch[0]);
    rt->Pushup(rt->ch[1]);
    if (rt->IsBad()) res = &rt;
}

Node *st[MAXN << 1];
int top = 0;
  
inline void Travel(Node *&rt)
{
    if (!rt) return;
    Travel(rt->ch[0]);
    st[++top] = rt;
    Travel(rt->ch[1]);
}

inline int cmp(const Node *x, const Node *y)
{
    return x->v < y->v;
}
  
inline Node *Divide(int l, int r, int d)
{
    if (l > r) return NULL;
    int mid = l + r >> 1;
    now = d;
    nth_element(st + l, st + mid, st + r + 1, cmp);
    Node *rt = st[mid];
    rt->d = d;
    rt->ch[0] = Divide(l, mid - 1, d ^ 1);
    rt->ch[1] = Divide(mid + 1, r, d ^ 1);
    rt->s = 1;
    rt->Max[0] = rt->Min[0] = rt->v[0];
    rt->Max[1] = rt->Min[1] = rt->v[1];
    rt->Pushup(rt->ch[0]);
    rt->Pushup(rt->ch[1]);
    return rt;
}
  
inline void ReBuild(Node *&rt)
{
    top = 0;
    int d = rt->d;
    Travel(rt);
    rt = Divide(1, top, d);
}

// inline void Insert(Point x)
// {
//     cur = x;
//     Insert(root);
//     if (res != NULL)
//         ReBuild(*res);
// }

struct Seg_Node
{
    Seg_Node *ch[2];
    Node *rt;
    Seg_Node()
    {
        ch[0] = ch[1] = NULL;
        rt = NULL;
    }
}*root = new Seg_Node;


void Insert(Seg_Node *&rt, int l, int r)
{
    res = NULL;
    Insert(rt->rt);
    if (res != NULL) ReBuild(*res);
    if (l == r) return;
    int mid = l + r >> 1;
    if (cur.v <= mid)
    {
        if (rt->ch[0] == NULL) rt->ch[0] = new Seg_Node();
        Insert(rt->ch[0], l, mid);
    }
    else
    {
        if (rt->ch[1] == NULL) rt->ch[1] = new Seg_Node();
        Insert(rt->ch[1], mid + 1, r);
    }
}

void Insert(Point x)
{
    cur = x;
    Insert(root, 1, INF);
}

#define Judge(_) (\
((_)[0] >= cur[0] && (_)[0] <= cur1[0] && (_)[1] >= cur[1] && (_)[1] <= cur1[1])\
)

bool All(Node *rt)
{
    for (int i = 0; i <= 1; i++) if (rt->Max[i] > cur1[i]) return 0;
    for (int i = 0; i <= 1; i++) if (rt->Min[i] < cur[i]) return 0;
    return 1;
}

#define No(_) (\
((_)->Max[0] < cur[0] || (_)->Min[0] > cur1[0] || (_)->Max[1] < cur[1] || (_)->Min[1] > cur1[1])\
)

bool Have(Node *rt)
{
    Point x;
    x[0] = rt->Max[0], x[1] = rt->Max[1];
    if (Judge(x)) return 1;
    x[0] = rt->Max[0], x[1] = rt->Min[1];
    if (Judge(x)) return 1;
    x[0] = rt->Min[0], x[1] = rt->Max[1];
    if (Judge(x)) return 1;
    x[0] = rt->Min[0], x[1] = rt->Min[1];
    if (Judge(x)) return 1;
    return 0;
}

int Query(Node *rt)
{
    if (!rt) return 0;
    int ans = 0;
    if (Judge(rt->v)) ans += 1;
    if (rt->ch[0] && All(rt->ch[0])) ans += rt->ch[0]->s;
    else if (rt->ch[0] && !No(rt->ch[0])) ans += Query(rt->ch[0]);
    if (rt->ch[1] && All(rt->ch[1])) ans += rt->ch[1]->s;
    else if (rt->ch[1] && !No(rt->ch[1])) ans += Query(rt->ch[1]);
    return ans;
}

inline int Query(Seg_Node *rt)
{
    if (!rt) return 0;
    return Query(rt->rt);
}

int lastans = 0;

void Query(Point a, Point b, int k)
{
    cur = a, cur1 = b;
    if (Query(root) < k) return lastans = 0, printf ("NAIVE!ORZzyz.\n"), void();
    Seg_Node *rt = root;
    int l = 1, r = INF;
    while (l < r)
    {
        int mid = l + r >> 1;
        int ans = Query(rt->ch[1]);
        if (k > ans) k -= ans, rt = rt->ch[0], r = mid;
        else rt = rt->ch[1], l = mid + 1;
    }
    printf ("%d\n", lastans = l);
}

int main()
{
    int n = read(), Q = read();
    Point x, a;
    while (Q--)
    {
        // lastans = 0;
        int op = read();
        if (op == 1)
        {
            x[0] = read() ^ lastans, x[1] = read() ^ lastans, x.v = read() ^ lastans;
            Insert(x);
        }
        else
        {
            x[0] = read() ^ lastans, x[1] = read() ^ lastans, a[0] = read() ^ lastans, a[1] = read() ^ lastans;
            Query(x, a, read() ^ lastans);
        }
    }
    // while (1);
}