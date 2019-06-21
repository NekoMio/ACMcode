#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1000005;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct edge
{
    int END, next;
}v[N << 1];
int first[N], p, n;
void add(int a, int b)
{
    v[p].next = first[a];
    v[p].END = b;
    first[a] = p++;
}
long long f[N];
long long size[N];
void DFS1(int rt, int fa)
{
    f[rt] = 0;
    size[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        DFS1(v[i].END, rt);
        size[rt] += size[v[i].END];
        f[rt] += f[v[i].END] + size[v[i].END]; 
    }
}
void DFS2(int rt, int fa)
{
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        f[v[i].END] += f[rt] - f[v[i].END] + n - 2 * size[v[i].END];
        DFS2(v[i].END, rt);
    }
}
int main()
{
    int a, b;
    n = read();
    memset (first, -1, sizeof (first));
    for (int i = 1; i < n; i++)
    {
        a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    DFS1(1, 0);
    DFS2(1, 0);
    long long Ans = 0;
    int ans = 1;
    for (int i = 1; i <= n; i++)
    {
        if (Ans < f[i])
        {
            Ans = f[i];
            ans = i;
        }
    }
    printf ("%d", ans);
}