#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3e5 + 5;
const int MOD = 998244353;
long long F[MAXN], Inv[MAXN];
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  } 
  return ans;
}
long long C(int n, int m) {
  if (n < 0 || m < 0 || n < m) return 0;
  return F[n] * pow_mod(F[m] * F[n - m] % MOD, MOD - 2) % MOD;
}
int main() {
  int T, n, m, k;
  scanf ("%d", &T);
  F[0] = 1;
  for (int i = 1; i < MAXN; i++) F[i] = F[i - 1] * i % MOD;
  Inv[MAXN - 1] = pow_mod(F[MAXN - 1], MOD - 2);
  for (int i = MAXN - 2; i >= 0; i--)
    Inv[i] = Inv[i + 1] * (i + 1) % MOD;
  long long ans = 0;
  while (T--) {
    scanf ("%d%d%d", &n, &m, &k);
    ans = 0;
    for (int i = 0; i <= m; i++) {
      ans += ((i & 1) ? -1 : 1) * C(m, i) * C(k + m - 1 - n * i, m - 1) % MOD;
      ans %= MOD;
    }
    ans = (ans + MOD) % MOD;
    printf ("%lld\n", ans);
  }
}