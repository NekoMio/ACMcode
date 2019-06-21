#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 2e5 + 5;
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
map<int, int> f[MAXN];
int Mx = 0;
int a[MAXN], Hash[MAXN];
int DP(int rt, int fa)
{
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        DP(v[i].END, rt);
    }
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        if (f[rt].size() < f[v[i].END].size()) swap(f[rt], f[v[i].END]);
        for (map<int, int>::iterator it = f[v[i].END].begin(); it != f[v[i].END].end(); it++) 
            f[rt][it->first] += it->second;
    }
    f[rt][a[rt]]++;
    map<int, int>::iterator it = f[rt].find(a[rt]);
    if (it != f[rt].begin())
    {
        it--; it->second--;
        if (it->second == 0) f[rt].erase(it);
    }
}
int main()
{
    memset (first, -1, sizeof (first));
    int n = read();
    for (int i = 1; i <= n; i++)
        Hash[i] = a[i] = read();
    sort(Hash + 1, Hash + n + 1);
    Mx = unique(Hash + 1, Hash + n + 1) - Hash - 1;
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(Hash + 1, Hash + Mx + 1, a[i]) - Hash;
    for (int i = 1; i < n; i++)
    {
        int c = read(), b = read();
        add(c, b);
        add(b, c);
    }
    int ans = 0;
    DP(1, 0);
    for (map<int, int>::iterator it = f[1].begin(); it != f[1].end(); it++)
        ans += it->second;
    printf ("%d\n", n - ans);
}