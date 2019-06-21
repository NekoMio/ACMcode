#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int main()
{
    int n, t;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        int k = 0;
        for (int i = 1; i <= n; i++)
        {
            k = (k + n - i + 1) % i;
        }
        printf("%d\n", k + 1);
    }
}
