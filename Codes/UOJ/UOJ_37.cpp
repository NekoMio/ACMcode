#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int Num(unsigned int x)
{
    unsigned int tmp = x
                     - ((x >> 1) & 033333333333)
                     - ((x >> 2) & 011111111111);
    tmp = (tmp + (tmp >> 3)) & 030707070707;
    return tmp % 63;
}
const int MAXN = (1 << 15) + 1;
const int MOD = 1e9 + 7;
int v[MAXN], g[MAXN], f[MAXN], w[MAXN];
int bin[200], Sum[MAXN];
int S[MAXN];
void DFS(int i, int j)
{
    if (i & (j - 1)) DFS(i, i & (j - 1));
    S[j] = S[j - (j & -j)] + Num(w[j & -j] & i);
}
int main()
{
    int n = read(), m = read();
    bin[0] = 1;
    for (int i = 1; i <= m; i++)
    {
        int a = read(), b = read();
        v[(1 << (a - 1))] |= (1 << (b - 1));
        w[(1 << (b - 1))] |= (1 << (a - 1));
        bin[i] = bin[i - 1] * 2 % MOD;
    }
    int N = (1 << n) - 1;
    for (int i = 1; i <= N; i++)
    {
        int x = i - (i & -i);
        DFS(i, i);
        Sum[i] = Sum[x] + Num(w[i & -i] & i) + Num(v[i & -i] & i);
        f[i] = bin[Sum[i]];
        for (int j = x; j; j = (j - 1) & x)
            g[i] = (g[i] - 1ll * f[i ^ j] * g[j] % MOD + MOD) % MOD;
        for (int j = i; j; j = (j - 1) & i) 
            f[i] = (f[i] - 1ll * bin[Sum[i] - S[j]] * g[j] % MOD + MOD) % MOD;
        g[i] = (g[i] + f[i]) % MOD;
    }
    printf ("%d\n", f[N]);
}
