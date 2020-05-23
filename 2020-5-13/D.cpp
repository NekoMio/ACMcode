#include <bits/stdc++.h>
using namespace std;
long long Calc(long long p, long long b, long long q, long long n) {
  if (p == 0) return 0;
  if (p >= q || b >= q) {
    return n * (n + 1) * (p / q) / 2 + (b / q) * (n + 1) + Calc(p % q, b % q, q, n);
  } else {
    return n * ((p * n + b) / q) - Calc(q, q - b - 1, p, ((p * n + b) / q) - 1);
  }
}
int main() {
  int t;
  scanf ("%d", &t);
  int p, q, n;
  for (int i = 1; i <= t; i++) {
    scanf ("%d%d%d", &p, &q, &n);
    printf ("%lld\n", 1ll * p * n * (n + 1) / 2 - q * Calc(p, 0, q, n));
  }
}