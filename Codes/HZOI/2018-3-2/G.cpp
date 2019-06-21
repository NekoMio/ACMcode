// #pragma GCC optimize("O2")
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 998244353;
const int Inv100 = 828542813;
const int MAXN = 105;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'||ch=='.'){if(ch!='.')x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
long long a[2][MAXN], b[2][MAXN];
long long DP[2][2][105][105][105];
int n, now;
void Run_DP(int id)
{
    DP[id][0][0][0][0] = 1;
    now = 0;
    register int i, j, k, l;
    for (i = 0; i < n; i++)
    {
        now ^= 1;
        memset (DP[id][now], 0, sizeof (DP[id][now]));
        for (j = 0; j <= i; j++)
            for (k = 0; k <= j; k++)
                for (l = 0; l + j <= i; l++)
                {
                    (DP[id][now][l][k + 1][j + 1] += DP[id][now ^ 1][l][k][j] * a[id][i + 1] % MOD * b[id][i + 1] % MOD) %= MOD;
                    (DP[id][now][l + 1][k][j] += DP[id][now ^ 1][l][k][j] * (1 - a[id][i + 1] + MOD) % MOD * b[id][i + 1] % MOD) %= MOD;
                    (DP[id][now][l][k][j + 1] += DP[id][now ^ 1][l][k][j] * a[id][i + 1] % MOD * (1 - b[id][i + 1] + MOD) % MOD) %= MOD;
                    (DP[id][now][l][k][j] += DP[id][now ^ 1][l][k][j] * (1 - a[id][i + 1] + MOD) % MOD * (1 - b[id][i + 1] + MOD) % MOD) %= MOD;
                }
    }
}
struct data
{
    int a;
    long long Sum;
}st[MAXN * MAXN];
int main()
{
    register int i;
    n = read();
    for (i = 1; i <= n; i++) a[0][i] = 1ll * read() * Inv100 % MOD;
    for (i = 1; i <= n; i++) a[1][i] = 1ll * read() * Inv100 % MOD;
    for (i = 1; i <= n; i++) b[0][i] = 1ll * read() * Inv100 % MOD;
    for (i = 1; i <= n; i++) b[1][i] = 1ll * read() * Inv100 % MOD;
    Run_DP(0), Run_DP(1);
    int cnt = 0;
    register long long ans = 0;
    register int ip, j, k;
    for (i = 1; i <= n; i++)
        for (ip = 1; ip <= n; ip++)
        {
            cnt = 0;
            for (j = 0; j <= i; j++)
                for (k = 0; k <= n - i; k++)
                    if (j * (n - i) > k * i && DP[0][now][k][j][i])
                        st[++cnt].a = j * (2 * n - i - ip) - k * (i + ip), st[cnt].Sum = DP[0][now][k][j][i];
            sort(st + 1, st + cnt + 1, [](const data &a, const data &b){return a.a < b.a;});
            for (j = 1; j <= cnt; j++)
                st[j].Sum = (st[j].Sum + st[j - 1].Sum) % MOD;
            for (j = 0; j <= ip; j++)
                for (k = 0; k <= n - ip; k++)
                    if (j * (n - ip) > k * ip && DP[1][now][k][j][ip])
                        ans = (ans + (lower_bound(st + 1, st + cnt + 1,  (data){k * (i + ip) - j * (2 * n - i - ip), 0}, [](const data &a, const data &b){return a.a < b.a;}) - 1)->Sum * DP[1][now][k][j][ip] % MOD) % MOD;
        }
    printf ("%d\n", ans);
    // while (1);
}