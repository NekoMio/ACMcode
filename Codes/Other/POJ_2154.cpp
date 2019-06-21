#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int MOD;
int pow_mod(int a, int b)
{
    int ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
int phi(int n)
{
    int ans = n;
    int x = n;
    for (int i = 2; i * i <= n; i++)
        if (x % i == 0)
        {
            ans = ans - ans / i;
            while (x % i == 0) x /= i;
        }
    if (x != 1) ans = ans - ans / x;
    return ans % MOD;
}
int main()
{
    int t = read();
    while (t--)
    {
        int n = read();
        MOD = read();
        int ans = 0;
        for (int i = 1; i * i <= n; i++)
            if (n % i == 0)
            {
                ans = (ans + pow_mod(n % MOD, i - 1) * phi(n / i) % MOD) % MOD;
                if (i * i != n) ans = (ans + pow_mod(n % MOD, n / i - 1) * phi(i) % MOD) % MOD;
            }
        printf ("%d\n", ans);
    }
}