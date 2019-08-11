#include <bits/stdc++.h>
using namespace std;
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
int main() {
  int T = read();
  while (T--) {
    int n = read(), p = read();
    int ans = 0, a;
    double t, max = 0;
    for (int i = 1; i <= n; i++) {
      a = read();
      scanf ("%lf", &t);
      if (p >= a) {
        if (t > max) {
          ans = i;
          max = t;
        }
      }
    }
    printf ("%d\n", ans);
  }
}