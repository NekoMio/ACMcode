#pragma GCC optimize("O2")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MOD = 1e9 + 7;
const int Inv2 = MOD + 1 >> 1;
const int Inv4 = MOD + 1 >> 2;
map<int, int> f[(1 << 15) + 1];
struct edge
{
    int S, P;
}v[1050];
int cnt, n, m;
int F(int S)
{
    if (!S) return 1;
    int A = (S >> n), B = S ^ (A << n);
    if (f[B].count(A)) return f[B][A];
    int &ans = f[B][A];
    for (int i = 1; i <= cnt; i++)
        if (((v[i].S & S) == v[i].S) && S < (v[i].S << 1)) 
            ans = (ans + 1ll * F(S ^ v[i].S) * v[i].P % MOD) % MOD;
    return ans;
}
int main()
{
    n = read(), m = read();
    for (int i = 1; i <= m; i++)
    {
        int op = read(), x1 = read(), y1 = read();
        int S = (1 << (x1 - 1)) | (1 << (y1 + n - 1));
        v[++cnt] = (edge){S, Inv2};
        if (op)
        {
            int x2 = read(), y2 = read();
            int S1 = (1 << (x2 - 1)) | (1 << (y2 + n - 1));
            v[++cnt] = (edge){S1, Inv2};
            if (S1 & S) continue;
            if (op == 1) v[++cnt] = (edge){S1 | S, Inv4};
            else v[++cnt] = (edge){S1 | S, MOD - Inv4};
        }
    }
    printf ("%lld\n", 1ll * (1 << n) * F((1 << (2 * n)) - 1) % MOD);
    // while (1);
}