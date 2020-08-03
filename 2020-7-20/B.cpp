#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
int pow_mod(long long a, int b) {
  int ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int div(int x) {
  int p = 2, ans = 0;
  while (p * p <= x) {
    while (x % p == 0) ans++, x /= p;
    p++;
  }
  if (x != 1) ans++;
  return ans;
}
int main() {
  int T;
  scanf ("%d", &T);
  while (T--) {
    int n, c;
    scanf ("%d%d", &n, &c);
    printf ("%d\n", pow_mod(c, div(n)));
  }
}