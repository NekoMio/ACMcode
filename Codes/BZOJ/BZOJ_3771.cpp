#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
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
const int MAXN = 5e5 + 5;
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
Complex A[MAXN], B[MAXN], C[MAXN];
Complex tmp[MAXN];
long long ans[MAXN];
int m = 0;
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
    {
        int x = read();
        ans[x]++;
        A[x].x = 1;
        B[2 * x].x = 1;
        C[3 * x].x = 1;
        m = max(m, 3 * x);
    }
    m = m + m + 1;
    N = 1;
    while (N < m) 
        N <<= 1;
    for (int i = 1; i < N; i++) 
        if (i & 1)
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
    Inv = 1. / N;
    FFt(A, 1);
    for (int i = 0; i < N; i++) tmp[i] = A[i] * A[i];
    FFt(tmp, -1);
    for (int i = 0; i < N; i++) ans[i] += round((tmp[i].x - B[i].x) / 2);
    // for (int i = 0; i < N; i++)
    //     if (ans[i])
    //         printf ("%d %lld\n", i, ans[i]);
    // printf ("======================================\n");
    FFt(B, 1);
    for (int i = 0; i < N; i++) B[i] = B[i] * A[i];
    FFt(B, -1);
    for (int i = 0; i < N; i++) tmp[i] = A[i] * A[i] * A[i];
    FFt(tmp, -1);
    for (int i = 0; i < N; i++) ans[i] += round((tmp[i].x - B[i].x * 3 + C[i].x * 2) / 6);
    for (int i = 0; i <= m / 2; i++)
        if (ans[i])
            printf ("%d %lld\n", i, ans[i]);
    // while (1);
}