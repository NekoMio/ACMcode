#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define int long long

const int MAXN = 50005;
const long long INF = 0x3f3f3f3f3f3f3f3fll;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

int now;
struct data
{
    int d[2];
    int h;
    inline int &operator[](const int &x)
    {
        return d[x];
    }
    bool operator < (const data &a) const 
    {
        return d[now] == a.d[now] ? d[now ^ 1] < a.d[now ^ 1] : d[now] < a.d[now];
    }
}a[MAXN], cur;

struct Node
{
    Node *ch[2];
    data v;
    int Max[2], Min[2];
    long long s;
    Node(data x)
    {
        ch[0] = ch[1] = NULL;
        v = x;
        s = x.h;
        Max[0] = Min[0] = x[0];
        Max[1] = Min[1] = x[1];
    }
    void Pushup(Node *x)
    {
        if (!x) return;
        for (int i = 0; i <= 1; i++) Max[i] = max(Max[i], x->Max[i]);
        for (int i = 0; i <= 1; i++) Min[i] = min(Min[i], x->Min[i]);
        s += x->s;
    }
    long long calc_min()
    {
        long long ans = 0;
        if (cur[0] < 0) ans += (long long)cur[0] * Max[0];
        else ans += (long long)cur[0] * Min[0];
        if (cur[1] < 0) ans += (long long)cur[1] * Max[1];
        else ans += (long long)cur[1] * Min[1];
        return ans;
    }
    long long calc_max()
    {
        long long ans = 0;
        if (cur[0] < 0) ans += (long long)cur[0] * Min[0];
        else ans += (long long)cur[0] * Max[0];
        if (cur[1] < 0) ans += (long long)cur[1] * Min[1];
        else ans += (long long)cur[1] * Max[1];
        return ans;
    }
}*root;

void Build(Node *&rt, int l, int r, int d = 0)
{
    if (l > r) return;
    int mid = l + r >> 1; now = d;
    nth_element(a + l, a + mid, a + r + 1);
    rt = new Node(a[mid]);
    Build(rt->ch[0], l, mid - 1, d ^ 1);
    Build(rt->ch[1], mid + 1, r, d ^ 1);
    rt->Pushup(rt->ch[0]);
    rt->Pushup(rt->ch[1]);
}


long long ans, c;

#define Calc(_, __) (((long long)(_)[0]) * (__)[0] + ((long long)(_)[1]) * (__)[1])

void Query(Node *rt)
{
    if (!rt) return;
    if (Calc(cur, rt->v) < c) ans += rt->v.h;
    long long min_l = rt->ch[0] ? rt->ch[0]->calc_min() : INF;
    long long min_r = rt->ch[1] ? rt->ch[1]->calc_min() : INF;
    long long max_l = rt->ch[0] ? rt->ch[0]->calc_max() : INF;
    long long max_r = rt->ch[1] ? rt->ch[1]->calc_max() : INF;
    if (max_l < c) ans += rt->ch[0]->s;
    else if (min_l < c) Query(rt->ch[0]);
    if (max_r < c) ans += rt->ch[1]->s;
    else if (min_r < c) Query(rt->ch[1]);
}

long long Query(data x, int C)
{
    cur = x;
    ans = 0;
    c = C;
    Query(root);
    return ans;
}

signed main()
{
    // freopen("cho1.in", "r", stdin);
    // freopen("cho.out", "w", stdout);
    int n = read(), m = read();
    for (int i = 1; i <= n; i++)
        a[i][0] = read(), a[i][1] = read(), a[i].h = read();
    Build(root, 1, n);
    data x;
    int t;
    while (m--)
    {
        x[0] = read(), x[1] = read(), t = read();
        printf ("%lld\n", Query(x, t));
    }
    // while (1);
}