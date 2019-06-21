#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
using namespace std;
unsigned int tmp1[100005], tmp2[100005], s[100005];
int prime[100005], tot;
int mu[100005];
bool isnprime[100005];
int a[100005];
int N = 100000;
int comp(const int &c, const int &b)
{
    return s[c] < s[b];
}
void Get_Fun()
{
    s[1] = mu[1] = 1;
    tmp1[1] = tmp2[1] = 0;
    for (int i = 2; i <= N; i++)
    {
        if (!isnprime[i])
        {
            prime[++tot] = i;
            mu[i] = -1;
            tmp1[i] = i + 1, tmp2[i] = i;
            s[i] = i + 1;
        }
        for (int j = 1; j <= tot; j++)
        {
            if (i * prime[j] > N)
                break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                mu[i * prime[j]] = 0;
                s[i * prime[j]] = s[i] / tmp1[i] * (tmp1[i] + tmp2[i] * prime[j]);
                tmp1[i * prime[j]] = tmp1[i] + tmp2[i] * prime[j];
                tmp2[i * prime[j]] = tmp2[i] * prime[j];
                break;
            }
            mu[i*prime[j]] = -mu[i];
            s[i * prime[j]] = s[i] * s[prime[j]];
            tmp1[i * prime[j]] = prime[j] + 1;
            tmp2[i * prime[j]] = prime[j];
        }
    }
    for (int i = 1; i <= N; i++)
        a[i] = i;
    sort(a + 1, a + N + 1, comp);
}
unsigned int Sum[100005];
#define lowbit(_) ((_) & (-_))
void add(int a, int b)
{
    for (int i = a; i <= N; i += lowbit(i))
        Sum[i] += b;
}
unsigned int Query(int a)
{
    unsigned int ans = 0;
    for (int i = a; i > 0; i -= lowbit(i))
        ans += Sum[i];
    return ans;
}
struct data
{
    int n, m, a, ID;
    bool operator<(const data &b) const
    {
        return a < b.a;
    }
} Q[20005];
unsigned int ans[20005];
unsigned int Query(data S)
{
    if (S.n > S.m)
        swap(S.n, S.m);
    unsigned int ans = 0,last;
    for (int i = 1; i <= S.n; i = last + 1)
    {
        last = min(S.n / (S.n / i), S.m / (S.m / i));
        ans += (Query(last) - Query(i - 1)) * (S.n / i) * (S.m / i);
    }
    return ans;
}
int main(int argc, char const *argv[])
{
    freopen("sdoi2014shb.in","r",stdin);
    freopen("sdoi2014shb.out","w",stdout);
    int T;
    Get_Fun();
    scanf("%d", &T);
    for (int i = 1; i <= T; i++)
        scanf("%d%d%d", &Q[i].n, &Q[i].m, &Q[i].a), Q[i].ID = i;
    sort(Q + 1, Q + T + 1);
    for (int i = 1, j = 1; i <= T; i++)
    {
        while (s[a[j]] <= Q[i].a && j <= N)
        {
            for (int k = 1; k * a[j] <= N; k++)
                add(k * a[j], s[a[j]] * mu[k]);
            j++;
        }
        ans[Q[i].ID] = Query(Q[i]);
    }
    for (int i = 1; i <= T; i++)
    {
        printf("%d\n",((ans[i]<<1)>>1));
    }
    return 0;
}
