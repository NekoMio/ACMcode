#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <complex>
using namespace std;
#define Complex complex<double>
const double pi = acos(-1.);
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 100005 * 8;
int rev[MAXN]; 
double Inv;
int N;
void FFt(Complex *a, int op)
{
    Complex t, w;
    for (int i = 0; i < N; i++)
        if (i > rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 2; k <= N; k <<= 1)
    {
        Complex wn(cos(pi / (k >> 1)), op * sin(pi / (k >> 1)));
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
            a[i] *= Inv;
}
Complex a[MAXN], b[MAXN], g[MAXN];
int main()
{
    int n = read();
    n--;
    for (int i = 0; i <= n; i++)
    {
        double x;
        scanf ("%lf", &x);
        b[n - i] = a[i] = x;
    }
    for (int i = 1; i <= n; i++) g[i] = (1. / i / i);
    int m = n + n + 1;
    N = 1;
    while (N < m)
        N <<= 1;
    Inv = 1. / N;
    for (int i = 0; i < N; i++)
        if (i & 1)
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
    FFt(a, 1), FFt(b, 1), FFt(g, 1);
    for (int i = 0; i < N; i++) a[i] = a[i] * g[i];
    for (int i = 0; i < N; i++) b[i] = b[i] * g[i];
    FFt(a, -1), FFt(b, -1);
    for (int i = 0; i <= n; i++)
        printf ("%.3f\n", a[i].real() - b[n - i].real());
    // while (1);
}