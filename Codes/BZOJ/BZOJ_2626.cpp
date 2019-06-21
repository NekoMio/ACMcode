#pragma GCC optimize("O")
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const long long INF = 0x3f3f3f3f3f3f3f3fll;

const int MAXN = 1e5 + 5;

char xch,xB[1<<15],*xS=xB,*xTT=xB;
#define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
inline int read()
{
    int x=0,f=1;char ch=getc();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getc();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getc();}
    return x*f;
}

int now;

struct Point
{
    long long d[2];
    int id;
    Point(long long x = 0, long long y = 0)
    {
        d[0] = x, d[1] = y;
    }
    long long &operator[](const int &x) 
    {
        return d[x];
    }
    bool operator < (const Point &a) const 
    {
        return d[now] == a.d[now] ? d[now ^ 1] < a.d[now ^ 1] : d[now] < a.d[now];
    }
    bool operator == (const Point &a) const 
    {
        return d[0] == a.d[0] && d[1] == a.d[1];
    }
}a[MAXN], cur;

long long dis(Point x, Point y)
{
    return (x[0] - y[0]) * (x[0] - y[0]) + (x[1] - y[1]) * (x[1] - y[1]);
}

struct Node
{
    Node *ch[2];
    Point v;
    long long Min[2], Max[2];
    Node (Point x)
    {
        ch[0] = ch[1] = NULL;
        v = x;
        Min[0] = Max[0] = x[0];
        Min[1] = Max[1] = x[1];
    }
    Node (){;}
    void Pushup(Node *rt)
    {
        if (!rt) return;
        for (int i = 0; i <= 1; i++) Min[i] = min(Min[i], rt->Min[i]);
        for (int i = 0; i <= 1; i++) Max[i] = max(Max[i], rt->Max[i]);
    }
    long long max_dis()
    {
        long long ans = 0;
        ans = max(ans, dis(cur, Point(Min[0], Min[1])));
        ans = max(ans, dis(cur, Point(Min[0], Max[1])));
        ans = max(ans, dis(cur, Point(Max[0], Min[1])));
        ans = max(ans, dis(cur, Point(Max[0], Max[1])));
        return ans;
    }
    void *operator new (size_t);
}*root, *C, *mempool;

void* Node::operator new(size_t)
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
    int mid = l + r >> 1;
    now = d;
    nth_element(a + l, a + mid, a + r + 1);
    rt = new Node(a[mid]);
    Build(rt->ch[0], l, mid - 1, d ^ 1);
    Build(rt->ch[1], mid + 1, r, d ^ 1);
    rt->Pushup(rt->ch[0]);
    rt->Pushup(rt->ch[1]);
}

struct data
{
    long long dis;
    int id;
    data(long long x, int i)
    {
        dis = x, id = i;
    }
    bool operator < (const data &x) const 
    {
        return dis == x.dis ? id < x.id : dis > x.dis;
    }
};

priority_queue<data> Q;

int K;

void Query(Node *rt)
{
    if (rt == NULL) return;
    if (Q.size() == K && rt->max_dis() < Q.top().dis) return;
    data now = data(dis(rt->v, cur), rt->v.id);
    if (Q.size() < K) Q.push(now);
    else if (now < Q.top()) Q.pop(), Q.push(now);
    long long dis_l = rt->ch[0] ? rt->ch[0]->max_dis() : INF;
    long long dis_r = rt->ch[1] ? rt->ch[1]->max_dis() : INF;
    if (dis_l > dis_r)
    {
        Query(rt->ch[0]);
        if (dis_r >= Q.top().dis || Q.size() < K) Query(rt->ch[1]);
    }
    else
    {
        Query(rt->ch[1]);
        if (dis_l >= Q.top().dis || Q.size() < K) Query(rt->ch[0]);
    }
}

void Clear(priority_queue<data> &s)
{
    priority_queue<data> L;
    swap(L, s);
}

int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
        a[i][0] = read(), a[i][1] = read(), a[i].id = i;
    Build(root, 1, n);
    n = read();
    for (int i = 1; i <= n; i++)
    {
        cur[0] = read(), cur[1] = read(), K = read();
        Clear(Q);
        Query(root);
        printf ("%d\n", Q.top().id);
    }
    // while (1);
}
