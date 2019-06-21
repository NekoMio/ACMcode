#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int MOD = 1e9 + 7;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int b[10];
int l[10], r[10]; 
int a[10];
long long pow_mod(long long a, long long b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
priority_queue<int, vector<int>, greater<int> > Q;
int main()
{
    // freopen("mouko.in", "r", stdin);
    // freopen("mouko.out", "w", stdout);
    int n = read(), k = read();
    for (int i = 1; i <= n; i++)
        b[i] = read();
    int N = 1;
    for (int i = 1; i <= n; i++)
        l[i] = read(), r[i] = read(), N *= i;
    for (int i = 1; i <= n; i++) a[i] = l[i];
    int Sum = 0;
    int Inv = pow_mod(N, MOD - 2);
    while (N--)
    {
        int i;
        int ans = 0;
        for (i = 1; i <= k; i++)
            Q.push(a[i]);
        int cnt = 0;
        for (; i <= n; i++)
        {
            (ans += (Q.top() * b[++cnt]) % MOD) %= MOD;
            Q.pop();
            Q.push(a[i]);
        }
        while (!Q.empty()) (ans += Q.top() * b[++cnt] % MOD) %= MOD, Q.pop();
        (Sum += ans) %= MOD;
        next_permutation(a + 1, a + n + 1);
    }
    printf ("%lld", (long long)Sum * Inv % MOD);
}