#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
const int MAXN = 1e6 + 1;
int F[MAXN * 2], Inv[MAXN * 2], InvF[MAXN * 2];
int pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int main() {
  int n;
  F[0] = 1;
  for (int i = 1; i < MAXN * 2; i++) F[i] = 1ll * F[i - 1] * i % MOD;
  InvF[MAXN * 2 - 1] = pow_mod(F[MAXN * 2 - 1], MOD - 2);
  for (int i = MAXN * 2 - 2; i >= 1; i--) InvF[i] = 1ll * InvF[i + 1] * (i + 1) % MOD;
  while (scanf("%d", &n) != EOF) {
    printf ("%lld\n", 1ll * InvF[2 * n + 1] * F[n] % MOD * F[n] % MOD);
  }
  // printf ("%lld\n", pow_mod(630, MOD - 2));
}