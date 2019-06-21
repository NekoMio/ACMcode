#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1005;
const int MOD = 1000000007;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct edge
{
    int END, next, v;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
long long f[MAXN][MAXN];
long long g[MAXN];
long long Sum[MAXN][MAXN];
long long C[MAXN][MAXN];
int size[MAXN];
void dfs(int rt, int fa)
{
    size[rt] = f[rt][0] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        dfs(v[i].END, rt);
        for (int j = 0; j < size[rt] + size[v[i].END]; j++) g[j] = 0;
        if (v[i].v == 1)
            for (int j = 0; j < size[rt]; j++)
                for (int k = 0; k <= size[v[i].END]; k++)
                {
                    long long tmp = f[rt][j] * Sum[v[i].END][k - 1] % MOD;
                    long long rmp = C[j + k][j] * C[size[rt] + size[v[i].END] - k - j - 1][size[v[i].END] - k] % MOD;
                    (g[j + k] += tmp * rmp % MOD) %= MOD;
                }
        else
            for (int j = 0; j < size[rt]; j++)
                for (int k = 0; k <= size[v[i].END]; k++)
                {
                    long long tmp = f[rt][size[rt] - j - 1] * (Sum[v[i].END][size[v[i].END] - 1] - Sum[v[i].END][size[v[i].END] - k - 1] + MOD) % MOD;
                    long long rmp = C[j + k][j] % MOD * C[size[v[i].END] + size[rt] - k - j - 1][size[v[i].END] - k] % MOD;
                    (g[size[rt] + size[v[i].END] - j - k - 1] += tmp * rmp % MOD) %= MOD;
                }
        size[rt] += size[v[i].END];
        for (int j = 0; j < size[rt]; j++) f[rt][j] = g[j];
    }
    Sum[rt][0] = f[rt][0];
    for (int i = 1; i < size[rt]; i++)
        Sum[rt][i] = (Sum[rt][i - 1] + f[rt][i]) % MOD;
}
int main()
{
    int t = read();
    C[0][0] = 1;    
    for (int i = 1; i <= 1000; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
    while (t--)
    {
        memset (size, 0, sizeof (size));
        memset (Sum, 0, sizeof (Sum));
        memset (f, 0, sizeof (f));
        memset (first, -1, sizeof (first));
        p = 0;
        int n = read(), a, b;
        char c[3];
        for (int i = 1; i < n; i++)
        {
            scanf ("%d%s%d", &a, c, &b);
            a++, b++;
            if (c[0] == '>') add(a, b, 1), add(b, a, -1);
            else add(a, b, -1), add(b, a, 1);
        }
        dfs(1, 0);
        printf ("%lld\n", Sum[1][n - 1]);
    }
    // while (1);
}