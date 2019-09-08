#include <bits/stdc++.h>
using namespace std;
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
const int MOD = 100003;
const int MAXN = 1e5 + 5;
const long double pi = acos(-1.0);
#define Complex complex<long double>
int r[MAXN << 3], N;
Complex A[MAXN << 3], B[MAXN << 3];
void DFT(Complex *a, int f)
{
	for (int i = 0; i < N; i++)
		if (r[i] > i) swap(a[i], a[r[i]]);
	for (int i = 1; i < N; i <<= 1)
	{
		Complex wn(cos(pi / i), f * sin(pi / i));
		for (int j = 0; j < N; j += i << 1)
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
void FFT(long long *a, int m1, long long *b, int m2, long long *c)
{
  int m = m1 + m2 + 1;
  for (int i = 0; i <= m1; i++) A[i] = Complex(a[i], 0);
  for (int i = 0; i <= m2; i++) B[i] = Complex(b[i], 0);
	int l = 0;
	for (N = 1, m <<= 1; N < m; N <<= 1) ++l;
  for (int i = m1 + 1; i < N; i++) A[i] = 0;
  for (int i = m2 + 1; i < N; i++) B[i] = 0;
	for (int i = 0; i < N; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	DFT(A, 1), DFT(B, 1);
	for (int i = 0; i < N; i++) A[i] *= B[i];
	DFT(A, -1);
	for (int i = 0; i < N; i++) A[i] /= N;
	for (int i = 0; i < N; i++) c[i] = (long long)(A[i].real() + 0.5) % MOD;
}
int s[MAXN];
long long Ans[20][MAXN], tmp[20][MAXN], bin[MAXN], f[MAXN];
void Divide(int l, int r, int dep) {
  if (l == r) {
    Ans[dep][0] = 1;
    Ans[dep][1] = bin[s[l] % (MOD - 1)];
    return;
  }
  int mid = l + r >> 1;
  Divide(l, mid, dep + 1);
  for (int i = 0; i <= mid - l + 1; i++) tmp[dep][i] = Ans[dep + 1][i];
  Divide(mid + 1, r, dep + 1);
  FFT(tmp[dep], mid - l + 1, Ans[dep + 1], r - mid, Ans[dep]);
}
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while(b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
long long C(int n, int m) {
  return f[n] * pow_mod(f[m] * f[n - m] % MOD, MOD - 2) % MOD;
}
int main() {
  int n = read(), a = read(), Q = read();
  bin[0] = 1;
  f[0] = 1;
  for (int i = 1; i <= MAXN - 1; i++) bin[i] = bin[i - 1] * a % MOD, f[i] = f[i - 1] * i % MOD;
  for (int i = 1; i <= n; i++)
    s[i] = read();
  Divide(1, n, 0);
  for (int i = 1; i <= Q; i++) {
    int k = read();
    printf ("%lld\n", (Ans[0][k] - C(n, k) + MOD) % MOD * pow_mod(a - 1, MOD - 2) % MOD);
  }
  // while(1);
}