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
const int MOD = 1000000009;
const int MAXN = 2e5 + 5;
const double pi = acos(-1.);
struct edge {
  int END, next;
} v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
int size[MAXN], ff[MAXN];
int F[MAXN], Inv[MAXN];
struct Complex {
  double x, y;
  Complex operator+(const Complex &a) const { return (Complex){x + a.x, y + a.y}; }
  Complex operator-(const Complex &a) const { return (Complex){x - a.x, y - a.y}; }
  Complex operator*(const Complex &a) const { return (Complex){x * a.x - y * a.y, x * a.y + a.x * y}; }
  Complex operator*(const double &a) const { return (Complex){x * a, y * a}; }
  inline double real() const { return x; }
  inline double imag() const { return y; }
}X[MAXN * 10], Y[MAXN * 10], Z[MAXN * 10];
Complex conj(const Complex &a) {
  return (Complex){a.x, -a.y};
}
int N, rev[MAXN * 10];
double inv;

Complex w[MAXN * 10];
void FFT(Complex *a, int op) {
  Complex t;
  for (int i = 0; i < N; ++i)
    if (i > rev[i]) swap(a[i], a[rev[i]]);
  w[0] = (Complex){1, 0};
  for (int k = 2; k <= N; k <<= 1) {
    Complex wn = (Complex){cos(pi / (k >> 1)), op * sin(pi / (k >> 1))};
    for (int j = k >> 1; j >= 0; j -= 2) w[j] = w[j >> 1];
    for (int j = 1; j < (k >> 1); j += 2) w[j] = w[j - 1] * wn;
    for (int j = 0; j < N; j += k) {
      for (int i = 0; i < (k >> 1); ++i) {
        t = a[i + j + (k >> 1)] * w[i];
        a[i + j + (k >> 1)] = a[i + j] - t;
        a[i + j] = a[i + j] + t;
      }
    }
  }
  if (op == -1)
    for (int i = 0; i < N; ++i) a[i] = a[i] * inv;
}
void Init(int x) {
  N = 1;
  while (N < x) N <<= 1;
  inv = 1. / N;
  for (int i = 0; i < N; ++i) {
    if (i & 1)
      rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
    else
      rev[i] = (rev[i >> 1] >> 1);
  }
}
void Mul(int *a, int *b, int *ans, int ra) {
  for (int i = 0; i < N; ++i) {
    X[i] = (Complex){double(a[i] >> 15), double(a[i] & 32767)};
    Y[i] = (Complex){double(b[i] >> 15), double(b[i] & 32767)};
  }
  for (int i = 0; i < ra; ++i) ans[i] = 0;
  FFT(X, 1), FFT(Y, 1);
  for (int i = 0; i < N; ++i) {
    int j = i ? N - i : 0;
    Z[i] = ((X[i] + conj(X[j])) * (Y[i] - conj(Y[j])) + 
            (X[i] - conj(X[j])) * (Y[i] + conj(Y[j]))) * 
           (Complex){0, -0.25};
  }
  FFT(Z, -1);
  for (int i = 0; i < N; ++i) {
    ans[i] =
        (ans[i] + ((long long)(Z[i].real() + 0.5) % MOD << 15) % MOD) % MOD;
  }
  for (int i = 0; i < N; ++i) {
    int j = i ? N - i : 0;
    Z[i] = (X[i] - conj(X[j])) * (Y[i] - conj(Y[j])) * (Complex){-0.25, 0} + 
           (X[i] + conj(X[j])) * (Y[i] + conj(Y[j])) * (Complex){0, 0.25};
  }
  FFT(Z, -1);
  for (int i = 0; i < ra; ++i) {
    ans[i] = (ans[i] + (long long)(Z[i].real() + 0.5) % MOD + 
              ((long long)(Z[i].imag() + 0.5) % MOD << 30) % MOD) %
              MOD;
  }
}
struct data {
  int val, id;
  bool operator < (const data &c) const {
    return val < c.val;
  }
}num[MAXN];
int Solve(int *a, int l, int r) {
  int ra = r - l + 2;
  if (ra <= 256) {
    memset (a, 0, ra << 2), a[0] = 1;
    for (int i = l; i <= r; ++i) {
      for (int j = i - l; j != -1; --j) {
        a[j + 1] = (a[j + 1] + 1ll * a[j] * num[i].val % MOD) % MOD;
      }
    }
    return ra;
  }
  // assert(0);
  int mid = l + r >> 1;
  int *f1 = a, r1 = Solve(f1, l, mid);
  int *f2 = a + r1, r2 = Solve(f2, mid + 1, r);
  Init(ra);
  static int tmp1[MAXN * 10], tmp2[MAXN * 10];
  memcpy(tmp1, f1, r1 << 2),  memset (tmp1 + r1, 0, (N - r1) << 2);
  memcpy(tmp2, f2, r2 << 2),  memset (tmp2 + r2, 0, (N - r2) << 2);
  Mul(tmp1, tmp2, a, ra);
  return ra;
}
int tmp[MAXN * 10];
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int k;
int C(int n, int m) {
  if (n < m) return 0;
  return 1ll * F[n] * Inv[m] % MOD * Inv[n - m] % MOD;
}
void Build(int rt, int cnt) {
  Solve(tmp, 1, cnt);
  for (int i = 0; i <= min(cnt, k); ++i)
    ff[rt] = (ff[rt] + 1ll * tmp[i] * C(k, i) % MOD * F[i] % MOD) % MOD;
}
int SumF[MAXN], ans, n;
void MUL(int *a, int c, int cnt) {
  for (int i = cnt; i >= 0; --i) {
    a[i + 1] = (a[i + 1] + 1ll * c * a[i] % MOD) % MOD;
  }
}
int a[MAXN];
int Get_G(int x, int cnt) {
  memcpy(a, tmp, (cnt + 1) << 2);
  for (int i = 0; i <= cnt; ++i) {
    a[i + 1] = ((a[i + 1] - 1ll * x * a[i] % MOD) % MOD + MOD) % MOD;
  }
  int ans = 0;
  for (int i = 0; i <= min(cnt, k); ++i)
    ans = (ans + 1ll * a[i] * C(k, i) % MOD * F[i] % MOD) % MOD;
  return ans;
}
void DFS(int rt, int fa) {
  size[rt] = 1;
  SumF[rt] = 0;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    DFS(v[i].END, rt);
    ans = (ans + 1ll * SumF[rt] * SumF[v[i].END] % MOD) % MOD;
    SumF[rt] = (SumF[rt] + SumF[v[i].END]) % MOD;
    size[rt] += size[v[i].END];
  }
  int cnt = 0;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    num[++cnt] = (data){size[v[i].END], v[i].END};
  }
  Build(rt, cnt);
  sort(num + 1, num + cnt + 1);
  MUL(tmp, n - size[rt], cnt);
  int G;
  for (int i = 1; i <= cnt; ++i) {
    if (num[i].val != num[i - 1].val)
      G = Get_G(num[i].val, cnt);
    ans = (ans + 1ll * G * SumF[num[i].id] % MOD) % MOD;
  }
  SumF[rt] = (SumF[rt] + ff[rt]) % MOD;
  // fprintf (stderr, "%d %d\n", rt, ans);
}
int main() {
  // freopen ("a.in", "r", stdin);
  // freopen ("a.out", "w", stdout);
  memset(first, -1, sizeof(first));
  n = read(), k = read();
  F[0] = 1;
  for (int i = 1; i <= k; ++i) F[i] = 1ll * F[i - 1] * i % MOD;
  Inv[k] = pow_mod(F[k], MOD - 2);
  for (int i = k - 1; i >= 0; --i) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % MOD;
  for (int i = 1; i < n; ++i) {
    int a = read(), b = read();
    add(a, b);
    add(b, a);
  }
  DFS(1, 0);
  printf ("%d\n", ans);
}
