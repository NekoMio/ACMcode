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
int F[1000005], F_Inv[1000005];
int Calc(int n, int m) {
  if (n > m) swap(n, m);
  int ans = 1;
  for (int i = 1; i <= n; ++i)
    ans = 1ll * ans * F[m + i - 1] % MOD * F_Inv[i - 1] % MOD;;
  return ans;
}
int Calc(int n, int m, int v) {
  if (n > m) swap(n, m);
  int ans = 1;
  for (int i = 1; i <= n; ++i)
    ans = 1ll * ans * F[m + i - 1 + v] % MOD * F_Inv[i - 1 + v] % MOD;
  return ans;
}
int main() {
  int T = read();
  F[0] = 1;
  int N = 1000000;
  for (int i = 1; i <= N; ++i) F[i] = 1ll * F[i - 1] * i % MOD; 
  F_Inv[N] = pow_mod(F[N], MOD - 2);
  for (int i = N - 1; i >= 0; --i) F_Inv[i] = 1ll * F_Inv[i + 1] * (i + 1) % MOD;
  while (T--) {
    int A = read(), B = read(), C = read(), D = read();
    A = A - B + 1, C = C - D + 1;
    if (A < C) swap(A, C), swap(B, D);
    if (A >= C && B >= D) {
      printf ("%lld\n", 1ll * F[A * B] * pow_mod(Calc(A, B), MOD - 2) % MOD);
    } else {
      int ans = 1ll * Calc(A - C, B) * Calc(C, D - B) % MOD * Calc(C, B, A - C + D - B) % MOD;
      printf ("%lld\n", 1ll * F[(A - C) * B + C * (D - B) + C * B] * pow_mod(ans, MOD - 2) % MOD);
    }
  }
}