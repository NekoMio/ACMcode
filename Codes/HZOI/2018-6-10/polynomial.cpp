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
const int MOD = 1000109107;
const int MAXN = 1e6;
int F[MAXN + 2], Inv[MAXN + 2];
int pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int C(int n, int m) {
  if (n < m) return 0;
  return 1ll * F[n] * Inv[m] % MOD * Inv[n - m] % MOD;
}
int main() {
  int ans = 0;
  int S = read(), T = read(), N = read(), M = read();
  F[0] = 1;
  for (int i = 1; i <= MAXN; ++i) F[i] = 1ll * F[i - 1] * i % MOD;
  Inv[MAXN] = pow_mod(F[MAXN], MOD - 2) % MOD;
  for (int i = MAXN - 1; i >= 0; --i) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % MOD;
  for (int i = 0; i <= N; ++i) {
    if (i & 1) ans = (ans - 1ll * C(S - i * T, M) * C(N, i) % MOD + MOD) % MOD;
    else ans = (ans + 1ll * C(S - i * T, M) * C(N, i) % MOD) % MOD;
  }
  printf ("%d\n", ans);
}
