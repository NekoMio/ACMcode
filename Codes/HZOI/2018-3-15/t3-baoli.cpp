#pragma GCC optimize("O2")
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
const int MAXN = 3e6 + 5;
const int MAXM = 3e5 + 5;
long long H[MAXN], L[MAXN];
char s[MAXN], c[MAXM], s_rev[MAXN];
int main()
{
    scanf ("%s", s + 1);
    int n = strlen(s + 1);
    reverse_copy(s + 1, s + n + 1, s_rev + 1);
    int m = read();
    while (m--)
    {
        scanf ("%s", c + 1);
        int len = strlen(c + 1);
        for (int i = 1; i <= n; i++)
        {
            int j = 0;
            for (j = 1; j <= len && i + j - 1 <= n && c[j] == s[i + j - 1]; j++);
            H[i] = (H[i] + (j - 1)) % MOD;
        }
        for (int i = 1; i <= n; i++)
        {
            int j = 0;
            for (j = 1; j <= len && i + j - 1 <= n && c[j] == s_rev[i + j - 1]; j++);
            L[i] = (L[i] + (j - 1)) % MOD;
        }
    }
    reverse(L + 1, L + n + 1);
    long long ans = 0;
    for (int i = 1; i < n; i++)
        ans = (ans + L[i] * H[i + 1] % MOD) % MOD;
    printf ("%lld\n", ans);
    // while (1);
}