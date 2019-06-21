#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    if (n == 1 || n == 2)
    {
        if ((m - 1) % 3)
        {
            printf("impossible\n");
            return 0;
        }
        else
        {
            printf("%d", (m - 1) / 3 * 2 + 1);
            return 0;
        }
    }
    if (m == 1 || m == 2)
    {
        if ((n - 1) % 3)
        {
            printf("impossible\n");
            return 0;
        }
        else
        {
            printf("%d", (n - 1) / 3 * 2 + 1);
            return 0;
        }
    }
    if (n==3&&m==3)
    {
        printf("8");
        return 0;
    }
    if (m == 3)
    {
        int ans=0;
        int k = (n - 1) % 3;
        if (k == 1)
        {
            ans += 5;
        }
        if (k == 2)
        {
            ans += 6;
        }
        printf("%d\n",(n - 1)/3*2+ans);
        return 0;
    }
    if (n == 3)
    {
        int ans=0;
        int k = (m - 1) % 3;
        if (k == 1)
        {
            ans += 5;
        }
        if (k == 2)
        {
            ans += 6;
        }
        printf("%d\n",(m - 1)/3*2+ans);
        return 0;
    }
    printf("%d", (n - 1) / 3 * 2 + (m - 1) / 3 * 2 + (n - 1) % 3 + (m - 1) % 3);
}
