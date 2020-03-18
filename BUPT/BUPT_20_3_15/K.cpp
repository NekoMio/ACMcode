#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
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
  int T, a, b, c, d;
  scanf ("%d", &T);
  while (T--) {
    scanf ("%d%d%d%d", &a, &b, &c, &d);
    printf ("%lld\n", ((d * pow_mod(2, c) % MOD * pow_mod(2, a) % MOD + \
                    (pow_mod(2, c) - 1 + MOD) % MOD * (b + 1) % MOD * pow_mod(2, a) % MOD) % MOD + \
                    pow_mod(2, b + a)) % MOD);
  }
}