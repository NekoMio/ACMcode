// #pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 50005;
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
int MaX, t, n, m;
void DFS(int rt, int fa, int d)
{
    if (d > MaX) MaX = d, t = rt;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        DFS(v[i].END, rt, d + v[i].v);
    }
}
int du[MAXN];
vector<int> vc, vcc[MAXN * 15];
int RT[MAXN * 15];
bool vis[MAXN];
int size[MAXN], Max[MAXN], root, Sum, sum;
long long mid;
void Get_Root(int rt, int fa)
{
    size[rt] = 1;
    Max[rt] = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (!vis[v[i].END] && v[i].END != fa)
        {
            Get_Root(v[i].END, rt);
            size[rt] += size[v[i].END];
            Max[rt] = max(Max[rt], size[v[i].END]);
        }
    }
    Max[rt] = max(Max[rt], Sum - size[rt]);
    if (Max[rt] < Max[root]) root = rt;
}
void DFSDIS(int rt, int fa, int d, vector<int> &vct)
{
    vct.push_back(d);
    for (int i = first[rt]; i != -1; i = v[i].next)
        if (v[i].END != fa && !vis[v[i].END])
            DFSDIS(v[i].END, rt, d - v[i].v, vct);
}
int id = 0;
inline int Calc(int rt, int len)
{
    id++;
    int ans = 0;
    // cnt = 0;
    // DFSDIS(rt, 0, len);
    // sort(dis + 1, dis + cnt + 1);
    for (int l = 0, r = vcc[id].size() - 1; l <= r; )
        if (vcc[id][l] + vcc[id][r] <= -mid) ans += r - l, l++;
        else r--;
    return ans;
}
struct data
{
    int a, b;
    data(int _a = 0, int _b = 0): a(_a), b(_b) {}
    bool operator < (const data &c) const
    {
        return a > c.a;
    }
}vccans[MAXN * 20];
int vvv, cnt;
void Update(int rt, int op)
{
    id++;
    for (int l = 0, r = vcc[id].size() - 1; l <= r; )
        if (vcc[id][l] + vcc[id][r] <= -vvv)
        {
            for (int i = l + 1; i <= r; i++)
                vccans[++cnt] = data(- vcc[id][l] - vcc[id][i], op);
            l++;
        }
        else r--;
}
void build(int rt, int len)
{
    id++;
    DFSDIS(rt, 0, len, vcc[id]);
    sort(vcc[id].begin(), vcc[id].end());
}
void Solve_init(int rt)
{
    vis[rt] = 1;
    build(rt, 0);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (!vis[v[i].END])
        {
            build(v[i].END, -v[i].v);
            Sum = size[v[i].END];
            root = 0;
            Get_Root(v[i].END, 0);
            RT[id] = root;
            Solve_init(root);
        }
    }
}
void Solve(int rt)
{
    vis[rt] = 1;
    sum += Calc(rt, 0);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (!vis[v[i].END])
        {
            sum -= Calc(v[i].END, -v[i].v);
            // Sum = size[v[i].END];
            // root = 0;
            // Get_Root(v[i].END, 0);
            Solve(RT[id]);
        }
    }
}
void Solve2(int rt)
{
    vis[rt] = 1;
    Update(rt, 1);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (!vis[v[i].END])
        {
            Update(v[i].END, -1);
            // Sum = size[v[i].END];
            // root = 0;
            // Get_Root(v[i].END, 0);
            Solve2(RT[id]);
        }
    }
}
int main()
{
    // freopen ("tree3_10.in", "r", stdin);
    // freopen ("1.out", "w", stdout);
    memset (first, -1, sizeof (first));
    n = read(), m = read();
    for (int i = 1; i < n; i++)
    {
        int a = read(), b = read(), c = read();
        add(a, b, c);
        add(b, a, c);
        du[a]++, du[b]++;
    }
    long long l = 0, r = 0x3f3f3f3f;
    int ans = 0;
    root = 0, Max[0] = Sum = n;
    for (int i = 1; i <= n; i++) vis[i] = 0;
    Get_Root(1, 0);
    RT[id] = root;
    Solve_init(root);
    while (l <= r)
    {
        mid = l + r >> 1;
        sum = 0;
        id = 0;
        // root = 0, Max[0] = Sum = n;
        for (int i = 1; i <= n; i++) vis[i] = 0;
        // Get_Root(1, 0);
        Solve(RT[id]);
        if (sum >= m) l = mid + 1;
        else ans = mid, r = mid - 1;
    }
    vvv = ans - 1;
    // root = 0, Max[0] = Sum = n;
    id = 0;
    for (int i = 1; i <= n; i++) vis[i] = 0;
    // Get_Root(1, 0);
    cnt = 0;
    Solve2(RT[id]);
    sort(vccans + 1, vccans + cnt + 1);
    int t = 0;
    for (int i = 1; i <= cnt; i++)
    {
        int z = vccans[i].b, hdd = vccans[i].a;
        while (vccans[i + 1].a == hdd)
        {
            i++;
            z += vccans[i].b;
        } 
        for (; z; z--)
        {
            printf ("%d\n", hdd);
            t++;
            if (t == m) break;
        }
        if (t == m) break;
    }
    // while (1);
}
