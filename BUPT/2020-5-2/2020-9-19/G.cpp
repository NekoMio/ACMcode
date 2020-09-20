#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
int F[100004];
const int Inv2 = (MOD + 1) / 2;
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
  int n, m, a, b;
  F[0] = 1;
  for (int i = 1; i <= 100000; i++) {
    F[i] = 1ll * F[i - 1] * i % MOD;
  }
  scanf ("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    scanf ("%d%d", &a, &b);
  }
  int Ans = 0;
  for (int i = 0; i <= m; i++) {
    Ans = ((Ans + (i & 1 ? -1ll : 1ll) * F[n] * pow_mod(Inv2, i) % MOD * F[m] % MOD * pow_mod(1ll * F[i] * F[m - i] % MOD, MOD - 2) % MOD) % MOD + MOD) % MOD;
  }
  printf ("%d\n", Ans);
}