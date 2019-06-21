#include <cstdio>
#include <cstring>
#include <algorithm>
#include <complex>
#include <cmath>
using namespace std;
const int MAXN = 60005 << 2;
const double pi = acos(-1.0);
#define Complex complex<double>
int r[MAXN], n;
Complex a[MAXN], b[MAXN];
void DFT(Complex *a, int f)
{
	for (int i = 0; i < n; i++)
		if (r[i] > i) swap(a[i], a[r[i]]);
	for (int i = 1; i < n; i <<= 1)
	{
		Complex wn(cos(pi / i), f * sin(pi / i));
		for (int j = 0; j < n; j += i << 1)
		{
			Complex w = 1;
			for (int k = 0; k < i; k++, w *= wn)
			{
				Complex x = a[j + k], y = w * a[j + k + i];
				a[j + k] = x + y, a[j + k + i] = x - y;
			}
		}
	}
}
int c[MAXN], m;
void FFT(Complex *a, Complex *b)
{
	int l = 0;
	for (n = 1, m <<= 1; n < m; n <<= 1) ++l;
	for (int i = 0; i < n; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	DFT(a, 1), DFT(b, 1);
	for (int i = 0; i < n; i++) a[i] *= b[i];
	DFT(a, -1);
	for (int i = 0; i < n; i++) a[i] /= n;
	for (int i = 0; i < m; i++) c[i] = (int)(a[i].real() + 0.5);
}
int main()
{
	static char A[MAXN], B[MAXN];
	scanf ("%d%s%s", &m, A, B);
	for (int i = 0; i < m; i++)
		a[i] = A[m - i - 1] - '0', b[i] = B[m - i - 1] - '0';
	FFT(a, b);
	for (int i = 0; i < m; i++)
		if (c[i] >= 10)
			c[i + 1] += c[i] / 10, c[i] %= 10;
		else if (!c[i] && i == m - 1) --m;
	for (int i = m - 1; i != -1; i--) printf ("%d", c[i]);
}