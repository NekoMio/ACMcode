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
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int f[2][(1 << 20) + 1], m, a[35];
int Get(int S, int t) {
  return (S >> ((t - 1) << 1)) & 3;
}
int Set(int S, int x, int t) {
  S ^= (Get(S, t) << ((t - 1) << 1));
  return S | (x << ((t - 1) << 1));
}
int main() {
  int n = read();
  for (int i = 1; i <= n; ++i)
    a[i] = read(), m += a[i];
  int now = 0;
  int S = 0;
  int N = (1 << ((n << 1))) - 1;
  for (int i = 1; i <= n; ++i) S = Set(S, a[i], i);
  f[now][S] = 1;
  for (int i = 1; i < m; ++i) {
    now ^= 1;
    memset (f[now], 0, sizeof (f[now]));
    for (int s = 0; s <= N; ++s) if (f[now ^ 1][s]) {
      int Inv = 0;
      for (int j = 1; j <= n; ++j) if (Get(s, j)) Inv++;
      Inv = pow_mod(Inv, MOD - 2);
      for (int j = 1; j <= n; ++j) if (Get(s, j)) {
        int tp = Set(Set(s, 0, j), Get(s, j) - 1, j);
        (f[now][tp] += 1ll * f[now ^ 1][s] * Inv % MOD) %= MOD;
      }
    }
  }
  for (int i = 1; i <= n; ++i)
    printf ("%d ", f[now][Set(0, 1, i)]);
}
