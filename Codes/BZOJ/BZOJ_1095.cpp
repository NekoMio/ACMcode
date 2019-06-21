#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>
#include<ext/pb_ds/priority_queue.hpp>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='0')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 100005;
struct Priority_queue
{
    __gnu_pbds::priority_queue<int, less<int>, __gnu_pbds::binary_heap_tag> Q1, Q2;
    inline int size()
    {
        return Q1.size() - Q2.size();
    }
    inline void push(const int &x)
    {
        Q1.push(x);
    }
    inline void erase(const int &x)
    {
        Q2.push(x);
    }
    inline int top()
    {
        while (!Q2.empty() && Q1.top() == Q2.top())
        {
            Q1.pop();
            Q2.pop();
        }
        if (!Q1.empty()) return Q1.top();
        else return 0;
    }
    inline int top2()
    {
        if (size() < 2) return 0;
        while (!Q2.empty() && Q1.top() == Q2.top())
        {
            Q1.pop();
            Q2.pop();
        }
        int tmp = Q1.top(); Q1.pop();
        while (!Q2.empty() && Q1.top() == Q2.top())
        {
            Q1.pop();
            Q2.pop();
        }
        int ans = Q1.top(); Q1.push(tmp);
        return ans;
    }
}B[MAXN], C[MAXN], ans;
struct edge
{
    int END, next;
}v[MAXN << 1];
int first[MAXN], p;
inline void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int f[MAXN][18];
int dep[MAXN];
inline void PreDFS(int rt, int fa)
{
    dep[rt] = dep[fa] + 1;
    f[rt][0] = fa;
    for (int i = 1; i <= 17; i++) f[rt][i] = f[f[rt][i - 1]][i - 1];
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        PreDFS(v[i].END, rt);
    }
}
int sum, Max[MAXN], size[MAXN], root;
bool vis[MAXN];
static inline void GetRoot(int rt, int fa)
{
    size[rt] = 1; Max[rt] = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (vis[v[i].END] || v[i].END == fa) continue;
        GetRoot(v[i].END, rt);
        size[rt] += size[v[i].END];
        Max[rt] = max(Max[rt], size[v[i].END]);
    }
    Max[rt] = max(Max[rt], sum - size[rt]);
    if (Max[rt] < Max[root]) root = rt;
}
int Fa[MAXN];
static inline void Divide(int rt, int fa)
{
    vis[rt] = 1;
    Fa[rt] = fa;
    // cerr << rt << endl;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (vis[v[i].END]) continue;
        sum = size[v[i].END], root = 0;
        GetRoot(v[i].END, 0);
        Divide(root, rt);
    }
}
static inline int LCA(int a, int b)
{
    if (dep[a] < dep[b]) swap(a, b);
    int d = dep[a] - dep[b];
    for (int i = 17; i >= 0; i--)
        if (d & (1 << i))
            d -= (1 << i), a = f[a][i];
    if (a == b) return a;
    for (int i = 17; i >= 0; i--)
        if (f[a][i] != f[b][i])
            a = f[a][i], b = f[b][i];
    return f[a][0];
}
static inline int dis(const int &a, const int &b)
{
    return dep[a] + dep[b] - 2 * dep[LCA(a, b)];
}
int Color[MAXN];
static inline void Change_To_Black(const int &Height_root, const int &Child)
{
    if (Height_root == Child)
    {
        B[Height_root].push(0);
        if (B[Height_root].size() == 2)
            ans.push(B[Height_root].top());
    }
    if (!Fa[Height_root]) return;
    int Father = Fa[Height_root];
    int Dis = dis(Father, Child);
    int tmp = C[Height_root].top();
    C[Height_root].push(Dis);
    if (Dis > tmp)
    {
        int size = B[Father].size();
        int tmp2 = B[Father].top() + B[Father].top2();
        if (tmp)
            B[Father].erase(tmp);
        B[Father].push(Dis);
        int now = B[Father].top() + B[Father].top2();
        if (now > tmp2)
        {
            if (size >= 2) ans.erase(tmp2);
            if (B[Father].size() >= 2)
                ans.push(now);
        }
    }
    Change_To_Black(Father, Child);
}
static inline void Change_To_White(const int &Height_root, const int &Child)
{
    if (Height_root == Child)
    {
        if (B[Height_root].size() == 2)
            ans.erase(B[Height_root].top());
        B[Height_root].erase(0);
    }
    if (!Fa[Height_root]) return;
    int Father = Fa[Height_root];
    int Dis = dis(Father, Child);
    int tmp = C[Height_root].top();
    C[Height_root].erase(Dis);
    if (tmp == Dis)
    {
        int size = B[Father].size();
        int tmp2 = B[Father].top() + B[Father].top2();
        B[Father].erase(Dis);
        if (C[Height_root].top())
            B[Father].push(C[Height_root].top());
        int now = B[Father].top() + B[Father].top2();
        if (now < tmp2)
        {
            if (size >= 2)
                ans.erase(tmp2);
            if (B[Father].size() >= 2)
                ans.push(now);
        }
    }
    Change_To_White(Father, Child);
}
int main()
{
    memset (first, -1, sizeof (first));
    int n = read();
    for (int i = 1; i < n; i++)
    {
        int a = read(), b = read();
        add(a, b);
        add(b, a);
        // cerr << i << endl;
    }
    PreDFS(1, 0);
    
    Max[0] = sum = n;
    GetRoot(1, 0);
    
    Divide(root, 0);
    // cerr << "11!!" << endl;
    for (int i = 1; i <= n; i++)
    {
        Color[i] = 1;
        // cerr << i << endl;
        C[i].push(0);
        // Change_To_Black(i, i);
    }
    for (int i = 1; i <= n; i++)
    {
        Change_To_Black(i, i);
        // cerr << i << endl;        
    }
    // for (int i = 1; i <= n; i++) cerr << "i fa is " << Fa[i] << endl;
    int m = read();
    char s[10];
    for (int i = 1; i <= m; i++)
    {
        // cerr << i << endl;
        scanf ("%s", s);
        if (s[0] == 'C')
        {
            int k = read();
            if (Color[k])
            {
                Color[k] = 0;
                Change_To_White(k, k);
            }
            else
            {
                Color[k] = 1;
                Change_To_Black(k, k);
            }
        }
        else
            printf ("%d\n", ans.top());
    }
}