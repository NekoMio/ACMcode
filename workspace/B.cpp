#include <bits/stdc++.h>
using namespace std;
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
int main() {
  int n, m;
  scanf ("%d%d", &n, &m);
  printf ("%lld", pow_mod(pow_mod(2, m) - 1, n));
  // while (1);
}