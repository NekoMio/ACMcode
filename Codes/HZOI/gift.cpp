#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MaxN = (1 << 20) + 1;
int N;
double P[MaxN], f[MaxN];
double a[25];
int Get_Num(int n)
{
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j < n; j++)
            if ((1 << j) & i)
            {
                P[i] += a[j + 1];
            }
    }
}
int main()
{
    int n, b;
    scanf("%d", &n);
    long long ans1 = 0;
    double all = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lf%d", &a[i], &b);
        ans1 += b;
        all += a[i];
    }
    all = 1. - all;
    printf("%lld\n", ans1);
    N = (1 << n) - 1;
    Get_Num(n);
    for (int i = 0; i <= N; i++)
        P[i] += all;
    f[N] = 0;
    for (int i = N - 1; i >= 0; i--)
    {
        for (int j = 0; j < n; j++)
        {
            if (!((1 << j) & i))
            {
                f[i] += f[i | (1 << j)] * a[j + 1];
            }
        }
        f[i] = (f[i] + 1)/(1 - P[i]);
    }
    printf("%.3lf\n", f[0]);
    //while (1);
}