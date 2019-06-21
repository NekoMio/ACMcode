#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long m, bin[65], c[65][65];
long long k;
long long Judge(long long x)
{
    if(!x) return -1;
    long long ans = 0;
    int num = 0;
    for (int i = 63; i >= 0; i--)
    {
        if(bin[i] & x) {
            num++;
            ans += c[i][k - num];
        }
    }
    return ans;
}
long long Calc(long long m)
{
    long long l = 1, r = bin[62], mid, ans;
    while (l <= r)
    {
        mid = l + r >> 1;
        if (Judge(mid) < m) l = mid + 1;
        else ans = mid, r = mid - 1;
    }
    return ans;
}
int main()
{
    bin[0] = 1;
    for (int i = 1; i <= 63; i++) bin[i] = bin[i - 1] << 1;
    c[0][0] = 1;
    for (int i = 1; i <= 63; i++)
    {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++)
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
    }
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%lld%lld", &m, &k);
        if (k == 1) {printf("-1\n");continue;}
        if (k == 63) {printf("1 4611686018427387903\n");continue;}
        if (k == 64) {printf("1 9223372036854775807\n");continue;}
        long long L = Calc(m);
        long long R = Calc(m + 1) - 1;
        printf("%lld %lld\n", L, R);
    }
}