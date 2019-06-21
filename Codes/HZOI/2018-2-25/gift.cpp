#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
char s[205];
int DP[205][205][205];
const int ZZH = 10007;
int f(int l, int r, int n24)
{
    if (DP[l][r][n24] != -1) return DP[l][r][n24];
    int &ans = DP[l][r][n24];
    ans = 0;
    if (l == r)
    {
        if (n24 == 0) ans = 1;
    }
    else
    {
        if (s[l] == s[r])
            if (l + 1 == r) 
            {
                if (n24 == 0) ans = 1;
            }
            else
                ans = f(l + 1, r - 1, n24);
        else
            if (n24 > 0)
                ans = (f(l + 1, r, n24 - 1) + f(l, r - 1, n24 - 1)) % ZZH;
    }
    return ans;
}
struct Matrix
{
    int a[405][405];
    int n;
    Matrix()
    {
        memset(a, 0, sizeof (a));
        n = 0;
    }
    int *operator[](int x)
    {
        return a[x];
    }
    const int *operator[](int x) const
    {
        return a[x];
    }
    Matrix operator * (const Matrix &b)
    {
        Matrix ans;
        ans.n = n;
        for (register int i = 1; i <= n; i++)
            for (register int j = 1; j <= n; j++) if (a[i][j] != 0) 
                for (register int k = 1; k <= n; k++) if (b[j][k] != 0)
                    ans[i][k] = (ans[i][k] + a[i][j] * b[j][k] % ZZH) % ZZH;
        return ans;
    }
    Matrix operator ^ (int b)
    {
        Matrix ans, a = *this;
        ans.n = n;
        for (register int i = 1; i <= n; i++) ans[i][i] = 1;
        while (b)
        {
            if (b & 1) ans = ans * a;
            b >>= 1;
            a = a * a;
        }
        return ans;
    }
}A;
int main()
{
    scanf ("%s", s + 1);
    int m = strlen(s + 1);
    int n = read() + m;
    int K = (n + 1) >> 1;
    int R = m - 1, G = (m + 1) >> 1;
    int B = G;
    int M = R + B + G;
    A.n = M;
    for (register int i = 1; i <= R; i++)
    {
        A[i][i] = 24;
        A[i][i + 1] = 1;
    }
    for (register int i = R + 1; i <= R + G; i++)
    {
        A[i][i] = 25;
        if (i != R + G) A[i][i + 1] = 1;
        A[i][i + G] = 1;
    }
    for (register int i = R + G + 1; i <= M; i++)
        A[i][i] = 26;
    static Matrix C = A ^ (K - 1);
    // for (int i = 1; i <= C.n; i++)
    //     for (int j = 1; j <= C.n; j++)
    //         printf ("%d%c", C[i][j], " \n"[j == C.n]);
    A = C * A;
    int ans = 0;
    memset (DP, -1, sizeof (DP));
    for (int n24 = 0; n24 < m; n24++)
    {
        int n25 = (m - n24 + 1) >> 1;
        if (K - n24 - n25 < 0) continue;
        (ans += f(1, m, n24) * A[R - n24 + 1][R + n25 + G] % ZZH) %= ZZH;
        if ((n & 1) && !((m - n24) & 1))
            ans = (ans - f(1, m, n24) * C[R - n24 + 1][R + n25] % ZZH + ZZH) % ZZH;
    }
    printf ("%d", ans);
    // while (1);
}