#include <cstdio>
#include <cstring>
#include <algorithm>
#include <complex>
#include <cmath>

const int MAXN = 102005 << 2;
using namespace std;
#define Complex complex<double>
const double pi = acos(-1.0);
struct Fast_Fourier_Transform
{
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
	void FFT(int m, int *c, int t)
	{
		int l = 0;
		for (n = 1; n < m; n <<= 1) l++;
		for (int i = 0; i < n; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
		DFT(a, 1), DFT(b, 1);
		for (int i = 0; i < n; i++) a[i] *= b[i];
		DFT(a, -1);
		for (int i = 0; i < n; i++) a[i] /= n;
		for (int i = 0; i < m; i++) c[i] = c[i] + t * (int)(a[i].real() + 0.5);
	}
}ft1, ft2, ft3;
int a[MAXN], b[MAXN];
int ans[MAXN];
int out[MAXN];
char s1[MAXN], s2[MAXN];

int main()
{
	// freopen("guess.in", "r", stdin);
	// freopen("guess.out", "w", stdout);
	scanf ("%s%s", s1, s2);
	int n = strlen(s1), m = strlen(s2);
	for (int i = 0; i < n; i++) a[i] = s1[i] == '?' ? 0 : s1[i] - 'a' + 1;
	for (int i = 0; i < m; i++) b[m - i - 1] = s2[i] == '?' ? 0 : s2[i] - 'a' + 1;
	// printf ("\n");
	// for (int i = 0; i < n; i++) printf ("%d ", a[i]);
	// printf ("\n");
	// printf ("\n");
	// for (int i = 0; i < m; i++) printf ("%d ", b[i]);
	// printf ("\n");
	for (int i = 0; i < n; i++) ft1.a[i] = a[i] * a[i];
	for (int i = 0; i < m; i++) ft1.b[i] = b[i];
	ft1.FFT(n + m - 1, ans, 1);
	// printf ("\n");
	// for (int i = 0; i < m + n - 1; i++) printf ("%d ", ans[i]);
	// printf ("\n");

	for (int i = 0; i < n; i++) ft2.a[i] = 1;
	for (int i = 0; i < m; i++) ft2.b[i] = b[i] * b[i] * b[i];
	ft2.FFT(n + m - 1, ans, 1);
	// printf ("\n");
	// for (int i = 0; i < m + n - 1; i++) printf ("%d ", ans[i]);
	// printf ("\n");

	for (int i = 0; i < n; i++) ft3.a[i] = 2 * a[i];
	for (int i = 0; i < m; i++) ft3.b[i] = b[i] * b[i];
	ft3.FFT(n + m - 1, ans, -1);
	// printf ("\n");
	// for (int i = 0; i < m + n - 1; i++) printf ("%d ", ans[i]);
	// printf ("\n");

	for (int i = m - 1; i < n; i++) 
		if (!ans[i])
			out[++out[0]] = i - m + 1;
	printf ("%d\n", out[0]);
	for (int i = 1; i <= out[0]; i++) printf ("%d\n", out[i]); 
}

