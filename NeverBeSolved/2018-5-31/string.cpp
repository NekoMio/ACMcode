#include <bits/stdc++.h>
using namespace std;
inline long long read() {
  long long x = 0, f = 1;
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
const int MOD = 65537;
const int MAXN = 2e6 + 5;
long long pow_mod(long long a, long long b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int N, rev[MAXN];
int Inv;
void FFT(int *a, int op) {
  for (int i = 0; i < N; ++i)
    if (i < rev[i])
      swap(a[i], a[rev[i]]);
  int w, wn, t;
  for (int k = 2; k <= N; k <<= 1) {
    wn = pow_mod(3, op == 1 ? (MOD - 1) / k : MOD - 1 - (MOD - 1) / k);
    for (int j = 0; j < N; j += k) {
      w = 1;
      for (int i = 0; i < (k >> 1); ++i, w = 1ll * w * wn % MOD) {
        t = 1ll * a[i + j + (k >> 1)] * w % MOD;
        a[i + j + (k >> 1)] = (a[i + j] - t + MOD) % MOD;
        a[i + j] = (a[i + j] + t) % MOD;
      }
    }
  }
  if (op == -1) {
    for (int i = 0; i < N; ++i) {
      a[i] = 1ll * a[i] * Inv % MOD;
    }
  }
}
void Init(int n) {
  N = 1;
  while (N < (n << 1)) N <<= 1;
  Inv = pow_mod(N, MOD - 2);
  for (int i = 1; i < N; ++i) {
    if (i & 1) rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
    else rev[i] = (rev[i >> 1] >> 1);
  }
}
int tmp[MAXN];
void Get_Inv(int *a, int *b, int n) {
  if (n == 1) return b[0] = pow_mod(a[0], MOD - 2), void();
  Get_Inv(a, b, (n + 1) >> 1);
  Init(n);
  for (int i = 0; i < n; ++i) tmp[i] = a[i];
  for (int i = n; i < N; ++i) tmp[i] = 0;
  FFT(tmp, 1), FFT(b, 1);
  for (int i = 0; i < N; ++i) {
    b[i] = 1ll * b[i] * ((2 - 1ll * b[i] * tmp[i] % MOD + MOD) % MOD) % MOD;
  }
  FFT(b, -1);
  for (int i = n; i < N; ++i) b[i] = 0;
}
int Get_Mod(int *a, int ra, int *b, int rb, int *c) {
  while (ra && !a[ra - 1]) --ra;
  while (rb && !b[rb - 1]) --rb;
  if (ra < rb) {
    memcpy (c, a, ra << 2);
    memset (c + ra, 0, (rb - ra) << 2);
    return rb;
  }
  static int tmp1[MAXN], tmp2[MAXN];
  int rc = ra - rb + 1;
  int l = 1;
  while (l < (rc << 1)) l <<= 1;
  memset (tmp1, 0, l << 2);
  memset (tmp2, 0, l << 2);
  reverse_copy (b, b + rb, tmp1);
  Get_Inv(tmp1, tmp2, rc);
  reverse_copy (a, a + ra, tmp1);
  for (int i = rc; i < l; ++i) tmp1[i] = 0;
  Init(rc), FFT(tmp1, 1), FFT(tmp2, 1);
  for (int i = 0; i < N; ++i) tmp1[i] = 1ll * tmp1[i] * tmp2[i] % MOD;
  FFT(tmp1, -1);
  reverse(tmp1, tmp1 + rc);
  Init(ra);
  memcpy (tmp2, b, rb << 2);
  memset (tmp2 + rb, 0, (N - rb) << 2);
  memset (tmp1 + rc, 0, (N - rc) << 2);
  FFT(tmp1, 1), FFT(tmp2, 1);
  for (int i = 0; i < N; ++i) tmp1[i] = 1ll * tmp1[i] * tmp2[i] % MOD;
  FFT(tmp1, -1);
  for (int i = 0; i < rb; ++i) c[i] = (a[i] - tmp1[i] + MOD) % MOD;
  for (int i = rb; i < N; ++i) c[i] = 0;
  while (rb && !c[rb - 1]) --rb;
  return rb;
}
int f[MAXN], Sum[MAXN];
int a[MAXN], b[MAXN], C[MAXN], g[MAXN], d[MAXN];
void Mul(int *a, int *b, int *c, int m) {
  Init(m + m - 1);
  FFT(a, 1);
  if (a != b) FFT(b, 1);
  for (int i = 0; i < N; ++i) {
    c[i] = 1ll * a[i] * b[i] % MOD;
  }
  FFT(c, -1);
  if (a != b) FFT(b, -1);
  Get_Mod(c, m + m - 1, g, m + 1, d);
  for (int i = 0; i < m; ++i) {
    c[i] = d[i];
  }
  for (int i = m; i < m + m - 1; ++i) c[i] = 0;
  return;
}
int F[MAXN], inv[MAXN];
int c(int n, int m) {
  if (n < m) return 0;
  return 1ll * F[n] * inv[m] * inv[n - m] % MOD;
}
int lucas(long long n, long long m) {
  if (n < m) return 0;
  if (n == 0) return 1;
  return 1ll * lucas(n / MOD, m / MOD) * c(n % MOD, m % MOD) % MOD;
}
int Solve(long long n, long long m) {
  int lim = n / (m + 1), ans = 0;
  int P = pow_mod(2, n % (MOD - 1));
  int T = pow_mod(pow_mod(2, MOD - 2), (m + 1) % (MOD - 1));
  for (int i = 0; i <= lim; ++i) {
    if (i & 1) ans = (ans - 1ll * P * lucas(n - i * m, i)) % MOD;
    else ans = (ans + 1ll * P * lucas(n - i * m, i)) % MOD;
    P = 1ll * P * T % MOD;
  }
  return (ans + MOD) % MOD;
}
int main() {
  long long n = read(), m = read();
  if (m == 1) return printf ("1\n"), 0;
  if (m <= 7000) {
    f[0] = 1;
    Sum[0] = 1;
    for (int i = 1; i <= m; ++i) {
      f[i] = Sum[i - 1];
      Sum[i] = (Sum[i - 1] + f[i]) % MOD;
    }
    for (int i = 0; i < m; ++i) {
      g[i] = MOD - 1;
    }
    g[m] = 1;
    if (m & 1) {
      for (int i = 0; i <= m; ++i) {
        g[i] = MOD - g[i];
      }
    }
    a[1] = 1;
    C[0] = 1;
    long long k = n;
    while (k) {
      if (k & 1) Mul(C, a, C, m);
      k >>= 1;
      Mul(a, a, a, m);
    }
    int ans = 0;
    for (int i = 0; i < m; ++i) ans = (ans + 1ll * C[i] * f[i + 1] % MOD) % MOD;
    printf ("%d\n", ans);
  } else {
    F[0] = 1;
    for (int i = 1; i < MOD; ++i) F[i] = 1ll * F[i - 1] * i % MOD;
    inv[MOD - 1] = pow_mod(F[MOD - 1], MOD - 2);
    for (int i = MOD - 2; i >= 0; --i) inv[i] = 1ll * inv[i + 1] * (i + 1) % MOD;
    printf ("%d\n", (Solve(n + 1, m) - Solve(n, m) + MOD) % MOD);
  }
}
