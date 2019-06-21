#include <cstdio>
#include <cstring>
using namespace std;
int f[1001005];
int main()
{
    int n;
    scanf("%d", &n);
    memset(f, 0x3f, sizeof(f));
    f[1] = 0;
    f[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        // if (f[i] > f[i + 1] + 1) f[i] = f[i + 1] + 1;
        for (int j = i + 10; j >= i; j--)
            if (f[i] > f[j] + j - i) f[i] = f[j] + j - i;
        for (int j = 1; i * j <= n + 10; j++)
            if (f[i * j] > f[i] + j)
                f[i * j] = f[i] + j;
    }
    printf("%d\n", f[n]);
}