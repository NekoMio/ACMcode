#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 1000005;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

struct sam
{
    int cnt;
    int a[MAXN << 1][10], Max[MAXN << 1], fa[MAXN << 1];
    int extend(int p, int c)
    {
        int np = ++cnt;
        Max[np] = Max[p] + 1;
        while (!a[p][c] && p) a[p][c] = np, p = fa[p];
        if (!p) fa[np] = 1;
        else
        {
            int q = a[p][c];
            if (Max[q] == Max[p] + 1) fa[np] = q;
            else
            {
                int nq = ++cnt;
                Max[nq] = Max[p] + 1;
                memcpy(a[nq], a[q], sizeof (a[nq]));
                fa[nq] = fa[q];
                fa[q] = fa[np] = nq;
                while (a[p][c] == q) a[p][c] = nq, p = fa[p];
            }
        }
        return np;
    }
}SAM;
int Color[MAXN], id[MAXN], du[MAXN];
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

void DFS(int rt, int fa)
{
    id[rt] = SAM.extend(id[fa], Color[rt]);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        DFS(v[i].END, rt);
    }
}

int main()
{
    id[0] = ++SAM.cnt;
    int n = read(), c = read();
    memset (first, -1, sizeof (first));
    for (int i = 1; i <= n; i++)
        Color[i] = read();
    for (int j = 1; j < n; j++)
    {
        int a = read(), b = read();
        add(a, b); add(b, a);
        du[a]++, du[b]++;
    }
    for (int i = 1; i <= n; i++)
        if (du[i] == 1)
            DFS(i, 0);
    long long ans = 0;
    for (int i = 2; i <= SAM.cnt; i++)
        ans += SAM.Max[i] - SAM.Max[SAM.fa[i]];
    printf ("%lld\n", ans);
}