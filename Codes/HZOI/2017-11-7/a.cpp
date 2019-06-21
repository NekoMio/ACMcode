#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int C[50];
int To(int N, int k, int *a, int &Sum, int lim)
{
    int t = 0;
    Sum = 0;
    while (N)
    {
        if (t == lim) a[++t] = N, N = 0;
        else a[++t] = N % k;
        Sum += a[t];
        N /= k;
    }
    return t;
}
int main()
{
    // freopen ("a.in", "r", stdin);
    // freopen ("a.out", "w", stdout);
    int S, T, a, b;
    scanf ("%d%d%d%d", &S, &T, &a, &b);
    long long Pow = 1;
    int ans = 0x3f3f3f3f, Sum;
    for (int i = 0; i <= 30; i++)
    {
        if (Pow * S > T || Pow > 1000000000) break;
        int t = T - Pow * S;
        Pow *= b;
        if (t % a) continue;
        t /= a;
        memset (C, 0, sizeof (C));
        To(t, b, C, Sum, i);
        ans = min(ans, Sum + i);
    }
    printf ("%d", (ans == 0x3f3f3f3f ? -1: ans));
    // while (1);
}