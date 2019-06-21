#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long P;
long long f[305];
long long plus_mod(long long a, long long b)
{
    a %= P;
    b %= P;
    long long ans = 0;
    while (b)
    {
        if (b & 1)
            ans = (ans + a) % P;
        b >>= 1;
        a = a + a % P;
    }
    return ans;
}
long long DP(int x);
long long DFS(int now, int x, int Dep)
{
    if (now == x + 1) return 1;
    long long ans = 1;
    for (int i = now; i < x + (now != 1); i++)
    {
        ans = plus_mod(plus_mod(ans, DFS(i + 1, x, Dep + 1)), DP(i - now + 1)); 
    }
    if (now == 1) ans += x;
    return ans;
}
long long DP(int x)
{
    if (f[x] != -1) return f[x];
    if (x == 1) return f[x] = 2;
    return f[x] = DFS(1, x, 0);
}
int main()
{
    int n;
    // P = 998244353;
    scanf ("%d%lld", &n, &P);
    memset(f, -1, sizeof (f));
    printf ("%lld", DP(n));
    // while (1);
}