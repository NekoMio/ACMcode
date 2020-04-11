#include <bits/stdc++.h>
const int MOD = 1e9 + 7;
using namespace std;
int C4(int n) {
  if (n < 4) return 0;
  return ((__int128_t)n * (n - 1) * (n - 2) * (n - 3) / (2 * 3 * 4)) % MOD; 
}
int C3(int n) {
  if (n < 3) return 0;
  return ((__int128_t)n * (n - 1) * (n - 2) / (2 * 3)) % MOD;
}
int main() {
  int T;
  int n, m;
  scanf ("%d", &T);
  int cnt = 0;
  while (T--) {
    scanf ("%d%d", &n, &m);
    printf ("Case %d: %lld\n", ++cnt, 1ll * (C4(n) + C3(n)) * (C4(m) + C3(m)) % MOD);
  }
}