#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int Maxn = 44721;
int prime[4729], tot = 0;
bool isnprime[44722];
void get_prime()
{
    isnprime[1] = 1;
    for (int i = 2; i <= Maxn; i++)
    {
        if (!isnprime[i])
            prime[++tot] = i;
        for (int j = 1; j <= tot; j++)
        {
            if (i * prime[j] > Maxn)
                break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}
int times = 6;
long long pow_mod(long long x, long long y, long long mod)
{
    long long ans = 1;
    while (y)
    {
        if (y & 1)
            ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}
bool judge(int p)
{
    if (p == 2)
        return true;
    for (int i = 1; i <= times; i++)
    {
        int a = rand() % (p - 2) + 2;
        if (pow_mod(a, p, p) != a)
            return false;
    }
    return true;
}
int allans[100];
void dfs(int p, int les, int ans)
{
    if (les == 1)
    {
        allans[++allans[0]] = ans;
        return;
    }
    if (p > tot)
    {
        return;
    }
    if (les - 1 >= prime[p] && judge(les - 1))
        allans[++allans[0]] = ans * (les - 1);
    for (int i = p; prime[i]*prime[i]<les &&i <= tot; i++)
    {
        for (int sum = prime[i] + 1, j = prime[i]; sum <= les; j *= prime[i], sum += j)
        {
            if (les % sum == 0)
            {
                dfs(i + 1, les / sum, ans * j);
            }
        }
    }
}
int main()
{
    get_prime();
    int s;
    while(scanf("%d", &s)!=EOF){
        memset(allans,0,sizeof(allans));
        dfs(1, s, 1);
        printf("%d\n", allans[0]);
        sort(allans + 1, allans + allans[0] + 1);
        for (int i = 1; i <= allans[0]; i++)
        {
            printf("%d ", allans[i]);
        }
        if(allans[0])printf("\n");
    }
    return 0;
}