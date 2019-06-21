#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define int long long
using namespace std;
int prime[27] = {0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101};
map<int, long long> mp[2000005];
map<pair<long long,long long>, int> Hash[26];
int C[21][21];
int Num[27], n, l, r, len;
long long gcd(long long a, long long b)
{
    return b == 0 ? a : gcd(b, a % b);
}
void Update(long long &L, long long &R)
{
    int GCD = gcd(L, R);
    L /= GCD, R /= GCD;   
}
int DFS(int dep, long long L, long long R)
{
    Update(L, R);
    if (Hash[dep].count(pair<long long,long long>(L,R))) return Hash[dep][pair<long long,long long>(L,R)];
    if (dep == 3)
    {
        int ans = 0;
        for (int i = 0; i <= len; i++)
        {
            long long A = L << i, B = R << (len - i);
            Update(A, B);
            if (A > 2000000) continue;
            if (mp[A].count(B))
                ans += C[len][i] * mp[A][B];
        }
        return Hash[dep][pair<long long, long long>(L, R)] = ans;
    }
    int ans = 0;
    for (int i = 0; i <= Num[dep]; i++)
        ans += DFS(dep - 1, L * (i + 1), R * (Num[dep] - i + 1));
    return Hash[dep][pair<long long,long long>(L,R)] = ans;
}
int Ans[17] = {0,1,0,1,0,1,1,1,0,5,3,5,5,13,11,11,11};
signed main()
{
    // freopen("euler.in", "r", stdin);
    // freopen("euler.out", "w", stdout);
    scanf ("%lld", &n);
    if (n <= 16)
    {
        printf ("%lld", Ans[n]);
        return 0;
    }
    for (int i = 1; i <= n; i++)
    {
        int m = i;
        for (int j = 1; j <= 25; j++)
            while (m % prime[j] == 0)
            {
                Num[j]++;
                m /= prime[j];
            }
    }
    for (int i = 0; i <= 20; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    for (int i = 0; i <= Num[1]; i++)
    {
        for (int j = 0; j <= Num[2]; j++)
        {
            for (int k = 0; k <= Num[3]; k++)
            {
                long long A = (i + 1) * (j + 1) * (k + 1);
                long long B = (Num[1] - i + 1) * (Num[2] - j + 1) * (Num[3] - k + 1);
                Update(A, B);
                mp[A][B]++;
            }
        }
    }
    // for (int i = 1; i <= 25; i++) printf ("%d%c", Num[i], " \n"[i == 25]);
    // while (1);
    for (int i = 25; i >= 1; i--)
    {
        if (Num[i] == 1 && Num[i + 1] == 0)
            r = i;
        else if (Num[i] != 1 && Num[i + 1] == 1)
        {
            l = i + 1;
            break;
        }
    }
    len = r - l + 1;
    printf ("%lld", DFS(l - 1, 1, 1) >> 1);
}
