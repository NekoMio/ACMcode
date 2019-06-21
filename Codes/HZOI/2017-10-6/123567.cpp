#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 3e7 + 5;
int mu[N], prime[N / 10], cnt;
bool isnprime[N];
struct hash
{
    long long v, val;
    int next;
}v[N / 10];
int first[76545], p;
void add(int x, int a)
{
    v[p].next = first[x % 76543];
    v[p].v = x;
    v[p].val = a;
    first[x % 76543] = p++;
}
void Get_mu()
{
    mu[1] = 1;
    for (int i = 2; i <= N; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > N) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
            mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 2; i <= N; i++) mu[i] += mu[i - 1]; 
}
long long Query(long long x)
{
    if (x <= N) return mu[x];
    int ans = 1;
    long long last;
    for (int i = first[x % 76543]; i != -1; i = v[i].next)
        if(v[i].v == x) return v[i].val;
    for (long long i = 2; i <= x; i = last + 1)
    {
        last = x / (x / i);
        ans -= (last -  i + 1) * Query(x / i);
    }
    add(x, ans);
    return ans;
}
long long S(long long a, long long b)
{
    return Query(b) - Query(a - 1);
}
int main()
{
    memset(first, -1, sizeof(first));
    Get_mu();
    long long ans = 0, n, last, kk;
    scanf("%lld", &n);
    kk = sqrt(n);
    for (long long i = 1; i <= kk; i = last + 1)
    {
        last = sqrt(n / (n / (i * i)));
        ans += S(i, last) * (n / (i * i));
    }
    printf("%lld", ans);
    // while(1);
}