#include <bits/stdc++.h>
using namespace std;
const long double pi = acos(-1.0);
const int M = 100000;
const int MAXN = M + 5;
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
void gmax(int &a, int b) {
  if (a < b) a = b;
}
struct Complex {
  long double x, y;
  Complex(long double _x = 0, long double _y = 0) : x(_x), y(_y) {}
  Complex operator+(const Complex &a) { return Complex(x + a.x, y + a.y); }
  Complex operator-(const Complex &a) { return Complex(x - a.x, y - a.y); }
  Complex operator*(const Complex &a) {
    return Complex(x * a.x - y * a.y, x * a.y + a.x * y);
  }
  void operator*=(const Complex &a) { *this = *this * a; }
  Complex operator*(const long double &a) { return Complex(x * a, y * a); }
  Complex operator/(const long double &a) { return Complex(x / a, y / a); }
  void operator/=(const long double &a) {
    x /= a;
    y /= a;
  }
};
int r[MAXN << 3], N;
Complex A[MAXN << 3], B[MAXN << 3];
void DFT(Complex *a, int f) {
  for (int i = 0; i < N; i++)
    if (r[i] > i) swap(a[i], a[r[i]]);
  Complex wn, w, x, y;
  for (int i = 1; i < N; i <<= 1) {
    wn = Complex(cos(pi / i), f * sin(pi / i));
    for (int j = 0; j < N; j += i << 1) {
      w = 1;
      for (int k = 0; k < i; k++, w *= wn) {
        x = a[j + k];
        y = w * a[j + k + i];
        a[j + k] = x + y;
        a[j + k + i] = x - y;
      }
    }
  }
}
void FFT(int *a, int *b, long long *c, int mx1, int mx2) {
  int m = mx1 + mx2 + 1;
  register int i;
  for (i = 0; i <= mx1; i++) A[i] = Complex(a[i], 0);
  for (i = 0; i <= mx2; i++) B[i] = Complex(b[i], 0);
  int l = 0;
  for (N = 1; N < m; N <<= 1) ++l;
  for (i = mx1 + 1; i < N; i++) A[i] = 0;
  for (i = mx2 + 1; i < N; i++) B[i] = 0;
  for (i = 0; i < N; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
  DFT(A, 1), DFT(B, 1);
  for (i = 0; i < N; i++) A[i] *= B[i];
  DFT(A, -1);
  for (i = 0; i < N; i++) A[i] /= N;
  for (i = 0; i < N; i++) c[i] = (long long)(A[i].x + 0.5);
}
int a[MAXN], b[MAXN], c[MAXN];
int Num1[MAXN], Num2[MAXN], Num4[MAXN];
long long Num3[MAXN << 3];
long long ans = 0;
void Calc(int *a, int *b, int *c, int n) {
  // long long ans = 0;
  register int i;
  int Mx1 = 0, Mx2 = 0;
  for (i = 1; i <= n; i++) Num1[a[i]]++, gmax(Mx1, a[i]);
  for (i = 1; i <= n; i++) Num2[b[i]]++, gmax(Mx2, b[i]);
  if (n <= 1000) {
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        Num3[a[i] + b[j]]++;
  } else {
    FFT(Num1, Num2, Num3, Mx1, Mx2);
  }
  for (i = 2 * M; i >= 1; i--) Num3[i] += Num3[i + 1];
  for (i = M; i >= 1; i--) Num2[i] += Num2[i + 1];
  for (i = 1; i <= n; i++) ans = ans - 1ll * Num1[c[i]] * (Num2[1] - Num2[c[i]]);
  for (i = M; i >= 1; i--) Num1[i] += Num1[i + 1];
  for (i = 1; i <= n; i++) {
    ans = ans + Num3[c[i]];
    ans = ans - 1ll * Num1[c[i] + 1] * n;
    ans = ans - 1ll * Num2[c[i] + 1] * n;
    ans = ans + 1ll * Num1[c[i] + 1] * Num2[c[i] + 1];
  }
  memset(Num2, 0, sizeof(Num2));
  memset(Num1, 0, sizeof(Num1));
  for (i = 1; i <= 2 * M; i++) Num3[i] = 0; 
}
int main() {
  int T = read();
  int cnt = 0;
  register int i;
  while (T--) {
    int n = read();
    ans = 0;
    for (i = 1; i <= n; i++) a[i] = read();
    for (i = 1; i <= n; i++) b[i] = read();
    for (i = 1; i <= n; i++) c[i] = read();
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1);
    sort(c + 1, c + n + 1);
    Calc(a, b, c, n);
    Calc(b, c, a, n);
    Calc(c, a, b, n);
    for (i = 1; i <= n; i++) Num2[b[i]]++, Num4[c[i]]++;
    for (i = 1; i <= n; i++) {
      ans -= 1ll * Num2[a[i]] * Num4[a[i]] * 2;
    }
    for (i = 1; i <= n; i++) Num2[b[i]] = 0, Num4[c[i]] = 0;
    printf("Case #%d: %lld\n", ++cnt, ans);
  }
}