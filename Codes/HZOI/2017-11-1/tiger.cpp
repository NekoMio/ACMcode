#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int N = 10000005;
struct edge
{
    int S, END, next, v, Need;
}v[N << 1];
int first[N], p;
void add(int a, int b, int c, int d)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    v[p].Need = d;
    first[a] = p++;
}
bool vis[N];
bool lst[N];
int ans = 0;
void dfs(int rt, int fa)
{
    int S = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        dfs(v[i].END, rt);
        if (v[i].v == 0 && v[i].Need == 1)
            S += 1;
        else if (v[i].Need == 0) 
            S += lst[v[i].END];
        else
            ans += lst[v[i].END];
    }
    ans += S / 2;
    lst[rt] = S & 1;
}
int main()
{
    freopen ("tiger.in", "r", stdin);
    freopen ("tiger.out", "w", stdout);
    int n = read();
    memset (first, -1, sizeof (first));
    int x,y,z;
    for (int i = 2; i <= n; i++)
    {
        x = read(), y = read(), z = read();
        add(i, x, y ? 1 : 0, z ? 1 : 0);
        add(x, i, y ? 1 : 0, z ? 1 : 0);
    }
    dfs(1, 0);
    printf ("%d", ans + lst[1]);
    fclose(stdin), fclose(stdout);
    return 0;
}