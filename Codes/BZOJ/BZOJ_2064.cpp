#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[100];
int S[(1 << 20) + 1], f[(1 << 20) + 1];
int main()
{
    int n, m;
    int cnt = 0;
    scanf ("%d", &n);
    for (cnt = 1; cnt <= n; cnt++)
        scanf ("%d", &a[cnt]);
    scanf ("%d", &m);
    n += m;
    for (; cnt <= n; cnt++)
        scanf ("%d", &a[cnt]), a[cnt] = -a[cnt];
    int N = (1 << n) - 1;
    for (int i = 1; i <= N; i++)
    {
        int j = 0;
        for (j = 1; j <= n; j++)
            if (i & (1 << (j - 1)))
                break;
        S[i] = S[i ^ (1 << (j - 1))] + a[j];
        for (j = 1; j <= n; j++)
            if (i & (1 << (j - 1)))
                f[i] = max(f[i], f[i ^ (1 << (j - 1))] + (!S[i]));
    }
    printf ("%d", n - f[N] * 2);
}