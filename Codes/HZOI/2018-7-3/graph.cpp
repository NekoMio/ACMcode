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
const int MAXN = 2e5 + 5;
const int MOD = 998244353;
int a[MAXN];
int Pow[MAXN];
int f[MAXN][2][2][2];
int main() {
  int n = read(), p = read();
  for (int i = 1; i <= n; ++i) a[i] = read(); 
  Pow[0] = 1;
  for (int i = 1; i <= n; ++i) Pow[i] = Pow[i - 1] * 2 % MOD;
  if (a[1] == 1 || a[1] == -1) f[1][1][0][1] = 1;
  if (a[1] == 0 || a[1] == -1) f[1][0][1][1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (a[i] == 1 || a[i] == -1) {
      f[i][1][0][1] = (f[i][1][0][1] + 1ll * f[i - 1][0][0][0] * Pow[i - 1] % MOD) % MOD;
      f[i][1][0][1] = (f[i][1][0][1] + 1ll * f[i - 1][1][0][0] * Pow[i - 1] % MOD) % MOD;
      f[i][1][0][0] = (f[i][1][0][0] + 1ll * f[i - 1][1][0][1] * Pow[i - 1] % MOD) % MOD;
      f[i][1][1][1] = (f[i][1][1][1] + 1ll * f[i - 1][1][1][0] * Pow[i - 2] % MOD) % MOD;
      f[i][1][1][1] = (f[i][1][1][1] + 1ll * f[i - 1][1][1][1] * Pow[i - 2] % MOD) % MOD;
      f[i][1][1][1] = (f[i][1][1][1] + 1ll * f[i - 1][0][1][0] * Pow[i - 2] % MOD) % MOD;
      f[i][1][1][0] = (f[i][1][1][0] + 1ll * f[i - 1][1][1][1] * Pow[i - 2] % MOD) % MOD;
      f[i][1][1][0] = (f[i][1][1][0] + 1ll * f[i - 1][1][1][0] * Pow[i - 2] % MOD) % MOD;
      f[i][1][1][0] = (f[i][1][1][0] + 1ll * f[i - 1][0][1][1] * Pow[i - 2] % MOD) % MOD;
      f[i][0][1][0] = (f[i][0][1][0] + 1ll * f[i - 1][0][1][0] * Pow[i - 2] % MOD) % MOD;
      f[i][0][1][1] = (f[i][0][1][1] + 1ll * f[i - 1][0][1][1] * Pow[i - 2] % MOD) % MOD;
    }
    if (a[i] == 0 || a[i] == -1) {
      f[i][0][1][1] = (f[i][0][1][1] + 1ll * f[i - 1][0][0][0] * Pow[i - 1] % MOD) % MOD;
      f[i][0][1][1] = (f[i][0][1][1] + 1ll * f[i - 1][0][1][0] * Pow[i - 1] % MOD) % MOD;
      f[i][0][1][0] = (f[i][0][1][0] + 1ll * f[i - 1][0][1][1] * Pow[i - 1] % MOD) % MOD;
      f[i][1][1][1] = (f[i][1][1][1] + 1ll * f[i - 1][1][1][0] * Pow[i - 2] % MOD) % MOD;
      f[i][1][1][1] = (f[i][1][1][1] + 1ll * f[i - 1][1][1][1] * Pow[i - 2] % MOD) % MOD;
      f[i][1][1][1] = (f[i][1][1][1] + 1ll * f[i - 1][1][0][0] * Pow[i - 2] % MOD) % MOD;
      f[i][1][1][0] = (f[i][1][1][0] + 1ll * f[i - 1][1][1][1] * Pow[i - 2] % MOD) % MOD;
      f[i][1][1][0] = (f[i][1][1][0] + 1ll * f[i - 1][1][1][0] * Pow[i - 2] % MOD) % MOD;
      f[i][1][1][0] = (f[i][1][1][0] + 1ll * f[i - 1][1][0][1] * Pow[i - 2] % MOD) % MOD;
      f[i][1][0][0] = (f[i][1][0][0] + 1ll * f[i - 1][1][0][0] * Pow[i - 2] % MOD) % MOD;
      f[i][1][0][1] = (f[i][1][0][1] + 1ll * f[i - 1][1][0][1] * Pow[i - 2] % MOD) % MOD;
    }
  }
  int ans = 0;
  for (int i = 0; i <= 1; ++i) 
    for (int j = 0; j <= 1; ++j)
      ans = (ans + f[n][i][j][p]) % MOD;
  printf ("%d\n", ans);
}
