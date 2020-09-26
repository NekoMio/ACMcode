#include <bits/stdc++.h>
using namespace std;
long long Sum;
int Max;
int main() {
  int T;
  scanf ("%d", &T);
  while (T--) {
    int n, m, k, a;
    Sum = 0;
    Max = 0;
    scanf ("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++) {
      scanf ("%d", &a);
      if (a <= k) {
        Sum = Sum + 2 * (k - a);
        Max = max(Max, k - a);
      } else {
        Sum = Sum + 2 * (a - k);
      }
    }
    printf ("%lld\n", Sum - 2 * Max + (k - 1) * 2);
  }
}