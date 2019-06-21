#include <bits/stdc++.h>
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0'|| ch > '9') {
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
int Inv3 = pow_mod(3, MOD - 2);
int C(int n, int m) {
  if (n < m) return 0;
  return 1ll * F[n] * Inv[n - m] % MOD * Inv[m] % MOD;
}
int p;
int Calc1(int n, int m, int k) {
  return (1ll * C(n - p, m - 2) * (p - 1) % MOD + C(n - p, m - 1)) * n % MOD;
}
int Calc2(int n, int m, int k) {
  return 1ll * (C(n - p + 1, m - 1) + C(n - p, m - 1)) * n % MOD;  
}
int Calc3(int n, int m, int k) {
  if (m != 3) return 0;
  return 1ll * C(n - p + 1, m - 1) * n % MOD * Inv3 % MOD;
}
int main() {
  int T = read();
  F[0] = 1;
  for (int i = 1; i <= MAXN; ++i) F[i] = 1ll * F[i - 1] * i % MOD;
  Inv[MAXN] = pow_mod(F[MAXN], MOD - 2);
  for (int i = MAXN - 1; i >= 0; --i) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % MOD;
  while (T--) {
    int n = read(), m = read(), k = read();
    p = n / 2 + 1;
    if (k >= 4) { printf ("0\n"); }
    else if (k == 3) { printf ("%d\n", Calc3(n, m, k)); }
    else if (k == 2) { printf ("%d\n", ((Calc2(n, m, k) - 3ll * Calc3(n, m, k)) % MOD + MOD) % MOD); }
    else if (k == 1) { printf ("%d\n", ((Calc1(n, m, k) - 2ll * Calc2(n, m, k) + 3ll * Calc3(n, m, k)) % MOD + MOD) % MOD); }
    else { printf ("%d\n", ((1ll * C(n, m) - Calc1(n, m, k) + Calc2(n, m, k) - Calc3(n, m, k)) % MOD + MOD) % MOD); }
  }
}
