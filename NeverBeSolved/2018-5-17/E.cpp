#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <complex>
#include <cmath>
#include <iostream>
using namespace std;
// #define Complex complex<double>
const double pi = acos(-1.);
struct Complex
{
    double a, b;
    // Complex() {}
    // Complex(double _a, double _b): a(_a), b(_b) {}
    Complex operator*(const Complex &c) const { return (Complex){a * c.a - b * c.b, a * c.b + b * c.a};}
    Complex operator*(const double c) const { return (Complex){a * c, b * c};}
    Complex operator-(const Complex &c) const { return (Complex){a - c.a, b - c.b}; }
    Complex operator+(const Complex &c) const { return (Complex){a + c.a, b + c.b}; }
    inline double real() {return a; }
    inline double imag() {return b; }
};
Complex conj(Complex &x)
{
    return (Complex){x.a, -x.b};
}
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int MOD, n;
int pow_mod(long long a, int b)
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
const int MAXN = 2e5 + 5;
int prime[MAXN], phi[MAXN], cnt;
bool isnprime[MAXN];
void Get_Phi()
{
    isnprime[1] = 1, phi[1] = 1;
    for (int i = 2; i <= MAXN - 5; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > MAXN - 5) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
}
int rev[MAXN * 4]; 
double Inv;
int N;
Complex w[MAXN * 4];
void FFT(Complex *a, int op)
{
    Complex t;
    for (int i = 0; i < N; i++)
        if (i > rev[i]) swap(a[i], a[rev[i]]);
    w[0] = (Complex){1, 0};
    for (int k = 2; k <= N; k <<= 1)
    {
        Complex wn = (Complex){cos(pi / (k >> 1)), op * sin(pi / (k >> 1))};
        for (int j = k >> 1; j >= 0; j -= 2) w[j] = w[j >> 1];
        // for(int j=i>>1;j>=0;j-=2)w[j]=w[j>>1];
        for (int j = 1; j < k >> 1; j += 2) w[j] = w[j - 1] * wn;
        // for(int j=1;j<i>>1;j+=2)w[j]=w[j-1]*g;
        for (int j = 0; j < N; j += k)
        {
            for (int i = 0; i < (k >> 1); i++)
            {
                t = a[i + j + (k >> 1)] * w[i];
                a[i + j + (k >> 1)] = a[i + j] - t;
                a[i + j] = a[i + j] + t;
            }
        }
    }
    if (op == -1)
        for (int i = 0; i < N; i++)
            a[i] = a[i] * Inv;
}
void Init(int m)
{
    N = 1;
    while (N < m)
        N <<= 1;
    Inv = 1. / N;
    for (int i = 0; i < N; i++)
        if (i & 1)
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
}
Complex X[MAXN * 4], Y[MAXN * 4], Z[MAXN * 4];
void Mul(int *a, int *b, int len1, int len2, int *ans)
{
    for (int i = 0; i < len1 + len2; i++) ans[i] = 0;
    if ((len1 <= 100 && len2 <= 100) || min(len1, len2) <= 5)
    {
        for (int i = 0; i < len1; i++)
            for (int j = 0; j < len2; j++)
                ans[i + j] = (ans[i + j] + 1ll * a[i] * b[j] % MOD) % MOD;
        N = 0;
        return;
    }
    Init(len1 + len2);
    for (int i = 0; i < N; i++)
    {
        X[i] = (Complex){double(a[i] >> 15), double(a[i] & 32767)};
        Y[i] = (Complex){double(b[i] >> 15), double(b[i] & 32767)};
    }
    FFT(X, 1), FFT(Y, 1);
    for (int i = 0; i < N; i++)
    {
        int j = i ? N - i : 0;
        Z[i] = ((X[i] + conj(X[j])) * (Y[i] - conj(Y[j])) + (X[i] - conj(X[j])) * (Y[i] + conj(Y[j]))) * (Complex){0, -0.25};
        // if (len1 == 10001) printf ("(%f,%f) (%f,%f)\n", (double)X[i].a, (double)X[i].b, (double)Y[i].a, (double)Y[i].b);
    }
    FFT(Z, -1);
    for (int i = 0; i < N; i++)
    {
        ans[i] = (ans[i] + ((long long)(Z[i].real() + 0.5) % MOD << 15) % MOD) % MOD;
    }
    for (int i = 0; i < N; i++)
    {
        int j = i ? N - i : 0;
        Z[i] = (X[i] - conj(X[j])) * (Y[i] - conj(Y[j])) * (Complex){-0.25, 0} + (X[i] + conj(X[j])) * (Y[i] + conj(Y[j])) * (Complex){0, 0.25};
        // if (len1 == 10001) printf ("(%f,%f)\n", (double)Z[i].a, (double)Z[i].b);
    }
    FFT(Z, -1);
    for (int i = 0; i < len1 + len2 - 1; i++)
    {
        ans[i] = (ans[i] + (long long)(Z[i].real() + 0.5) % MOD + ((long long)(Z[i].imag() + 0.5) % MOD << 30) % MOD) % MOD;
    }
}
int F[MAXN], inv[MAXN], A[MAXN], C[MAXN * 2];
int main()
{
	// freopen ("1004.in", "r", stdin);
	// freopen ("1.out", "w", stdout);
    int T = read();
    Get_Phi();
    while (T--)
    {
        n = read(), MOD = read();
        F[0] = 1;
        for (int i = 1; i <= n; i++) F[i] = 1ll * F[i - 1] * i % MOD;
        inv[n] = pow_mod(F[n], MOD - 2);
        for (int i = n - 1; i >= 0; i--) inv[i] = 1ll * inv[i + 1] * (i + 1) % MOD;
        int ans = 0;
        for (int d = 1; d <= n; d++)
        {
            int tmp = 0;
            for (int i = 0; i <= N; i++) A[i] = 0;
            for (int i = 0; i <= n / d; i++) A[i] = inv[i * d];
            Mul(A, A, n / d + 1, n / d + 1, C);
            for (int i = 0; i <= n / d; i++)
                tmp = (tmp + 1ll * inv[n - i * d] * C[i] % MOD) % MOD;
            tmp = 1ll * tmp * F[n] % MOD * phi[d] % MOD;
            ans = (ans + tmp) % MOD;
            // printf ("%d\n", ans);
        }
        for (int i = 1; i <= n; i++) ans = (ans - phi[i] + MOD) % MOD;
        // for(int i=1;i<=n;i++)ans=dec(ans,euler[i]);
        ans = 1ll * ans * pow_mod(3, n) % MOD;
        printf ("%d\n", ans);
    }
}
