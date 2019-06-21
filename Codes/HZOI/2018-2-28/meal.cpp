#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 5e4 + 5;
struct edge
{
    int END, next, v;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int dep[MAXN];
int num[MAXN];
int a[MAXN], b[MAXN];
void dfs(int rt, int fa)
{
    dep[rt] = dep[fa] + 1;
    if (b[rt] == 0) dep[rt] = 1;
    num[rt] = a[rt];
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        num[rt] -= a[v[i].END] * b[v[i].END];
        dfs(v[i].END, rt);
    }
}
int main()
{
    int t = read();
    while (t--)
    {
        memset (first, -1, sizeof (first));
        // memset (fa, 0, sizeof (fa));
        memset (num, 0, sizeof (num));
        memset (dep, 0, sizeof (dep));
        p = 0;
        int n = read();
        int Maxa = 0, Maxb = 0;
        for (int i = 1; i <= n; i++)
            Maxa = max(Maxa, a[i] = read());
        for (int i = 1; i <= n; i++)
            Maxb = max(Maxb, b[i] = read());
        for (int i = 1; i < n; i++)
        {
            int a = read(), b = read();
            add(a, b);
            add(b, a);
        }
        dfs(1, 0);
        int Sum = 0;
        for (int i = 1; i <= n; i++)
            if (dep[i] & 1)
                Sum ^= num[i];
        if (Sum) printf ("YES\n");
        else printf ("NO\n");
    }
}