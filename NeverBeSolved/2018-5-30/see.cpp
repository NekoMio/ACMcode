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
const double pi = acos(-1.);
const int MOD = 99991;
const int MAXN = 100005;
struct Complex {
  double x, y;
  Complex operator + (const Complex &a) const { return (Complex){x + a.x, y + a.y}; }
  Complex operator - (const Complex &a) const { return (Complex){x - a.x, y - a.y}; }
  Complex operator * (double z) const { return (Complex){x * z, y * z}; }
  Complex operator * (const Complex &a) const { return (Complex){x * a.x - y * a.y, x * a.y + y * a.x}; }
}A[MAXN << 4], w[MAXN];
int X[MAXN];
int pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int N, rev[MAXN << 2];
double Inv;
void FFt(Complex *a, int op) {
  for (int i = 1; i < N; ++i)
    if (i < rev[i])
      swap(a[i], a[rev[i]]);
  Complex t;
  for (int k = 2; k <= N; k <<= 1) {
    for (int j = 0; j < N; j += k) {
      for (int i = 0; i < (k >> 1); ++i) {
        t = a[i + j + (k >> 1)] * w[N / k * i];
        a[i + j + (k >> 1)] = a[i + j] - t;
        a[i + j] = a[i + j] + t;
      }
    }
  }
  if (op == -1)
    for (int i = 0; i < N; ++i) {
      a[i] = a[i] * Inv;
    } 
}
int tmp[MAXN];
int Solve(Complex *a, int l, int r) {
  int len = r - l + 2;
  if (len <= 256) {
    memset (tmp, 0, sizeof (tmp[0]) * len), tmp[0] = 1;
    for (int i = l; i <= r; ++i) {
      for (int j = i - l; j != -1; --j) {
        tmp[j + 1] = (tmp[j + 1] + 1ll * tmp[j] * X[i] % MOD) % MOD;
      }
    }
    for (int i = 0; i < len; ++i) a[i] = (Complex){tmp[i], 0};
    return len;
  }
  int mid = l + r >> 1;
  Complex *f1 = a;
  int r1 = Solve(f1, l, mid);
  Complex *f2 = a + r1;
  int r2 = Solve(f2, mid + 1, r);
  N = 1;
  while (N < len) N <<= 1;
  Inv = 1. / N;
  for (int i = 1; i < N; ++i) 
    if (i & 1) rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
    else rev[i] = (rev[i >> 1] >> 1);
  for (int i = 0; i <= N; ++i) w[i] = (Complex){cos(pi * 2 / N * i), sin(pi * 2 / N * i)};
  static Complex tmp1[MAXN << 2], tmp2[MAXN << 2];
  memcpy(tmp1, f1, r1 * sizeof (a[0])), memset (tmp1 + r1, 0, (N - r1) * sizeof (a[0])), FFt(tmp1, 1);
  memcpy(tmp2, f2, r2 * sizeof (a[0])), memset (tmp2 + r2, 0, (N - r2) * sizeof (a[0])), FFt(tmp2, 1);
  for (int i = 0; i < N; ++i) a[i] = tmp1[i] * tmp2[i];
  for (int i = 0; i <= N; ++i) w[i] = (Complex){cos(pi * 2 / N * i), -sin(pi * 2 / N * i)};
  FFt(a, -1);
  for (int i = 0; i < len; ++i) a[i] = (Complex){double(((long long)round(a[i].x)) % MOD), 0};
  return len; 
}
int c[MAXN];
int main() {
  // freopen ("see2.in", "r", stdin);
  int n = read(), k = read();
  for (int i = 1; i <= n; ++i) {
    c[i] = read();
  }
  int f0 = read(), f1 = read();
  for (int i = 1; i <= n; ++i)
    X[i] = pow_mod(3, c[i]);
  Solve(A, 1, n);
  // printf ("%d\n", ((int)A[k].x + MOD) % MOD);
  int a1 = 1ll * ((f0 + f1) % MOD) * pow_mod(4, MOD - 2) % MOD;
  int ans = ((long long)A[k].x) % MOD * a1 % MOD;
  for (int i = 1; i <= n; ++i)
    X[i] = ((c[i] & 1 ? -1 : 1) + MOD) % MOD;
  Solve(A, 1, n);
  ans = (ans + ((long long)A[k].x) % MOD * ((f0 - a1 + MOD) % MOD) % MOD + MOD) % MOD;
  // ans = (ans + MOD) % MOD;
  printf ("%d\n", ans);
}
