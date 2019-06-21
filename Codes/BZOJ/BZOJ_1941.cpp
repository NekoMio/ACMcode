#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 5e5 + 5;

const long long INF = 0x3f3f3f3f3f3f3f3fll;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

int now;

struct Point
{
    long long d[2];
    long long &operator[](const int &x) 
    {
        return d[x];
    }
    bool operator < (const Point &a) const
    {
        return d[now] == a.d[now] ? d[now ^ 1] < a.d[now ^ 1] : d[now] < a.d[now];
    }
    bool operator != (const Point &a) const 
    {
        return d[1] != a.d[1] || d[0] != a.d[0];
    }
}cur, a[MAXN];

long long dis(Point x, Point y)
{
    return abs(x[0] - y[0]) + abs(x[1] - y[1]);
}

struct Node
{
    Node *ch[2];
    Point v;
    long long Min[2], Max[2];
    Node(Point x)
    {
        ch[0] = ch[1] = NULL;
        v = x;
        Min[0] = Max[0] = x[0];
        Min[1] = Max[1] = x[1];
    }
    void Pushup(Node *x)
    {
        if (!x) return;
        for (int i = 0; i <= 1; i++) Min[i] = min(Min[i], x->Min[i]);
        for (int i = 0; i <= 1; i++) Max[i] = max(Max[i], x->Max[i]);
    }
    long long min_dis()
    {
        long long ans = 0;
        ans += max(Min[0] - cur[0], 0ll) + max(cur[0] - Max[0], 0ll);
        ans += max(Min[1] - cur[1], 0ll) + max(cur[1] - Max[1], 0ll);
        return ans;
    }
    long long max_dis()
    {
        long long ans = 0;
        ans += max(abs(cur[0] - Min[0]), abs(cur[0] - Max[0]));
        ans += max(abs(cur[1] - Min[1]), abs(cur[1] - Max[1]));
        return ans;
    }
}*root;

void build(Node *&rt, int l, int r, int d = 0)
{
    if (l > r) return;
    int mid = l + r >> 1;
    now = d;
    nth_element(a + l, a + mid, a + r + 1);
    rt = new Node(a[mid]);
    build(rt->ch[0], l, mid - 1, d ^ 1);
    build(rt->ch[1], mid + 1, r, d ^ 1);
    rt->Pushup(rt->ch[0]);
    rt->Pushup(rt->ch[1]);
    return;
}

long long Ans_min, Ans_max;

void Query_min(Node *rt)
{
    if (rt == NULL) return;
    if (rt->v != cur) Ans_min = min(Ans_min, dis(cur, rt->v));
    long long dis_l = rt->ch[0] ? rt->ch[0]->min_dis():INF;
    long long dis_r = rt->ch[1] ? rt->ch[1]->min_dis():INF;
    if (dis_l < dis_r) 
    {
        if (rt->ch[0]) Query_min(rt->ch[0]);
        if (dis_r <= Ans_min && rt->ch[1]) Query_min(rt->ch[1]);
    }
    else
    {
        if (rt->ch[1]) Query_min(rt->ch[1]);
        if (dis_l <= Ans_min && rt->ch[0]) Query_min(rt->ch[0]);        
    }
}

void Query_max(Node *rt)
{
    if (rt == NULL) return;
    if (rt->v != cur) Ans_max = max(Ans_max, dis(cur, rt->v));
    long long dis_l = rt->ch[0] ? rt->ch[0]->max_dis():INF;
    long long dis_r = rt->ch[1] ? rt->ch[1]->max_dis():INF;
    if (dis_l > dis_r) 
    {
        if (rt->ch[0]) Query_max(rt->ch[0]);
        if (dis_r >= Ans_max && rt->ch[1]) Query_max(rt->ch[1]);
    }
    else
    {
        if (rt->ch[1]) Query_max(rt->ch[1]);
        if (dis_l >= Ans_max && rt->ch[0]) Query_max(rt->ch[0]);
    }
}

long long Query_max(Point x)
{
    cur = x;
    Ans_max = -INF;
    Query_max(root);
    return Ans_max;
}

long long Query_min(Point x)
{
    cur = x;
    Ans_min = INF;
    Query_min(root);
    return Ans_min;
}


int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
        a[i][0] = read(), a[i][1] = read();
    build(root, 1, n);
    long long Mininum = INF;
    for (int i = 1; i <= n; i++) 
    {
        Mininum = min(Mininum, Query_max(a[i]) - Query_min(a[i]));
    }
    printf ("%d\n", Mininum);
}
