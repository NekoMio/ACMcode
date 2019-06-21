#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXM = 500005;
const int MAXN = 100005;
inline long long rand64() {
    return (long long)(((((unsigned long long)rand()) << 32) | ((unsigned long long)rand())) & ((1llu << 40) - 1));
}
struct edge
{
    int END, next, id; 
}v[MAXM << 1];
int first[MAXN], p = 2;
void add(int a, int b, int i)
{
    v[p].END = b;
    v[p].id = i;
    v[p].next = first[a];
    first[a] = p++;
}
long long XorSum[MAXN];
bool vis[MAXN];
long long W[MAXM];
void dfs(int rt, int fa)
{
    vis[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        if (!vis[v[i].END])
            dfs(v[i].END, rt);
        else
        {
            if (!W[v[i].id]) 
            {
                W[v[i].id] = rand64();
                XorSum[rt] ^= W[v[i].id];
                XorSum[v[i].END] ^= W[v[i].id];
            }
        }
    }
}
void dfs2(int rt, int fa)
{
    vis[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        if (!vis[v[i].END])
        {
            dfs2(v[i].END, rt);
            W[v[i].id] = XorSum[v[i].END];
            XorSum[rt] ^= XorSum[v[i].END];
        }
    }
}
struct P
{
    long long a[65];
    int cnt;
    P()
    {
        memset (a, 0, sizeof (a));
    }
    void Clear()
    {
        memset (a, 0, sizeof (a));
        cnt = 0;
    }
    void Build(long long *x, int n)
    {
        static long long tmp[65];
        memset (tmp, 0, sizeof (tmp));
        for (int i = 1; i <= n; i++)
        {
            for (int j = 40; j >= 0; j--)
            {
                if (x[i] & (1ll << j))
                {
                    if (tmp[j]) x[i] ^= tmp[j];
                    else
                    {
                        tmp[j] = x[i];
                        for (int k = j - 1; k >= 0; k--) if (tmp[k] && (tmp[j] & (1ll << k))) tmp[j] ^= tmp[k];
                        for (int k = j + 1; k <= 40; k++) if (tmp[k] & (1ll << j)) tmp[k] ^= tmp[j];
                        break;
                    }
                }
            }
        }
        for (int i = 0; i <= 40; i++) if (tmp[i]) a[cnt++] = i;
        cnt--;
    }
}P;
long long tmp[65];
int main()
{
    srand(time(NULL));
    memset (first, -1, sizeof (first));
    int n = read(), m = read();
    for (int i = 1; i <= m; i++)
    {
        int a = read(), b = read();
        add(a, b, i);
        add(b, a, i);
    }
    int q = read();
    dfs(1, 0);
    memset (vis, 0, sizeof (vis));
    dfs2(1, 0);
    
    // for (int i = 1; i <= m; i++) printf("w[%d] = %lld\n", i, W[i]);
    
    int Num = 0;
    for (int i = 1; i <= q; i++)
    {
        int k = read();
        for (int j = 1; j <= k; j++)
            tmp[j] = W[read() ^ Num];
        P.Clear();
        P.Build(tmp, k);
        if (P.cnt + 1 == k) Num++, printf ("Connected\n");
        else printf ("Disconnected\n");
    }
    // while (1);
}