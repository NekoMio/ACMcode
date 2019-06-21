#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 2e5 + 5;
int a[MAXN], n, t;
int ch[15][15], cnt[15];
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
void DFS_Init(int rt, int fa)
{
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        DFS_Init(v[i].END, rt);
        ch[rt][++cnt[rt]] = v[i].END;
    }
}
int f[(1 << 10) + 1];
int main()
{
    // freopen ("escape.in", "r", stdin);
    // freopen ("escape.out", "w", stdout);
    int T = read();
    while (T--)
    {
        memset (first, -1, sizeof (first)), p = 0;
        memset (cnt, 0, sizeof (cnt));
        n = read(), t = read();
        for (int i = 1; i <= n; i++)
            a[i] = read();
        for (int i = 1; i < n; i++)
        {
            int b = read(), c = read();
            add(b, c);
            add(c, b);
        }
        DFS_Init(1, 0);
        memset (f, -1, sizeof (f));
        f[1] = a[1];
        int N = (1 << n) - 1;
        bool OK = 0;
        for (int i = 1; i <= N; i++)
        {
            if (f[i] < 0) continue;
            if (i & (1 << (t - 1))) {OK = 1; break;}
            for (int j = 1; j <= n; j++)
                if (i & (1 << (j - 1)))
                    for (int k = 1; k <= cnt[j]; k++)
                        if (!(i & (1 << (ch[j][k] - 1))))
                            f[i | (1 << (ch[j][k] - 1))] = max(f[i | (1 << (ch[j][k] - 1))], f[i] + a[ch[j][k]]);
        }
        if (OK) printf ("escaped\n");
        else printf ("trapped\n");
    }
}