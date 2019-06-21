// #pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

using namespace std;

int now;

const int MAXN = 500005;
const double alpha = 0.9;
const int INF = 0x3f3f3f3f;

struct Point
{
    int d[2];
    inline int &operator[](const int &x)
    {
        return d[x];
    }
    inline bool operator < (const Point &a) const 
    {
        return d[now] == a.d[now] ? d[now ^ 1] < a.d[now ^ 1] : d[now] < a.d[now];
    }
}a[MAXN], cur;

#define dis(_, __) (\
    int(abs(_[0] - __[0]) + abs(_[1] - __[1]))\
)

struct Node
{
    Node *ch[2];
    Point v;
    int Max[2], Min[2], d;
    Node(Point x)
    {
        v = x;
        ch[0] = ch[1] = NULL;
        Max[0] = Min[0] = x[0];
        Max[1] = Min[1] = x[1];
    }
    Node() {;}
#define size(_) ((_) ? (_)->s : 0)
    inline void Pushup(Node *x)
    {
        if (!x) return;
        for (int i = 0; i <= 1; i++) Max[i] = max(Max[i], x->Max[i]);
        for (int i = 0; i <= 1; i++) Min[i] = min(Min[i], x->Min[i]);
    }
    inline int min_dis()
    {
        int ans = 0;
        ans += max(Min[0] - cur[0], 0) + max(cur[0] - Max[0], 0);
        ans += max(Min[1] - cur[1], 0) + max(cur[1] - Max[1], 0);
        return ans;
    }
    void *operator new (size_t s);
}*root, *C, *mempool;

void *Node::operator new (size_t s)
{
    if (C == mempool)
    {
        C = new Node[1 << 15];
        mempool = C + (1 << 15);
    }
    return C++;
}

void Build(Node *&rt, int l, int r, int d = 0)
{
    if (l > r) return;
    now = d;
    int mid = l + r >> 1;
    nth_element(a + l, a + mid, a + r + 1);
    rt = new Node(a[mid]);
    rt->d = now;
    Build(rt->ch[0], l, mid - 1, d ^ 1);
    Build(rt->ch[1], mid + 1, r, d ^ 1);
    rt->Pushup(rt->ch[0]);
    rt->Pushup(rt->ch[1]);
}

void Insert()
{
    Node **rt = &root;
    while (*rt)
    {
        now = (*rt)->d;
        for (int i = 0; i <= 1; i++) (*rt)->Max[i] = max((*rt)->Max[i], cur[i]);
        for (int i = 0; i <= 1; i++) (*rt)->Min[i] = min((*rt)->Min[i], cur[i]);
        if (cur < (*rt)->v) rt = &(*rt)->ch[0];
        else rt = &(*rt)->ch[1];
    }
    *rt = new Node(cur);
}

inline void Insert(Point x)
{
    cur = x;
    Insert();
}

int Min_ans;
void Query(Node *rt)
{
    if (!rt) return;
    Min_ans = min(Min_ans, dis(rt->v, cur));
    int dis_l = rt->ch[0] ? rt->ch[0]->min_dis() : INF;
    int dis_r = rt->ch[1] ? rt->ch[1]->min_dis() : INF;
    if (dis_l < dis_r)
    {
        if (rt->ch[0]) Query(rt->ch[0]);
        if (dis_r < Min_ans && rt->ch[1]) Query(rt->ch[1]); 
    }
    else
    {
        if(rt->ch[1]) Query(rt->ch[1]);
        if (dis_l < Min_ans && rt->ch[0]) Query(rt->ch[0]);
    }
}

inline int Query(Point x)
{
    cur = x;
    Min_ans = INF;
    Query(root);
    return Min_ans;
}

int main()
{
    int n = read(), m = read();
    for (int i = 1; i <= n; i++)
        a[i][0] = read(), a[i][1] = read();
    Build(root, 1, n);
    Point x;
    int op;
    while (m--)
    {
        op = read();
        if (op == 1)
        {
            x[0] = read(), x[1] = read();
            Insert(x);
        }
        else
        {
            x[0] = read(), x[1] = read();
            printf ("%d\n", Query(x));
        }
    }
}