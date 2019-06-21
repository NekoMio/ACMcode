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
const int MOD = 10086;
struct P
{
    int a[65];
    int cnt;
    P()
    {
        memset (a, 0, sizeof (a));
    }
    void Build(int *x, int n)
    {
        static int tmp[65];
        for (int i = 1; i <= n; i++)
        {
            for (int j = 31; j >= 0; j--)
            {
                if (x[i] & (1ll << j))
                {
                    if (tmp[j]) x[i] ^= tmp[j];
                    else
                    {
                        tmp[j] = x[i];
                        for (int k = j - 1; k >= 0; k--) if (tmp[k] && (tmp[j] & (1 << k))) tmp[j] ^= tmp[k];
                        for (int k = j + 1; k <= 31; k++) if (tmp[k] & (1 << j)) tmp[k] ^= tmp[j];
                        break;
                    }
                }
            }
        }
        for (int i = 0; i <= 31; i++) if (tmp[i]) a[cnt++] = i;
        cnt--;
    }
    int Query(int x)
    {
        int res = 0;
        for (int i = 0; i <= cnt; i++) if (x & (1ll << a[i])) res |= (1ll << i);
        return res % MOD;
    }
}p;
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
int a[100005];
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    p.Build(a, n);
    int k = read();
    int res = p.Query(k);
    res = (res * pow_mod(2, n - p.cnt - 1) % MOD + 1) % MOD;
    printf("%d\n", res);
}