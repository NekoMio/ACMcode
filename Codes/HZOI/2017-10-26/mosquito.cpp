// O(n)
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int MOD = 1e9 + 7;
char xch,xB[1<<15],*xS=xB,*xTT=xB;
#define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
inline int read()
{
    int x=0,f=1;char ch=getc();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getc();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getc();}
    return x*f;
}
// inline int read()
// {
//     int x=0,f=1;char ch=getchar();
//     while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
//     while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
//     return x*f;
// }
const int MAXN = 5000005;
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
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
long long f[MAXN], g[MAXN], Inv;
int dep[MAXN], S;
int d, P, q, t;
void dfs(int rt, int fa, int Dep)
{
    f[rt] = 0;
    dep[rt] = Dep;
    bool flag = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        flag = 1;
        dfs(v[i].END, rt, Dep + 1);
        (f[rt] += f[v[i].END]) %= MOD;
    }
    if (!flag) f[rt] = 1, S++;
    if (dep[rt] <= d) f[rt] = ((f[rt] * t % MOD) * Inv) % MOD;
}
long long Ans1 = 0;
void dfs1(int rt, int fa)
{
    if (rt == 1) g[1] = 0;
    else
    {
        if (dep[fa] <= d) g[rt] = (g[fa] + f[fa] - ((f[rt] * t) % MOD * Inv) % MOD + MOD) % MOD;
        else g[rt] = (g[fa] + f[fa] - f[rt] + MOD) % MOD;
        if (dep[rt] <= d) g[rt] = ((g[rt] * t) % MOD * Inv) % MOD;
    }
    int flag = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        dfs1(v[i].END, rt);
        flag = 1;
    }
    if (!flag) (Ans1 += g[rt]) %= MOD;
}
int main()
{
    int n, a, b;
    n = read();
    memset (first, -1, sizeof (first));
    for (int i = 1; i < n; i++)
    {
        a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    d = read(), P = read(), q = read();
    t = q - P;
    Inv = pow_mod(q, MOD - 2) % MOD;
    dfs(1, 0, 0);
    dfs1(1, 0);
    printf ("%lld\n", ((long long)S * (S - 1) % MOD - Ans1 + MOD) % MOD);
    // printf ("%lld", Ans1);
    // while (1);
}