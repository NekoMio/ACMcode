#pragma GCC optimize("O2")
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
const int MOD = 10007;
const int MAXN = 205;
struct Matrix
{
    int a[405][405];
    int n;
    Matrix()
    {
        memset(a, 0, sizeof (a));
        n = 0;
    }
    Matrix operator * (const Matrix &b) const 
    {
        Matrix ans;
        ans.n = n;
        for (int i = 1; i <= n; i++)
            for (int k = 1; k <= n; k++)
                if (a[i][k] != 0) 
                    for (int j = 1; j <= n; j++)
                        if (b.a[k][j] != 0)
                            ans.a[i][j] = (ans.a[i][j] + a[i][k] * b.a[k][j] % MOD) % MOD;
        return ans;
    }
    Matrix operator ^ (int b)
    {
        Matrix ans, a = *this;
        ans.n = n;
        for (int i = 1; i <= n; i++) ans.a[i][i] = 1;
        while (b)
        {
            if (b & 1) ans = ans * a;
            b >>= 1;
            a = a * a;
        }
        return ans;
    }
}A;
char s[MAXN];
int DP[MAXN][MAXN][MAXN];
int f(int l, int r, int n24)
{
    if (DP[l][r][n24] != -1) return DP[l][r][n24];
    DP[l][r][n24] = 0;
    if (l == r)
    {
        if (n24 == 0) DP[l][r][n24] = 1;
    }
    else
    {
        if (s[l] == s[r])
        {
            if (l + 1 == r)
            {
                if (n24 == 0) DP[l][r][n24] = 1;
            }
            else
                DP[l][r][n24] = f(l + 1, r - 1, n24);
        }
        else if (n24 > 0)
            DP[l][r][n24] = (f(l + 1, r, n24 - 1) + f(l, r - 1, n24 - 1)) % MOD;
    }
    return DP[l][r][n24];
}
int main()
{
    // freopen ("palindrome.in", "r", stdin);
    // freopen ("palindrome.out", "w", stdout);
    scanf ("%s", s + 1);
    int m = strlen(s + 1);
    int n = read() + m;
    int n24 = m - 1, n25 = (m + 1) >> 1, n26 = n25;
    A.n = n24 + n25 + n26;
    for (int i = 1; i <= n24; i++)
    {
        A.a[i][i] = 24;
        A.a[i][i + 1] = 1;
    }
    for (int i = n24 + 1; i <= n24 + n25; i++)
    {
        A.a[i][i] = 25;
        A.a[i][i + n25] = 1;
        if (i != n24 + n25) A.a[i][i + 1] = 1;
    }
    for (int i = n24 + n25 + 1; i <= n24 + n25 + n26; i++)
        A.a[i][i] = 26;
    int t = (n + 1) >> 1;
    static Matrix B = A ^ (t - 1);
    static Matrix C = B * A;
    memset (DP, -1, sizeof (DP));
    int ans = 0;
    for (int n4 = 0; n4 <= n24; n4++)
    {
        int n5 = (m - n4 + 1) >> 1;
        if (t - n4 - n5 < 0) continue;
        ans = (ans + C.a[n24 - n4 + 1][n24 + n5 + n25] * f(1, m, n4) % MOD) % MOD;
        if ((n & 1) && !((m - n4) & 1)) 
            ans = (ans - B.a[n24 - n4 + 1][n24 + n5] * f(1, m, n4) % MOD + MOD) % MOD;
    }
    printf ("%d\n", ans);
}