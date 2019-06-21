#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[25][55], Max, n;
bool isnprime[100005];
int prime[20005], Idx;
void Get_Prime()
{
    isnprime[1] = 1;
    for (int i = 2; i <= Max; i++)
    {
        if (!isnprime[i])
            prime[++Idx] = i;
        for (int j = 1; j <= Idx; j++)
        {
            if (i * prime[j] > Max)
                break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}
int ans = 0x3f3f3f3f;
void dfs(int x, int y)
{
    if (a[y - 1][n] == 0)
    {
        ans = x;
        return;
    }
    for (int i = 1; i <= Idx; i++)
    {
        int Sum1 = x, Sum2 = 0;
        for (int j = 1; j <= n; j++)
        {
            Sum1 += a[y - 1][j] % prime[i];
            a[y][j] = a[y - 1][j] / prime[i];
            if (a[y - 1][j] < prime[i])
                Sum2 = Sum1;
        }
        if (Sum2 >= ans)
            return;
        if (Sum1 >= ans)
            continue;
        dfs(Sum1, y + 1);
    }
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[0][i]);
    sort(a[0] + 1, a[0] + n + 1);
    Max = a[0][n];
    if (Max == 1)
        Max = 2;
    //printf("%d\n",Max);
    Get_Prime();
    dfs(0, 1);
    printf("%d", ans);
}
