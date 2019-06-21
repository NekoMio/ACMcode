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
int F[6][10008], a[20], MOD;
int P[6] = {10007, 2, 3, 11, 397, 0};
int exP[6] = {0, 5, 7, 101, 0, 0};
int pk[6] = {0, 125, 343, 10201, 0, 0};
int phip[6] = {0, 100, 294, 10100, 0, 0};
int TT[6][10205];
long long pow_mod(long long a, int b, int p)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % p;
        b >>= 1;
        a = a * a % p;
    }
    return ans;
}
int C(int n, int m, int id)
{
    if (n < m || m < 0 || n < 0) return 0;
    return 1ll * F[id][n] * pow_mod(1ll * F[id][m] * F[id][n - m] % P[id], P[id] - 2, P[id]) % P[id];
}
int lucas(int n, int m, int id)
{
    if (n < m || n < 0 || m < 0) return 0;
    if (m == n || m == 0) return 1;
    return 1ll * lucas(n / P[id], m / P[id], id) * C(n % P[id], m % P[id], id) % P[id];
}
int Num(unsigned int x)
{
    unsigned int tmp = x
                     - ((x >> 1) & 033333333333)
                     - ((x >> 2) & 011111111111);
    tmp = (tmp + (tmp >> 3)) & 030707070707;
    return tmp % 63;
}
long long Mul(int n, int id)
{
    if (n == 0) return 1;
    long long ans = 1;
    if (n / pk[id])
    {
        //for (int i = 2; i <= pk[id]; i++)
        //  if (i % exP[id])
        //      ans = ans * i % pk[id];
        ans = pow_mod(TT[id][pk[id]], n / pk[id], pk[id]);
    }
    ans = ans * TT[id][n % pk[id]] % pk[id];
    //for (int i = 2; i <= n % pk[id]; i++)
    //  if (i % exP[id])
    //      ans = ans * i % pk[id];
    return ans * Mul(n / exP[id], id) % pk[id];
}
int exlucas(int n, int m, int id)
{
    if (n < m || n < 0 || m < 0) return 0;
    if (m == n || m == 0) return 1;
    long long a = Mul(n, id), b = Mul(m, id), c = Mul(n - m, id);
    int t = 0;
    for (int i = n; i; i /= exP[id]) t += i / exP[id];
    for (int i = m; i; i /= exP[id]) t -= i / exP[id];
    for (int i = n - m; i; i /= exP[id]) t -= i / exP[id];
    return a * pow_mod(b, phip[id] - 1, pk[id]) % pk[id] * pow_mod(c, phip[id] - 1, pk[id]) % pk[id] * pow_mod(exP[id], t, pk[id]) % pk[id];
}
long long CRT(int *a, int *b, int n)
{
    long long N = 1, Ni, now, ans = 0;
    for (int i = 0; i <= n; i++) N *= a[i];
    for (int i = 0; i <= n; i++)
    {
        Ni = N / a[i];
        now = pow_mod(Ni, a[i] - 2, a[i]);
        ans = (ans + (b[i] * now % N) * Ni % N) % N;    
    }
    return ans;
}
long long cRT(int *a, int *b, int n)
{
    long long N = 1, Ni, now, ans = 0;
    for (int i = 1; i <= n; i++) N *= a[i];
    for (int i = 1; i <= n; i++)
    {
        Ni = N / a[i];
        now = pow_mod(Ni, phip[i] - 1, a[i]);
        ans = (ans + (b[i] * now % N) * Ni % N) % N;    
    }
    return ans;
}
int b[6];
long long Calc(int n, int m)
{
    if (n < 0 || m < 0 || n < m) return 0;
    for (int i = 0; i <= 4; i++)
        b[i] = lucas(n, m, i);
    return CRT(P, b, 4);
}
long long Calc2(int n, int m)
{
    if (n < 0 || m < 0 || n < m) return 0;
    for (int i = 1; i <= 3; i++)
    {
        b[i] = exlucas(n, m, i);
    }
    return cRT(pk, b, 3);
}
int main()
{
    int T = read();
    MOD = read();
    for (int j = 0; j <= 4; j++)
    {
        F[j][0] = 1;
        for (int i = 1; i <= 10006; i++)
            F[j][i] = 1ll * F[j][i - 1] * i % P[j];
    }
    for (int j = 1; j <= 3; j++)
    {
        TT[j][0] = 1;
        for (int i = 1; i <= pk[j]; i++)
            if (i % exP[j]) TT[j][i] = TT[j][i - 1] * i % pk[j];
            else TT[j][i] = TT[j][i - 1];
    }
    while (T--)
    {
        int n = read(), n1 = read(), n2 = read(), m = read();
        for (int i = 1; i <= n1; i++) a[i] = read();
        for (int i = 1; i <= n2; i++) m -= (read() - 1);
        if (MOD == 10007)
        {
            int N = (1 << n1) - 1;
            int ans = 0;
            for (int i = 0; i <= N; i++)
            {
                int tmp = m;
                for (int j = 1; j <= n1; j++) 
                    if (i & (1 << (j - 1)))
                        tmp -= a[j];
                if (Num(i) & 1) ans = (ans - lucas(tmp - 1, n - 1, 0) + MOD) % MOD;
                else ans = (ans + lucas(tmp - 1, n - 1, 0)) % MOD;
            }
            printf ("%d\n", ans);
        }
        else if (MOD == 262203414)
        {
            int N = (1 << n1) - 1;
            int ans = 0;
            for (int i = 0; i <= N; i++)
            {
                int tmp = m;
                for (int j = 1; j <= n1; j++) 
                    if (i & (1 << (j - 1)))
                        tmp -= a[j];
                if (Num(i) & 1) ans = (ans - Calc(tmp - 1, n - 1) + MOD) % MOD;
                else ans = (ans + Calc(tmp - 1, n - 1)) % MOD;
            }
            printf ("%d\n", ans);
        }
        else
        {
            // printf ("-------");
            int N = (1 << n1) - 1;
            int ans = 0;
            for (int i = 0; i <= N; i++)
            {
                int tmp = m;
                for (int j = 1; j <= n1; j++) 
                    if (i & (1 << (j - 1)))
                        tmp -= a[j];
                if (Num(i) & 1) ans = (ans - Calc2(tmp - 1, n - 1) + MOD) % MOD;
                else ans = (ans + Calc2(tmp - 1, n - 1)) % MOD;
            }
            printf ("%d\n", ans);
        }
    }
}
