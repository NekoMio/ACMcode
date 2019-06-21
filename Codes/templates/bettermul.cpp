#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
const double pi = acos(-1.);
struct Complex
{
    double x, y;
    Complex() { ; }
    Complex(double a, double b) : x(a), y(b) {}
    Complex operator+(const Complex &a) { return Complex(x + a.x, y + a.y); }
    Complex operator-(const Complex &a) { return Complex(x - a.x, y - a.y); }
    Complex operator*(const Complex &a) { return Complex(x * a.x - y * a.y, x * a.y + y * a.x); }
    Complex operator*(const double a) { return Complex(x * a, y * a); }
    Complex Get() { return Complex(x, -y); }
} A[150005 << 3], B[150005 << 3];
int rev[150005 << 3], N, FU;
double INV;
void FFt(Complex *a, int op)
{
    Complex w, wn, t;
    for (int i = 0; i < N; i++)
        if (i < rev[i])
            std::swap(a[i], a[rev[i]]);
    for (int k = 2; k <= N; k <<= 1)
    {
        wn = Complex(cos(op * 2 * pi / k), sin(op * 2 * pi / k));
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
            a[i] = a[i] * INV;
}
void FFt(const int *a, const int *b, int *res, int n)
{
    N = 1;
    while (N < n)
        N <<= 1;
    INV = 1. / N;
    for (int i = 0; i < N; i++)
        if (i & 1)
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
    for (int i = 0; i < N; i++)
        A[i].x = a[i], B[i].x = b[i];
    FFt(A, 1), FFt(B, 1);
    for (int i = 0; i < N; i++)
        A[i] = A[i] * B[i];
    FFt(A, -1);
    for (int i = 0; i < N; i++)
        res[i] = round(A[i].x);
}
char s[150005 << 2];
struct BigNum
{
    int len;
    int a[1000005];
    void read()
    {
        scanf("%s", s);
        len = strlen(s);
        for (int i = len - 1, j = 0; i >= 0; i--, j++)
            a[j] = s[i] - '0';
    }
    BigNum operator*(const BigNum &b)
    {
        BigNum ans;
        ans.len = len + b.len - 1;
        FFt(a, b.a, ans.a, ans.len + 1);
        for (int i = 0; i <= ans.len + 2; i++)
        {
            if (ans.a[i] > 9)
            {
                ans.a[i + 1] += ans.a[i] / 10;
                ans.a[i] %= 10;
            }
        }
        while (ans.a[ans.len])
            ans.len++;
        return ans;
    }
    void print()
    {
        for (int i = len - 1; i >= 0; i--)
            printf("%d", a[i]);
        printf("\n");
    }
} a, b;

int main()
{
    //freopen("bettermul.in","r",stdin);
    //freopen("bettermul.out","w",stdout);
    a.read();
    b.read();
    (a * b).print();
    //while (1)
        ;
}
