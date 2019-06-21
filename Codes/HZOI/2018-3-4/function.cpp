#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline long long read()
{
    long long x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MOD = 1005060097;
const int MAXN = 1e6;
const int Inv2 = 502530049;
int prime[MAXN + 2], cnt;
int mu[MAXN + 2];
bool isnprime[MAXN + 2];
void Get_G()
{
    isnprime[1] = 1;
    mu[1] = 1;
    for (int i = 2; i <= MAXN; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > MAXN) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                mu[i * prime[j]] = 0;
                break;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
}
long long Sum(long long a)
{
    return (a + 1) % MOD * (a % MOD) % MOD * Inv2 % MOD;
}
long long Calc(long long n)
{
    long long nxt;
    long long ans = 0;
    for (long long i = 1; i <= n; i = nxt + 1)
    {
        nxt = n / (n / i);
        ans = (ans + ((Sum(nxt) - Sum(i - 1)) % MOD + MOD) % MOD * ((n / i) % MOD) % MOD) % MOD;
    }
    return ans;
}
int main()
{
    long long ans = 0;
    long long n = read();
    Get_G();
    for (long long i = 1; i * i <= n; i++)
    {
        if (mu[i] == 0) continue;
        ans = (ans + mu[i] * i % MOD * Calc(n / i / i) % MOD + MOD) % MOD;
    }
    printf ("%d\n", (ans - Sum(n) + MOD) % MOD);
}