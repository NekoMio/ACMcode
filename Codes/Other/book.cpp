#include <cstdio>
#include <cstring>
using namespace std;
#define LL long long
const LL P = 1e9 + 7;
LL pow_mod(LL a, int b)
{
    LL ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % P;
        b >>= 1;
        a = a * a % P;
    }
    return ans;
}
LL q[1005];
int main()
{
    int n;
    scanf("%d", &n);
    LL a, b;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &a, &b);
        q[i] = a * pow_mod(b, P - 2) % P;
    }
    LL ans = 0;
    for (int i = 1; i <= n; i++)
    {
        LL sum = 0;
        for (int j = 1; j <= n; j++)
        {
            if (j == i)
                continue;
            sum = (sum + q[j] * pow_mod(q[i] + q[j], P - 2) % P) % P;
        }
        ans = (ans + (1 + sum) * q[i]) % P;
    }
    printf("%lld", ans);
}
