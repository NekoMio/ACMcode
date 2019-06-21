#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
double pi = acos(-1.);
double eps = 1e-4;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct Complex
{
    double x, y;
    Complex(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    Complex operator + (const Complex &a) const { return Complex(x + a.x, y + a.y); }
    Complex operator - (const Complex &a) const { return Complex(x - a.x, y - a.y); }
    Complex operator * (const Complex &a) const { return Complex(x * a.x - y * a.y, x * a.y + a.x * y); }
    Complex rev() { return Complex(-x, -y); }
}A[30], B[30], C[30], D[30], Inv;
int n;
void DFT(Complex *a, Complex *b, int f)
{
    Complex w(1, 0), wn(cos(2 * pi / n), f * sin(2 * pi / n));
    for (int i = 0; i < n; i++, w = w * wn)
    {
        Complex c(1, 0);
        for (int j = 0; j < n; j++, c = c * w)
            b[i] = b[i] + a[j] * c;
    }
    if (f == -1) for (int i = 0; i < n; i++) b[i] = b[i] * Inv;
}
Complex Sqrt(Complex a)
{
    double b = round((sqrt(a.x * a.x + a.y * a.y) - a.x) / 2);
    double c = (sqrt(a.x * a.x + a.y * a.y) + a.x) / 2;
    double a1 = sqrt(c), b1 = sqrt(b);
    if (2 * a1 * b1 == a.y) return Complex(a1, b1);
    else return Complex(a1, -b1);
}
int Cnt;
int ans[30];
bool Same[30];
int main()
{
    // freopen ("a.in", "r", stdin);
    // freopen ("a.out", "w", stdout);
    // freopen ("2.out", "w", stdout);
    int T = read();
    while (T--)
    {
        n = read();
        Cnt = 0;
        for (int i = 0; i < n; i++)
            A[i] = Complex(read(), 0);
        bool tmp = 0;
        for (int j = 1; j < n; j++)
            if (fabs(A[j].x - A[n - j].x) > eps)
            {
                tmp = 1;
                break;
            }
        if (tmp)
        {
            printf ("0\n");
            continue;
        }
        for (int i = 0; i < n; i++) B[i] = Complex(0, 0);
        Inv = Complex(1. / n, 0);
        DFT(A, B, 1);
        for (int i = 0; i < n; i++)
            B[i] = Sqrt(B[i]);
        // for (int i = 0; i < n; i++)

        // for (int i = 0; i < n; i++) printf ("%.3f\n", B[i].x);
        // printf ("\n");
        int m = (n / 2);
        int N = (1 << (m + 1)) - 1;
        for (int i = 0; i <= N; i++)
        {
            bool flag = 0;
            for (int j = 0; j <= m; j++)
                C[j] = (i & (1 << j)) ? B[j] : B[j].rev();
            for (int j = m + 1; j < n; j++)
                C[j] = C[n - j];
            for (int i = 0; i < n; i++) D[i] = Complex(0, 0);
            DFT(C, D, -1);
            // for (int j = 0; j < n; j++) printf ("%.4f ", D[j].x);
            // printf ("\n");
            for (int j = 0; j < n; j++)
                if (D[j].x < -eps || fabs(D[j].x - round(D[j].x)) > eps)
                {
                    flag = 1;
                    if (flag) break;
                }
            if (flag) continue;
            // for (int j = 1; j < n; j++)
            //     if (round(D[j].x) != round(D[n-j].x))
            //     {
            //         flag = 1;
            //         break;
            //     }
            // if (flag) continue;
            Cnt++;
            // for (int j = 0; j < n; j++) printf ("%d ", (int)round(D[j].x)); 
            // printf ("\n");
            for (int j = 0; j < n; j++)
            {
                if (round(D[j].x) < ans[j] || Cnt == 1)
                {
                    flag = 1;
                    break;
                }
                else if (round(D[j].x) > ans[j]) break;
            }
            if (flag) for (int j = 0; j < n; j++) ans[j] = round(D[j].x);
        }
        if (Cnt) 
        {
            int cnt = 0;
            for (int i = 0; i <= m; i++) 
                if (fabs(B[i].x) <= eps) cnt++;
            cnt = 1 << cnt;
            printf ("%d ", Cnt / cnt);
            for (int i = 0; i < n; i++)
                printf ("%d ", ans[i]);
            printf ("\n");
        }
        else printf ("0\n");
    }
    // while (1);
}