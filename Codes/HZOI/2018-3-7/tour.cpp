#pragma GCC optimize("O3")
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
const int MAXN = 205;
int MOD;
struct Matrix
{
    long long a[MAXN][MAXN];
    int n;
    Matrix()
    {
        n = 0;
        memset (a, 0, sizeof (a));
    }
    Matrix operator * (const Matrix &b)
    {
        Matrix ans;
        ans.n = n;
        for (int i = 1; i <= n; i++)
            for (int k = 1; k <= n; k++)
                if (a[i][k] != 0)
                    for (int j = 1; j <= n; j++)
                        ans.a[i][j] = (ans.a[i][j] + a[i][k] * b.a[k][j] % MOD) % MOD;
        return ans;
    }
    Matrix operator + (const Matrix &b)
    {
        Matrix ans;
        ans.n = n;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                ans.a[i][j] = (a[i][j] + b.a[i][j]) % MOD;
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
}A, B, ans;
char s[MAXN];
int K[30], t;
int main()
{
    // freopen("tour.in", "r", stdin);
    // freopen("tour.out", "w", stdout);
    int n = read();
    for (int i = 1; i <= n; i++)
    {
        scanf ("%s", s + 1);
        for (int j = 1; j <= n; j++)
            if (s[j] == 'Y') 
                A.a[i][j] = 1;
    }
    A.n = n;
    Matrix C = B = A;
    int k = read() - 1;
    MOD = read();
    while (k) K[++t] = k, k >>= 1;
    sort(K + 1, K + t + 1);
    for (int i = 2; i <= t; i++)
    {
        A = A + A * B;
        B = B * B;
        if (K[i] & 1)
        {
            B = B * C;
            A = A + B;
        }
    }
    long long Ans = 0;
    for (int i = 1; i <= n; i++)
        Ans = (Ans + A.a[i][i]) % MOD;
    printf ("%d\n", Ans);
}