#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int x[100005], b[100005];
int main(int argc, char const *argv[])
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &x[i]);
        }
        sort(x+1,x+n+1);
        for (int i = 1; i <= n; i++)
        {
            b[i] = x[i] - x[i - 1] - 1;
        }
        int S = 0;
        for (int i = n; i >= 1; i -= 2)
        {
            S ^= b[i];
        }
        if (S)
            printf("Georgia will win\n");
        else
            printf("Bob will win\n");
    }
    return 0;
}
