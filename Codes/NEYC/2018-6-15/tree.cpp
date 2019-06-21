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
const int MAXN = 2e6;
const int MOD = 998244353;
int F[MAXN + 2], Inv[MAXN + 2], n, prime[MAXN + 2], phi[MAXN + 2], cnt;
bool isnprime[MAXN + 2];
void Get_phi() {
  isnprime[1] = 1;
  phi[1] = 1;
  for (int i = 2; i <= MAXN; ++i) {
    if (!isnprime[i]) prime[++cnt] = i, phi[i] = i - 1;
    for (int j = 1; j <= cnt; ++j) {
      if (i * prime[j] >= MAXN) break;
      isnprime[i * prime[j]] = 1;
      if (i % prime[j] == 0) {
        phi[i * prime[j]] = phi[i] * prime[j];
        break;
      }
      phi[i * prime[j]] = phi[i] * (prime[j] - 1);
    }
  }
}
long long C(int n,int m) {
  if (n < m) return 0;
  return 1ll * F[n] * Inv[m] % MOD * Inv[n - m] % MOD;
}
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int main() {
  n = read();
  Get_phi();
  F[0] = 1;
  for (int i = 1; i <= MAXN; ++i) F[i] = 1ll * F[i - 1] * i % MOD;
  Inv[MAXN] = pow_mod(F[MAXN], MOD - 2) % MOD;
  for (int i = MAXN - 1; i >= 0; --i) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % MOD;
  int Ans = 0;
  for (int i = 1; i * i <= n; ++i) {
    if (n % i == 0) {
      Ans = (Ans + 1ll * C(2 * i, i) * phi[n / i] % MOD) % MOD;
      if (i * i != n) Ans = (Ans + 1ll * C(2 * (n / i), (n / i)) * phi[i] % MOD) % MOD;
    }
  }
  printf ("%lld\n", Ans * pow_mod(2 * n, MOD - 2) % MOD);
  // while (1);
}