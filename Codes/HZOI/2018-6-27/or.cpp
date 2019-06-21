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
const int MAXN = 200005;
const int MOD = 998244353;
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int rev[MAXN], inv, N;
void Init(int n) {
  N = 1;
  while (N < (n << 1)) N <<= 1;
  inv = pow_mod(N, MOD - 2) % MOD;
  for (int i = 1; i < N; ++i) {
    if (i & 1)
      rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
    else
      rev[i] = (rev[i >> 1] >> 1);
  }
}
void FFt(int *a, int op) {
  for (int i = 1; i < N; ++i)
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
  if (op == -1)
    for (int i = 0; i < N; ++i) a[i] = 1ll * a[i] * inv % MOD;
}
int bin[MAXN], F[MAXN], Inv[MAXN];
int f[MAXN], k;
int tmp1[MAXN], tmp2[MAXN], ans[MAXN];
void pow_mod(int *ans, int *a, int b) {
  ans[0] = 1;
  int Ans = 0, A = 1;
  while (b) {
    if (b & 1) {
      Ans = Ans + A;
      int t = 1;
      for (int i = 0; i <= k; ++i) {
        tmp1[i] = 1ll * ans[i] * t % MOD;
        t = 1ll * t * bin[A] % MOD;
      }
      for (int i = 0; i <= k; ++i) tmp2[i] = a[i];
      for (int i = k + 1; i < N; ++i) tmp1[i] = tmp2[i] = 0;
      FFt(tmp1, 1), FFt(tmp2, 1);
      for (int i = 0; i < N; ++i) tmp1[i] = 1ll * tmp1[i] * tmp2[i] % MOD;
      FFt(tmp1, -1);
      for (int i = 0; i <= k; ++i) ans[i] = tmp1[i];
    }
    b >>= 1;
    int t = 1;
    for (int i = 0; i <= k; ++i) {
      tmp1[i] = 1ll * a[i] * t % MOD;
      t = 1ll * t * bin[A] % MOD;
    }
    for (int i = 0; i <= k; ++i) tmp2[i] = a[i];
    for (int i = k + 1; i < N; ++i) tmp1[i] = tmp2[i] = 0;
    FFt(tmp1, 1), FFt(tmp2, 1);
    for (int i = 0; i < N; ++i) tmp1[i] = 1ll * tmp1[i] * tmp2[i] % MOD;
    FFt(tmp1, -1);
    for (int i = 0; i <= k; ++i) a[i] = tmp1[i];
    A = A * 2;
  }
}
int C(int n, int m) {
  return 1ll * F[n] * Inv[m] % MOD * Inv[n - m] % MOD;
}
int main() {
  // freopen ("or.in", "r", stdin);
  // freopen ("or.out", "w", stdout);
  int n = read();
  k = read();
  bin[0] = 1;
  for (int i = 1; i <= k; ++i) bin[i] = bin[i - 1] * 2 % MOD;
  F[0] = 1;
  for (int i = 1; i <= k; ++i) F[i] = 1ll * F[i - 1] * i % MOD;
  Inv[k] = pow_mod(F[k], MOD - 2);
  for (int i = k - 1; i >= 0; --i) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % MOD;
  Init(k + 1);
  for (int i = 1; i <= k; ++i) f[i] = Inv[i];
  pow_mod(ans, f, n);
  int Ans = 0;
  for (int i = 1; i <= k; ++i) Ans = (Ans + 1ll * C(k, i) * ans[i] % MOD * F[i] % MOD) % MOD;
  printf ("%d\n", Ans); 
}
