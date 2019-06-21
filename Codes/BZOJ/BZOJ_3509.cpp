#include <cmath>
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
const int MAXN = 1e6;
const double pi = acos(-1.);
struct Complex
{
    double x, y;
    Complex() { x = y = 0; }
    Complex(double a, double b) : x(a), y(b) {}
    Complex operator+(const Complex &a) { return Complex(x + a.x, y + a.y); }
    Complex operator-(const Complex &a) { return Complex(x - a.x, y - a.y); }
    Complex operator*(const Complex &a) { return Complex(x * a.x - y * a.y, x * a.y + y * a.x); }
    Complex operator*(const double a) { return Complex(x * a, y * a); }
    Complex Get() { return Complex(x, -y); }
};
double Inv;
int N;
int rev[MAXN];
void FFt(Complex *a, int op)
{
    Complex wn, w, t;
    for (int i = 0; i < N; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int k = 2; k <= N; k <<= 1)
    {
        wn = Complex(cos(pi / (k >> 1)), op * sin(pi / (k >> 1)));
        for (int j = 0; j < N; j += k)
        {
            w = Complex(1, 0);
            for (int i = 0; i < (k >> 1); i++, w = w * wn)
            {
                t = a[i + j + (k >> 1)] * w;
                a[i + j + (k >> 1)] = a[i + j] - t;
                a[i + j] = a[i + j] + t;
            }
        }
    }
    if (op == -1)
        for (int i = 0; i < N; i++)
            a[i] = a[i] * Inv;
}
int Sum1[MAXN], Sum2[MAXN];
int W[MAXN];
int l[MAXN], r[MAXN];
Complex A[65537], B[65537];
int main()
{
    int n = read();
    for (int i = 0; i < n; i++)
        W[i] = read();
    int len = min((int)sqrt(n) * 6, n);
    int num = n / len;
    if (n % len) num++;
    long long ans = 0;
    for (int i = 1; i <= num; i++)
    {
        l[i] = (i - 1) * len;
        r[i] = min(l[i] + len - 1, n - 1);
    }
    for (int i = 1; i <= num; i++)
    {
        for (int j = l[i]; j <= r[i]; j++)
        {
            for (int k = j + 1; k <= r[i]; k++) 
                if (2 * W[j] - W[k] >= 0)
                    ans += Sum1[2 * W[j] - W[k]];
            Sum1[W[j]]++;
        }
    }
    for (int i = num; i >= 1; i--)
    {
        for (int j = l[i]; j <= r[i]; j++)
        {
            for (int k = j + 1; k <= r[i]; k++)
                if (2 * W[k] - W[j] >= 0)
                    ans += Sum2[2 * W[k] - W[j]];
        }
        for (int j = l[i]; j <= r[i]; j++)
            Sum2[W[j]]++;
    }
    N = 65536;
    Inv = 1. / N;
    for (int i = 1; i < N; i++)
        if (i & 1) 
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
    for (int i = 2; i < num; i++)
    {
        memset (A, 0, sizeof (A));
        memset (B, 0, sizeof (B));
        for (int j = 0; j < l[i]; j++) A[W[j]].x++;
        for (int j = r[i] + 1; j < n; j++) B[W[j]].x++;
        FFt(A, 1), FFt(B, 1);
        for (int j = 0; j < N; j++) A[j] = A[j] * B[j];
        FFt(A, -1);
        for (int j = l[i]; j <= r[i]; j++) ans += round(A[2 * W[j]].x);
    }
    printf ("%lld\n", ans);
}