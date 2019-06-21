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
const int N = 100005;
struct edge
{
    int END, next;
}v[N << 1];
int first[N], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int size[N], n, ans = -1;
void DFS(int rt, int fa)
{
    size[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        DFS(v[i].END, rt);
        if (size[v[i].END] == n >> 1) ans = i;
        size[rt] += size[v[i].END];
    }
}
int main()
{
    freopen ("div.in", "r", stdin);
    freopen ("div.out", "w", stdout);
    int a, b;
    n = read();
    memset (first, -1, sizeof (first));
    for (int i = 1; i < n; i++)
    {
        a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    if (n & 1) return printf ("-1"), 0;
    DFS(1, 0);
    if (ans == -1) printf ("-1");
    else printf ("%d", (ans >> 1) + 1);
    fclose(stdin), fclose(stdout);
}