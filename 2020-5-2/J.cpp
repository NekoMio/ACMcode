#include <bits/stdc++.h>
using namespace std;
int main() {
  long long a, b;
  while (scanf ("%lld%lld", &a, &b) != EOF) {
    if (a == 0 && b == 0) break;
    double ans = 0;
    for (int i = a; i <= b; i++) {
      ans += 1. / 3 * pow(i, -2. / 3);
    }
    printf ("%.5E\n", ans * 1e-15);
  }
}