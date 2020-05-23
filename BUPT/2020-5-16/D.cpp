#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-10;
int main() {
  int t;
  scanf ("%d", &t);
  while (t--) {
    int h1, m1, h2, m2, alpha;
    scanf ("%d:%d%d:%d%d", &h1, &m1, &h2, &m2, &alpha);
    double Start = h1 * 30 + m1 * 1.0 / 2, End = h2 * 30 + m2 * 1.0 / 2;
    double b = m1 * 6;
    int ans = 0;
    if (alpha == 90) {
      for (int T = -60; T <= 60; T++) {
        double x = (Start - b + alpha + 180 * T) / 11;
        if (End - Start - x >= -eps  && x - 0 >= -eps)
          ans++;
        // if (End - Start - x < -eps) break;
      }
    } else {
      for (int T = -60; T <= 60; T++) {
        double x = (Start - b + alpha + 360 * T) / 11;
        if (End - Start - x >= -eps  && x - 0 >= -eps)
          ans++;
        // if (End - Start - x < -eps) break;
      }
    }
    printf ("%d\n", ans);
  }
}