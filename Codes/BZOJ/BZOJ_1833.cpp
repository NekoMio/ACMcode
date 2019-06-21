#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long A[50], B[50];
long long f[25], Base[25];
int num[25];
void Calc(long long x, long long *a)
{
    if (!x) return;
    int m = 0;
    long long tmp = x;
    while (x) num[++m] = x % 10, x /= 10;
    for (int i = 1; i < m; i++)
        for (int j = 0; j <= 9; j++)
            a[j] += f[i - 1] * 9 + ((!j) ? 0 : Base[i - 1]);
    for (int i = m; i > 0; i--)
    {
        tmp -= num[i] * Base[i - 1];
        for (int j = (i == m); j < num[i]; j++) a[j] += Base[i - 1];
        for (int j = 0; j <= 9; j++) a[j] += f[i - 1] * (num[i] - (i == m));
        a[num[i]] += (tmp + 1);
    }
}
void Init()
{
    Base[0] = 1;
    for (int i = 1; i <= 15; i++) Base[i] = Base[i - 1] * 10;
    for (int i = 1; i <= 15; i++)
         f[i] = f[i - 1] * 10 + Base[i - 1];
}
int main()
{
    long long a, b;
    scanf ("%lld%lld", &a, &b);
    Init();
    Calc(a - 1, A);
    Calc(b, B);
    for (int i = 0; i <= 8; i++)
        printf("%lld ", B[i] - A[i]);
    printf("%lld", B[9] - A[9]);
    // while(1);
}