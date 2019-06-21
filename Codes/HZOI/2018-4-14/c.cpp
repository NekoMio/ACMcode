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
int n, l, MOD;
int f[105][105][10005];
struct Matrix
{
    int a[105][105];
    int n;
    Matrix (int x = 0)
    {
        n = x;
        memset (a, 0, sizeof (a));
    }
    Matrix operator * (const Matrix &b)
    {
        Matrix ans(n);
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++) if (a[i][j])
                for (int k = 0; k <= n; k++) if (b.a[j][k])
                    ans.a[i][k] = (ans.a[i][k] + 1ll * a[i][j] * b.a[j][k] % MOD) % MOD;
        return ans;
    }
    Matrix operator ^ (int b)
    {
        Matrix ans(n), a = *this;
        for (int i = 0; i <= n; i++) ans.a[i][i] = 1;
        while (b)
        {
            if (b & 1) ans = ans * a;
            b >>= 1;
            a = a * a;
        }
        return ans;
    }
}A;
int F(int x, int c, int k)
{
    if (k < 0 || k > x * x || x < c) return 0;
    if (f[x][c][k] != -1) return f[x][c][k];
    if (x == 1) return f[x][c][k] = (c == 0 && k == 0);
    int &ret = f[x][c][k];
    ret = (F(x - 1, c, k - x + 1) * 2 % MOD + F(x - 1, c + 1, k - x - x + 2)) % MOD;
    if (c > 0)
        ret = (ret + 1ll * F(x - 1, c - 1, k) * 2 * c % MOD + 1ll * F(x - 1, c, k - x + 1) * 2 * c % MOD) % MOD;
    if (c > 1) 
        ret = (ret + 1ll * F(x - 1, c - 1, k) * (c - 1) % MOD * c % MOD) % MOD;
    return ret;
}
int c[15005][105];
int C(int x)
{
    // if (l - x + n < 0) return 0;
    return c[x + n][n];
}
void Init()
{
    A.a[0][0] = 1;
    for (int i = 1; i <= n; i++)
        A.a[i][i] = 1, A.a[i - 1][i] = 1;
    A.n = n;
    int t = l - n * n + n;
    int e = n * n;
    if (t < 0) t = 0, e = n + l;
    A = A ^ t;
    for (int i = 0; i <= n; i++)
        c[e][i] = A.a[0][i];
    for (int i = e - 1; i >= 0; i--)
    {
        c[i][0] = 1;
        for (int j = 0; j <= n; j++)
            c[i][j] = (c[i + 1][j] + c[i + 1][j - 1]) % MOD;
    }
}
int main()
{
    // freopen ("1.out", "w", stdout);
    n = read(), l = read(), MOD = read();
    // int Mi = 0, Ma = 0;
    Init();
    long long ans = 0;
    memset (f, -1, sizeof (f));
    for (int i = 1; i <= n * n; i++)
    {
        ans = (ans + 1ll * F(n, 0, i) * C(i) % MOD) % MOD;
        // printf ("%d\n", F(n, 0, i));
    }
    printf ("%lld\n", ans);
    // while (1);
}