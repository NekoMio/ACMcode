#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct edge
{
    int END, next;
}v[100005];
int first[100005], p;
inline void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int val[100005], tmp[100005];
int size[100005];
vector<int> f[100005];
int n, k;
void DP(int rt)
{
    size[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        DP(v[i].END);
        for (int j = 1; j <= size[rt] && j <= k; j++) tmp[j] = f[rt][j];
        for (int j = 0; j <= size[rt] && j <= k; j++)
            for (int l = 0; l <= size[v[i].END] && l <= k; l++) if (j + l <= k)
                tmp[j + l] = max(tmp[j + l], f[v[i].END][l] + f[rt][j]);
        size[rt] += size[v[i].END];
        for (int j = 1; j <= size[rt] && j <= k; j++) f[rt][j] = tmp[j];
    }
    f[rt][1] = max(f[rt][1], val[rt]);
}
int main()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    n = read(), k = read() + 1;
    memset (first, -1, sizeof (first));
    for (int i = 2; i <= n; i++)
        add(read(), i), val[i] = read();
    for (int i = 1; i <= n; i++)
        f[i].resize(k + 1);
    DP(1);
    int ans = -0x3f3f3f3f;
    for (int i = 0; i <= k; i++)
        ans = max(ans, f[1][i]);
    printf ("%d", ans);
    return 0;
}