#include <cstdio>
#include <cstring>
using namespace std;
const int full = 20;
int a[2005];
int kth[2005], Sum[2005][2005];
int main(int argc, char const *argv[])
{
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            kth[j] = 1;
            for (int k = i; k < j; k++)
            {
                if (a[k] < a[j])
                    kth[k]++;
                else
                    kth[j]++;
                ++Sum[a[k]][kth[k]];
            }
            ++Sum[a[j]][kth[j]];
        }
    }
    int k, x;
    while (q--)
    {
        scanf("%d%d", &k, &x);
        printf("%d\n",Sum[x][k]);
    }
    return 0;
}
