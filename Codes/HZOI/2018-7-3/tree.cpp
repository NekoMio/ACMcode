// #pragma GCC optimize("O2")
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
int f[50][50], n, MOD, F[50];
double g[50][50];
int pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int C[50][50];
double c[50][50];
int main() {
  // freopen ("tree.in", "r", stdin);
  // freopen ("tree.out", "w", stdout);
  n = read(), MOD = read();
  f[1][1] = g[1][1] = 1;
  F[0] = 1;
  for (int i = 0; i <= 40; ++i) {
    C[i][0] = c[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
      c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
    }
  }
  for (int i = 1; i <= 40; ++i) F[i] = 1ll * i * F[i - 1] % MOD;
  for (int i = 2; i <= n; ++i)
    for (int j = 1; j < i; ++j)
      for (int k = 1; k <= j; ++k)
        for (int l = 1; l <= i - j; ++l) {
          f[i][max(k + 1, l)] = (f[i][max(k + 1, l)] + 1ll * f[j][k] * f[i - j][l] % MOD * C[i - 2][j - 1] % MOD) % MOD;
          g[i][max(k + 1, l)] = g[i][max(k + 1, l)] + g[j][k] * g[i - j][l] * c[i - 2][j - 1];
        }
  int N = 1;
  double NN = 1;
  for (int i = 1; i < n; ++i) N = 1ll * N * i % MOD, NN = NN * i;
  int F_Inv = pow_mod(N, MOD - 2);
  int ans = 0;
  double ans2 = 0;
  for (int i = 1; i <= n; ++i) {
    ans = (ans + 1ll * f[n][i] * i % MOD * F_Inv % MOD) % MOD;
    ans2 = (ans2 + g[n][i] * i / NN);
    // printf ("%d\n", f[n][i]);
  }
  printf ("%d\n", int(round(ans2)));
  printf ("%d\n", ans);
}
