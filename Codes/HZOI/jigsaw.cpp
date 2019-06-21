#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int prime[200005], tot;
bool isnprime[1000005];
void Get_prime()
{
    isnprime[1] = 1;
    for (int i = 2; i <= 1000000; i++)
    {
        if(!isnprime[i]) 
            prime[++tot] = i;
        for (int j = 1; j <= tot; j++)
        {
            if(i * prime[j] > 1000000) break;
            isnprime[prime[j] * i] = 1;
            if(i % prime[j] == 0) 
                break;
        }
    }
}
struct Query
{
    int opt, l, r;
}Q[200005];
int a[200005];
int Index, ans[200005];
int main()
{
    Get_prime();
    int n, q, k;
    scanf("%d%d%d", &n, &k, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= q; i++)
    {
        scanf("%d%d%d", &Q[i].opt, &Q[i].l, &Q[i].r);
    }
    while (Q[q].opt & 1) q--;
    bool ok = 0; int lastans = 0;
    for (int i = 1; i <= q; i++)
    {
        if(!ok)
        {
            if(!(Q[i].opt & 1)) a[Q[i].l] = Q[i].r;
            else ok = 1;
        }
        else
        {
            if(Q[i].opt & 1)
            {
                lastans = Q[i].opt ^ 2;
                Q[i].l ^= lastans, Q[i].r ^= lastans;
                a[Q[i].l] = Q[i].r; 
            }
            else
            {
                lastans = Q[i].opt^1;ans[++Index] = lastans;
            }
        }
    }
    lastans = Q[q].opt ^ 1; Q[q].l ^= lastans, Q[q].r ^= lastans;
    sort(a + Q[q].l, a + Q[q].r + 1);
    int l = 0;
    for (int i = Q[q].l; i <= Q[q].r; i++)
        if(!isnprime[a[i]])
        {
            l++;
            if(l == k)
                ans[++Index] = a[i];
        }
    for (int i = 1; i <= Index; i++)
        printf("%d\n", ans[i]);
}