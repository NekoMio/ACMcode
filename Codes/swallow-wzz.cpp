#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define maxn 44721
using namespace std;

int n, tot;
int ansnum[100000];
int prime[maxn + 5], biao[maxn + 5];

bool judge(int x)
{
    int p = (int)sqrt(x);
    for (int i = 1; i <= prime[0] && p >= prime[i]; i++)
        if (x % prime[i] == 0)
            return false;
    return true;
}

void dfs(int p, int yuan, int ans)
{
    if (yuan == 1)
    {
        ansnum[++tot] = ans;
        return;
    }
    if (p > prime[0])
        return;
    if (yuan - 1 >= prime[p] && judge(yuan - 1))
        ansnum[++tot] = ans * yuan - ans;
    for (int i = p; prime[i] * prime[i] < yuan && i <= prime[0]; i++)
    {
        int u = prime[i] + 1, jie = prime[i];
        for (; u <= yuan; jie *= prime[i], u += jie)
            if (yuan % u == 0)
                dfs(i + 1, yuan / u, ans * jie);
    }
}

void shai()
{
    for (int i = 2; i <= maxn; i++)
    {
        if (!biao[i])
            prime[++prime[0]] = i;
        for (int j = 1; j <= prime[0] && i * prime[j] <= maxn; j++)
        {
            biao[i * prime[j]] = 1;
            if (!(i % prime[j]))
                break;
        }
    }
}

int main()
{
    // freopen("a.in","r",stdin);
    // freopen("a.out","w",stdout);
    shai();
    while (scanf("%d", &n) == 1)
    {
        tot = 0;
        memset(ansnum, 0, sizeof(ansnum));
        dfs(1, n, 1);
        printf("%d\n", tot);
        sort(ansnum + 1, ansnum + tot + 1);
        for (int i = 1; i <= tot; i++)
            printf("%d ", ansnum[i]);
        if (tot)
            printf("\n");
    }
}