#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
long long a, b, d, n;
bool Judge(long long mid)
{
    if (mid < b) return 1;
    long long T1 = ceil(((double)mid - a) / d);
    long long T2 = ceil(((double)mid - b) / d);
    return n >= T1 + T2;
}
int main()
{
    scanf ("%lld%lld%lld%lld", &n, &d, &a, &b);
    n--;
    long long l = a, r = 100000000000000000ll;
    long long ans = 0;
    while (l < r)
    {
        long long mid = l + r >> 1;
        if (Judge(mid))
        {
            ans = mid;
            l = mid + 1;
        }
        else 
            r = mid;
    }
    printf ("%lld", ans);
    // while (1);
    return 0;
}