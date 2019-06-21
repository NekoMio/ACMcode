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
const int MOD = 998244353;
const int MAXN = 2000005;
int pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int Inv, rev[MAXN], N;
void Init(int x) {
  N = 1;
  while (N < (x << 1)) N <<= 1;
  Inv = pow_mod(N, MOD - 2);
  for (int i = 1; i <= N; ++i) {
    if (i & 1)
      rev[i] = (rev[i >> 1] >> 1) | N >> 1;
    else
      rev[i] = (rev[i >> 1] >> 1);
  }
}
void FFt(int *a, int op) {
  for (int i = 1; i <= N; ++i)
    if (i < rev[i])
      swap(a[i], a[rev[i]]);
  int wn, w, t;
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
    for (int i = 0; i < N; ++i)
      a[i] = 1ll * a[i] * Inv % MOD;
}
int tmp[MAXN];
void Get_Inv(int *a, int *b, int n) {
  if (n == 1) return b[0] = pow_mod(a[0], MOD - 2), void();
  Get_Inv(a, b, (n + 1) >> 1);
  Init(n);
  for (int i = 0; i < n; ++i) tmp[i] = a[i];
  for (int i = n; i < N; ++i) tmp[i] = 0;
  FFt(tmp, 1), FFt(b, 1);
  for (int i = 0; i < N; ++i) {
    b[i] = 1ll * b[i] * ((2 - 1ll * tmp[i] * b[i] % MOD + MOD) % MOD) % MOD;
  }
  FFt(b, -1);
  for (int i = n; i < N; ++i) b[i] = 0;
}
int a[MAXN], b[MAXN], c[MAXN], f[MAXN], F[MAXN];
int main() {
  int n = read();
  F[0] = 1;
  for (int i = 1; i <= n; ++i) F[i] = 1ll * F[i - 1] * i % MOD;
  for (int i = 0; i <= n; ++i) b[i] = F[i], a[i] = 2 * F[i] % MOD;
  a[0] = (a[0] - 1 + MOD) % MOD;
  Get_Inv(b, c, n + 1);
  FFt(a, 1), FFt(c, 1);
  for (int i = 0; i < N; ++i) c[i] = 1ll * c[i] * a[i] % MOD;
  FFt(c, -1);
  c[0] = (1 - c[0] * 0 + MOD) % MOD;
  for (int i = 1; i <= n; ++i) c[i] = (MOD - 1ll * c[i] * i % MOD) % MOD;
  Get_Inv(c, f, n + 1);
  printf ("%d\n", f[n]);
}
