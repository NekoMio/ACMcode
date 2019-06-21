#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 500005;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct SAM
{
    struct edge
    {
        int END, next;
    }v[MAXN << 1];
    int first[MAXN << 1], p;
    void add(int a, int b)
    {
        v[p].END = b;
        v[p].next = first[a];
        first[a] = p++;
    }
    int last, cnt;
    long long ans;
    int a[MAXN << 1][26], fa[MAXN << 1], Max[MAXN << 1], size[MAXN << 1];
    SAM()
    {
        last = ++cnt;
    }
    void extend(int c)
    {
        int p = last, np = last = ++cnt;
        Max[np] = Max[p] + 1;
        size[np] = 1;
        while (!a[p][c] && p) a[p][c] = np, p = fa[p];
        if (!p) fa[np] = 1;
        else
        {
            int q = a[p][c];
            if (Max[p] + 1 == Max[q]) fa[np] = q;
            else
            {
                int nq = ++cnt;
                Max[nq] = Max[p] + 1;
                memcpy(a[nq], a[q], sizeof (a[nq]));
                fa[nq] = fa[q];
                fa[np] = fa[q] = nq;
                while (a[p][c] == q) a[p][c] = nq, p = fa[p];
            }
        }
    }
    void buildtree()
    {
        memset (first, -1, sizeof (first));
        for (int i = 2; i <= cnt; i++)
            add(fa[i], i);
    }
    void DFS(int rt, int fa)
    {
        for (int i = first[rt]; i != -1; i = v[i].next)
        {
            DFS(v[i].END, rt);
            size[rt] += size[v[i].END];
        }
        Max[rt] -= Max[fa];
        ans -= 1ll * size[rt] * (size[rt] - 1) * Max[rt];
    }
    long long query()
    {
        for (int i = first[1]; i != -1; i = v[i].next)
            DFS(v[i].END, 1);
        return ans;
    }
}sam;
int main()
{
    static char s[500005];
    scanf ("%s", s + 1);
    int n = strlen(s + 1);
    for (int i = n; i >= 1; i--)
    {
        sam.extend(s[i] - 'a');
    }
    sam.ans = 1ll * n * (n - 1) * (n + 1) / 2;
    sam.buildtree();
    printf ("%lld\n", sam.query());
}