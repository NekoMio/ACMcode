#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1e5 + 5;
const double eps = 1e-9;
const double INF = 1e300;
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
struct Point
{
    double x, y;
    Point() {}
    Point(double a, double b): x(a), y(b) {}
    Point operator + (const Point &a)
    {
        return Point(x + a.x, y + a.y);
    }
    Point operator - (const Point &a)
    {
        return Point(x - a.x, y - a.y);
    }
    double operator * (const Point &a)
    {
        return x * a.y - y * a.x;
    }
    bool operator < (const Point &a) const 
    {
        return x < a.x || x == a.x && y < a.y;
    }
}Point1[MAXN], Point2[MAXN], tmp[MAXN];
double K(const Point &a, const Point &b)
{
    if (fabs(a.x - b.x) < eps)
        return a.y < b.y ? INF : -INF;
    return (a.y - b.y) / (a.x - b.x);
}
struct data
{
    double y, q, x, p;
}a[MAXN];
int fa[MAXN], son[MAXN], dep[MAXN], size[MAXN];
int top[MAXN], id[MAXN], num[MAXN], Index;
void DFS1(int rt, int f)
{
    dep[rt] = dep[f] + 1;
    fa[rt] = f;
    size[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == f) continue;
        DFS1(v[i].END, rt);
        size[rt] += size[v[i].END];
        if (size[v[i].END] > size[son[rt]])
            son[rt] = v[i].END;
    }
}
void DFS2(int rt, int t)
{
    num[id[rt] = ++Index] = rt;
    top[rt] = t;
    if (son[rt]) DFS2(son[rt], t);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa[rt] || v[i].END == son[rt]) continue;
        DFS2(v[i].END, v[i].END);
    }
}
int st[MAXN];
struct Seg_Tree
{
    int n;
    struct Node
    {
        Node *ch[2];
        vector<Point> v1, v2;
        void *operator new (size_t)
        {
            static Node mempool[MAXN << 2], *C = mempool;
            return C++;
        }
        Node()
        {
            ch[0] = ch[1] = NULL;
        }
    }*root;
    void Update(int l, int r, Node *rt)
    {
        for (int i = l; i <= r; i++) tmp[i] = Point1[num[i]];
        sort(tmp + l, tmp + r + 1);
        int s = 0;
        for (int i = l; i <= r; i++)
        {
            while (s >= 2 && K(tmp[st[s - 1]], tmp[st[s]]) < K(tmp[st[s]], tmp[i])) s--;
            st[++s] = i;
        }
        // printf ("%d %d\n", l, r);
        for (int i = 1; i <= s; i++) 
        // {
            rt->v1.push_back(tmp[st[i]]);
            // printf ("%lf %lf\n", tmp[st[i]].x, tmp[st[i]].y);
        // }
        for (int i = l; i <= r; i++) tmp[i] = Point2[num[i]];
        sort(tmp + l, tmp + r + 1);
        s = 0;
        for (int i = l; i <= r; i++)
        {
            while (s >= 2 && K(tmp[st[s - 1]], tmp[st[s]]) < K(tmp[st[s]], tmp[i])) s--;
            st[++s] = i;
        }
        for (int i = 1; i <= s; i++)
        // { 
            rt->v2.push_back(tmp[st[i]]);
        //     printf ("%lf %lf\n", tmp[st[i]].x, tmp[st[i]].y);
        // }
    }
    void Build(int l, int r, Node *rt)
    {
        Update(l, r, rt);
        if (l == r) return;
        int mid = l + r >> 1;
        Build(l, mid, rt->ch[0] = new Node());
        Build(mid + 1, r, rt->ch[1] = new Node());
    }
    void Build(int x)
    {
        n = x;
        root = new Node();
        Build(1, n, root);
    }
    double Calc(const vector<Point> &vc, double mi)
    {
        int l = 0, r = vc.size();
        // int ans = 0;
        while (l + 1 < r)
        {
            int mid = l + r >> 1;
            if (K(vc[mid - 1], vc[mid]) > mi - eps)
                l = mid;
            else
                r = mid;
        }
        // printf ("%lf %lf\n", vc[l].y, vc[l].x);
        return vc[l].y - mi * vc[l].x;
    }
    double Query(int l, int r, Node *rt, int L, int R, double mid, bool flag)
    {
        if (L <= l && R >= r)
            return (flag ? Calc(rt->v1, mid) : Calc(rt->v2, mid));
        int mi = l + r >> 1;
        double ans = -INF;
        if (L <= mi) 
            ans = max(ans, Query(l, mi, rt->ch[0], L, R, mid, flag));
        if (R > mi)
            ans = max(ans, Query(mi + 1, r, rt->ch[1], L, R, mid, flag));
        return ans;
    }
    double Query(int l, int r, double mid, bool flag)
    {
        return Query(1, n, root, l, r, mid, flag);
    }
}Tree;
double Query(int a, int b, double mid, bool flag)
{
    double ans = -INF;
    while (top[a] != top[b])
    {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        ans = max(ans, Tree.Query(id[top[a]], id[a], mid, flag));
        a = fa[top[a]];
    }
    if (dep[a] < dep[b])
        swap(a, b);
    ans = max(ans, Tree.Query(id[b], id[a], mid, flag));
    return ans;
}
int main()
{
    memset (first, -1, sizeof (first));
    int n = read();
    for (int i = 1; i <= n; i++) scanf("%lf", &a[i].x);
    for (int i = 1; i <= n; i++) scanf("%lf", &a[i].y);
    for (int i = 1; i <= n; i++) Point1[i].x = a[i].x, Point1[i].y = a[i].y;
    for (int i = 1; i <= n; i++) scanf("%lf", &a[i].p);
    for (int i = 1; i <= n; i++) scanf("%lf", &a[i].q);
    for (int i = 1; i <= n; i++) Point2[i].x = a[i].p, Point2[i].y = a[i].q;
    for (int i = 1; i < n; i++)
    {
        int a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    DFS1(1, 0);
    DFS2(1, 0);
    Tree.Build(n);
    int m = read();
    while (m--)
    {
        int a = read(), b = read();
        double l = 0, r = 1e8;
        while (r - l >= 1e-5)
        {
            double mid = (r + l) / 2;
            if (Query(a, b, mid, 1) + Query(a, b, mid, 0) > 0)
                l = mid;
            else r = mid;
        }
        printf ("%.4lf\n", l);
    }
}

