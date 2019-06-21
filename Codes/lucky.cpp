#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
const int MOD = 1000000007;
int a[100005], num, k;
int bin[10];
long long F[100005];
long long f[1050][1050];
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
long long C(int n, int m)
{
    if (m == 0)
        return 1;
    if (m > n || m < 0 || n < 0)
        return 0;
    return F[n] * pow_mod(F[m] * F[n - m] % MOD, MOD - 2) % MOD;
}
map<int, int> Mp, Now;
void DFS(int x, int Dep)
{
    if (Dep >= 9)
        return;
    Mp[x * 10 + 4] = 0;
    DFS(x * 10 + 4, Dep + 1);
    Mp[x * 10 + 7] = 0;
    DFS(x * 10 + 7, Dep + 1);
}
int main()
{
    //freopen("lucky.in", "r", stdin);
    //freopen("lucky.out", "w", stdout);
    bin[0] = 1;
    for (int i = 1; i <= 9; i++)
        bin[i] = bin[i - 1] * 10;
    DFS(0, 0);
    F[0] = 1;
    for (int i = 1; i <= 100000; i++)
    {
        F[i] = F[i - 1] * i % MOD;
    }
    int n, num = 0;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        if (Mp.count(a[i]))
        {
            Mp[a[i]]++;
        }
        else
            num++;
    }
    map<int, int>::iterator it;
    for (it = Mp.begin(); it != Mp.end(); it++)
    {
        if (it->second == 1)
            num++;
        if (it->second > 1)
            Now[it->first] = it->second;
    }
    int N = min((int)Now.size(), k);
    long long ans = 0;
    f[0][0] = 1;
    it = Now.begin();
    for (int i = 1; i <= N; it++, i++)
    {
        f[i][0] = 1;
        for (int j = 1; j <= N; j++)
        {
            f[i][j] = (f[i - 1][j] + f[i - 1][j - 1] * (it->second)) % MOD;
        }
    }
    for (int i = 0; i <= N; i++)
    {
        ans = (ans + C(num, k - i) * f[N][i]) % MOD;
    }
    printf("%lld\n", ans);
}
