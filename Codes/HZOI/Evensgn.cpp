#include <cstdio>
#include <algorithm>
using namespace std;
int in[1000005], out[1000005];
long long Sum = 0;
int main()
{
    int n, m, a, b, c;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        out[a] += c;
        in[b] += c;
        Sum += c;
    }
    for (int i = 1; i <= n; i++)
    {
        Sum -= min(out[i], in[i]);
    }
    printf("%lld\n", Sum);
    //while (1)
}