#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
using namespace __gnu_pbds;
template<typename _Tp1, typename _Tp2>
inline void gmin(_Tp1 &x, const _Tp2 &y) { if (x > y) x = y; }
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 2e5 + 5;
struct edge
{
    int END, next, v;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].v = c;
    v[p].next = first[a];
    first[a] = p++;
}
int val[MAXN], fa[MAXN];
int Hash[MAXN], cnt;
void DFS(int rt, int f)
{
    fa[rt] = f;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == f) continue;
        val[v[i].END] = v[i].v;
        DFS(v[i].END, rt);
    }
}
long long h[MAXN];
struct data
{
    int x, k;
    data(int _x, int _k): x(_x), k(_k) {}
    bool operator < (const data &a) const
    {
        return x == a.x ? k > a.k : x > a.x;
    }
};
__gnu_pbds::priority_queue<data, less<data>, pairing_heap_tag> Q[MAXN];
vector<data> vc;
void DP(int rt)
{
    Q[rt].push(data(0, -1));
    h[rt] = val[rt];
    Q[rt].push(data(val[rt], 2));
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa[rt]) continue;
        DP(v[i].END);
        h[rt] += h[v[i].END];
        Q[rt].join(Q[v[i].END]);
    }
    int k = 0, lastx = Q[rt].top().x;
    long long H = h[rt];
    while (Q[rt].top().k < 0 || k < 0)
    {
        int x = Q[rt].top().x;
        vc.clear();
        while (!Q[rt].empty() && Q[rt].top().x == x)
        {
            vc.push_back(Q[rt].top());
            Q[rt].pop();
        }
        H = H + 1ll * k * (x - lastx);
        for (auto z : vc) k += z.k;
        if (k >= 0)
        {
            Q[rt].push(data(x, k));
            h[rt] = H;
            break;
        }
        lastx = x;
    }
}
int main()
{
    int T = read();
    while (T--)
    {
        memset (first, -1, sizeof (first)), p = 0;
        int n = read();
        for (int i = 1; i <= n - 1; i++)
        {
            int a = read(), b = read(), c = read();
            add(a, b, c);
            add(b, a, c);
            Hash[i] = c;
        }
        Hash[n] = 0;
        sort(Hash + 1, Hash + n + 1);
        cnt = unique(Hash + 1, Hash + n + 1) - Hash - 1;
        DFS(1, 0);
        DP(1);
        printf ("%lld\n", h[1]);
    }
    // while (1);
}
