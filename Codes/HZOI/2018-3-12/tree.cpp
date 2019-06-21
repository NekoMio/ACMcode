/* WildRage */
// #pragma GCC optimize("O3")
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
long long d[105][105], a[105][105];
long long gauss(int n)
{
    long long ans = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            a[i][j] = (a[i][j] + MOD) % MOD;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
            while (a[j][i])
            {
                int t = a[i][i] / a[j][i];
                for (int k = i; k <= n; k++)
                {
                    a[i][k] = (a[i][k] - a[j][k] * t % MOD + MOD) % MOD;
                    swap(a[i][k], a[j][k]);
                }
                ans = (MOD - ans) % MOD;
            }
        ans = ans * a[i][i] % MOD;
    }
    return ans;
}
long long f[105];
bool vis[105][105];
long long s[105], now[105], ans[105];
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
int main()
{
    int n = read(), k = read();
    for (int i = 2; i <= n; i++)
    {
        int c = read() + 1;
        vis[i][c] = vis[c][i] = 1; 
        d[i][i]++, d[c][c]++;
        d[i][c]--, d[c][i]--;
    }
    for (int k = 0; k < n; k++)
    {
        memcpy(a, d, sizeof (a));
        for (int i = 1; i <= n; i++)
            for (int j = i; j <= n; j++)
                if (!vis[i][j])
                {
                    a[i][i] += k, a[j][j] += k;
                    a[i][j] -= k, a[j][i] -= k;
                }
        f[k] = gauss(n - 1);
    }
    for (int i = 0; i < n; i++)
    {
        memset (now, 0, sizeof (now));
        now[0] = 1;
        long long t = 1;
        for (int j = 0; j < n; j++)
        {
            if (i == j) continue;
            t = (t * (i - j) % MOD + MOD) % MOD;
            memset (ans, 0, sizeof (ans));
            for (int k = 0; k < n; k++)
                ans[k + 1] = (now[k] - j * now[k + 1] % MOD + MOD) % MOD;
            ans[0] = (- j * now[0] % MOD + MOD) % MOD;
            for (int k = 0; k < n; k++)
                now[k] = ans[k];
        }
        for (int j = 0; j < n; j++)
            s[j] = (s[j] + now[j] * f[i] % MOD * pow_mod(t, MOD - 2) % MOD) % MOD;
    }
    long long Ans = 0;
    for (int i = 0; i <= k; i++) Ans = (Ans + s[i]) % MOD;
    printf ("%lld\n", Ans);
}