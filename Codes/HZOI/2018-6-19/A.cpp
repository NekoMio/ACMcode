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
const int MOD = 1e9 + 7;
const int MAXN = 1000005;
int F[MAXN], Inv[MAXN];
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int C(int n, int m) {
  if (n == m) return 1;
  if (n < 0 || m < 0 || n < m) return 0;
  return 1ll * F[n] * Inv[n - m] % MOD * Inv[m] % MOD; 
}
int n, k;
int f(int x) {
  if (k == 2) return C(x, n - x - 2);
  int d = n / k;
  int ans = 0;
  for (int i = 0; i <= d; ++i) {
    if (i & 1) ans = (ans - 1ll * C(n - i * k - 1 - k, x - 1) * C(x, i) % MOD + MOD) % MOD;
    else ans = (ans + 1ll * C(n - i * k - 1 - k, x - 1) * C(x, i) % MOD) % MOD;
  }
  return ans;
}
int main() {
  n = read(), k = read();
  int m = n - k + 1;
  F[0] = 1;
  for (int i = 1; i <= n; ++i) F[i] = 1ll * F[i - 1] * i % MOD;
  Inv[n] = pow_mod(F[n], MOD - 2);
  for (int i = n - 1; i >= 0; --i) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % MOD;
  int ans = 0;
  for (int i = 1; i <= m; ++i) {
    ans = (ans + 1ll * f(i - 1) * F[i] % MOD * F[m - i] % MOD) % MOD;
    // printf ("%d\n", f(i - 1));
  }
  printf ("%d\n", (ans - F[m] + MOD) % MOD);
}

