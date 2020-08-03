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
int a[205][205];
int Sum[205][205];
int main() {
  int T = read();
  while (T--) {
    int n = read(), m = read();
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        a[i][j] = read();
      }
    }
    for (int j = 1; j <= m; j++) {
      for (int i = 1; i <= n; i++) {
        Sum[i][j] = Sum[i - 1][j] + a[i][j];
      }
    }
    double ans = 0;
    for (int i = n; i >= 1; i--) {
      for (int j = 1; j <= m; j++) {
        ans = max(ans, 1. * Sum[i][j] / a[i][j]);
      }
    }
    printf ("%.9f\n", ans);
  }
}