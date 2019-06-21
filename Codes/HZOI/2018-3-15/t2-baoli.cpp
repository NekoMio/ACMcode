#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MOD = 1e9 + 7;
int a[305];
int Num1[305], Num0[305];
int pos[26], cnt;
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
    {
        a[i] = read();
        if (a[i] == -1) pos[++cnt] = i;
    }
    int N = (1 << cnt) - 1;
    long long ans = 0;
    for (int i = 0; i <= N; i++)
    {
        for (int j = 1; j <= cnt; j++)
            a[pos[j]] = ((i >> (j - 1)) & 1);
        for (int j = n; j >= 1; j--)
            Num1[j] = Num1[j + 1] + a[j];
        int len = 0, num = 0;
        for (int j = 1; j <= n; j++)
        {
            Num0[j] = Num0[j - 1] + (!a[j]);
            if (len < (Num0[j] + Num1[j]))
            {
                len = Num0[j] + Num1[j];
                num = Num1[j];
            }
        }
        ans = (ans + 1ll * len * num % MOD) % MOD;
    }
    printf ("%lld\n", ans);
}