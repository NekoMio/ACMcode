#include <cstdio>
using namespace std;
int main()
{
    freopen ("a.in", "r", stdin);
    freopen ("a.out", "w", stdout);
    long long n, m, p;
    scanf ("%lld%lld%lld", &n, &m, &p);
    printf ("%lld", n * m % p);
}