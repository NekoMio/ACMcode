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
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
const int MAXN = 2e6 + 5;
int F[MAXN];
int C(int n, int m) {
  if (n < m) return 0;
  return F[n] * pow_mod(1ll * F[m] * F[n - m] % MOD, MOD - 2) % MOD;
}
int Calc(int n, int k) {
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans = (ans + pow_mod(k, __gcd(i, n))) % MOD;
  }
  return 1ll * ans * pow_mod(n, MOD - 2) % MOD;
}
int main() {
  int n = read(), k = read(), l = read();
  if (l == n) {
    printf ("%d\n", Calc(n, k));
    return 0;
  }
  F[0] = 1;
  for (int i = 1; i <= 2e6; ++i) F[i] = 1ll * F[i - 1] * i % MOD;
  if (l & 1) {
    printf ("%d\n", (C(k, n) + C(n + k - 1, k - 1)) % MOD);
  } else {
    printf ("%d\n", C(n + k - 1, k - 1) % MOD);
  }
}
