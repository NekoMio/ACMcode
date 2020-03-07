#include <bits/stdc++.h>
using namespace std;
long long pow_mod(long long a, long long b, long long p) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % p;
    b >>= 1;
    a = a * a % p;
  }
  return ans;
}
int main() {
  int T, cnt = 0;
  scanf ("%d", &T);
  while (T--) {
    int n;
    scanf ("%d", &n);
    double TMP = 0;
    for (int i = 0; i < n; i++) {
      TMP += (4. / (8 * i + 1) * pow_mod(16, n - i - 1, 8 * i + 1) - 2. / (8 * i + 4) * pow_mod(16, n - i - 1, 8 * i + 4) - 1. / (8 * i + 5) * pow_mod(16, n - i - 1, 8 * i + 5) - 1. / (8 * i + 6) * pow_mod(16, n - i - 1, 8 * i + 6));
    }
    TMP -= (int)TMP;
    if (TMP < 0) TMP++;
    TMP *= 16;
    printf ("Case #%d: %d %X\n", ++cnt, n, int(TMP));
  }
}