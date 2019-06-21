#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
// #define int long long
const long long MOD = 19930726;
char s[1000005];
long long p[1000005];
long long stk[1000005];
long long pow_mod(long long a, long long b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
int main()
{
    // freopen("rehearse.in", "r", stdin);
    // freopen("rehearse.out", "w", stdout);
    int n;
    long long k;
    scanf("%d%lld", &n, &k);
    scanf("%s", s + 1);
    s[0] = '$';
    int mx = 0, id = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i < mx)
            p[i] = min(p[2 * id - i], (long long)mx - i);
        else
            p[i] = 1;
        while (s[i + p[i]] == s[i - p[i]]) p[i]++;
        if (i + p[i] > mx) mx = i + p[i], id = i;
    }
    // for (int i = 1; i <= n; i++)
        // printf("%d ",p[i]);
    // printf("\n");
    for (int i = 1; i <= n; i++)
        stk[p[i] * 2 - 1]++;
    long long ans = 1;
    for (int i = n; i >= 0; i--)
    {
        ans = (ans * pow_mod(i, min(stk[i], (long long)k)) % MOD) % MOD;
        k -= stk[i];
        if(k <= 0) break;
        stk[i - 2] += stk[i];
    } 
    printf("%lld\n", ans);
    // while(1);
}