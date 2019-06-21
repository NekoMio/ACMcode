#include <cstdio>
#include <cstring>
#include <algorithm>
const int MOD = 10007;
const int MAXM = 100005;
using namespace std;
inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') {if(ch=='-')f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9') {x = x*10+ch-'0'; ch = getchar();}
    return x * f;
}
int MaxM = 0;
int M[1005][15], Nn[1005], Nc[1005];
int g[21][MAXM];
int f[21][12][MAXM];
int m[15], n, c;
int prime[MAXM], mu[MAXM], cnt;
bool isnprime[MAXM];
int C[MAXM][21];
void Init()
{
    isnprime[1] = 1;
    mu[1] = 1;
    for (int i = 1; i <= MaxM; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > MaxM) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                mu[i * prime[j]] = 0;
                break;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
    C[0][0] = 1;
    for (int i = 1; i <= MaxM; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= 20; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
    for (int c = 2; c <= 20; c++)
        for (int i = 1; i <= MaxM; i++)
            for (int j = i, k = 1; j <= MaxM; j += i, k++)
                g[c][j] = (g[c][j] + C[i - 1][c - 2] * mu[k] + MOD) % MOD;
    for (int i = 1; i <= MaxM; i++)
        for (int c = 2; c <= 20; c++)
        {
            int tmp = 1;
            for (int j = 0; j <= 11; j++)
            {
                f[c][j][i] = (tmp * g[c][i] + f[c][j][i - 1]) % MOD;
                tmp = tmp * i % MOD;
            }
        }
}
int a[12];
void Calc(int x)
{
    memset (a, 0, sizeof (a));
    a[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        int t = m[i] / x;
        int b = ((long long)t * m[i]) % MOD, d = -((long long)t * (t + 1) / 2) % MOD;
        for (int j = n; j >= 1; j--)
            a[j] = ((a[j] * b + a[j - 1] * d) % MOD + MOD) % MOD;
        a[0] = a[0] * b % MOD;
    }
}

int main()
{
    int T = 0;
    T = read();
    for (int i = 1; i <= T; i++)
    {
        Nn[i] = read(), Nc[i] = read();
        for (int j = 1; j <= Nn[i]; j ++)
            M[i][j] = read(), MaxM = max(M[i][j], MaxM);
    }
    Init();
    for (int t = 1; t <= T; t++)
    {
        n = Nn[t], c = Nc[t];
        for (int i = 1; i <= n; i++) m[i] = M[t][i];
        int ans = 0, Mx = 0x3f3f3f3f;
        for (int i = 1; i <= n; i++) Mx = min(Mx, m[i]);
        for (int i = 1, pos = 0; i <= Mx; i = pos + 1)
        {
            pos = Mx + 1;
            for (int j = 1; j <= n; j++) pos = min(pos, m[j] / (m[j] / i));
            Calc(i);
            for (int j = 0; j <= n; j++) ans = (ans + a[j] * ((f[c][j][pos] - f[c][j][i - 1]) % MOD + MOD) % MOD) % MOD;
        }
        printf ("%d\n", ans);
    }
}