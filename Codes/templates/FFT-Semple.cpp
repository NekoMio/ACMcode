#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 1 << 18 | 5;
namespace FFT
{
const double pi = acos(-1.0);
struct Complex
{
    double x, y;
    Complex operator+(const Complex &a)
    {
        return (Complex){x + a.x, y + a.y};
    }
    Complex operator-(const Complex &a)
    {
        return (Complex){x - a.x, y - a.y};
    }
    Complex operator*(const Complex &a)
    {
        return (Complex){x * a.x - y * a.y, x * a.y + y * a.x};
    }
    Complex operator*(const double &a)
    {
        return (Complex){x * a, y * a};
    }
    Complex Get()
    {
        return (Complex){x, -y};
    }
} c[maxn], c1[maxn], V = (Complex){0.5, 0} * (Complex){0, -0.5};
int rev[maxn], N, FU;
double Inv;
void FFt(Complex *a, int op)
{
    Complex w, wn, t;
    for (int i = 0; i < N; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int k = 2; k <= N; k <<= 1)
    {
        wn = (Complex){cos(op * 2 * pi / k), sin(op * 2 * pi / k)};
        for (int j = 0; j < N; j += k)
        {
            w = (Complex){1, 0};
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
void FFt(int *a, int *b, int *res, int n)
{
    int j;
    N = 1;
    while (N < n)
        N <<= 1;
    FU = N - 1;
    Inv = 1. / N;
    for (int i = 0; i < N; i++)
        if (i & 1)
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
    for (int i = 0; i < N; i++)
        c[i].x = a[i], c[i].y = b[i];
    FFt(c, 1);
    for (int i = 0; i < N; i++)
        j = (N - i) & FU, c1[i] = (c[i] + c[j].Get()) * (c[i] - c[j].Get()) * V;
    FFt(c1, -1);
    for (int i = 0; i < N; i++)
        res[i] = round(c1[i].x);
}
} // FFT

int main(int argc, char const *argv[])
{
    static int a[maxn],b[maxn];
    int n1, n2, m;
    scanf("%d%d", &n1, &n2);
    m = n1 + n2 + 1;
    for (int i = 0; i <= n1; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i <= n2; i++)
        scanf("%d", &b[i]);
    FFT::FFt(a, b, a, m);
    for (int i = 0; i < m; i++)
        printf("%d ", a[i]);
    return 0;
}
