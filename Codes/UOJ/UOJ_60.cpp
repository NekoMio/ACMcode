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
int main(int argc, char const *argv[])
{
  int n;
  scanf ("%d", &n);
  printf ("%lld\n", 4ll * pow_mod(3, n - 1) % MOD);
  for (int i = 1; i <= n; ++i) {
    printf ("A 0 0 0 0\n");
  }
  return 0;
}