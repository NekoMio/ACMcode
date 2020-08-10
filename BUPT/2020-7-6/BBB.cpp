#include <bits/stdc++.h>
using namespace std;
double F[201][201];
int main() {
  int n;
  scanf ("%d", &n);
  F[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= 52 && j <= i; j++) {
      if (j) F[j][i - j] += F[j - 1][i - j] * (156.0 - (j - 1) * 3) / 365;
      if (i - j) F[j][i - j] += F[j][i - j - 1] * (209.0 - (i - j - 1)) / 365;
    }
  }
  long double ans = 1;
  for (int j = 0; j <= 52 && j <= n; j++) {
    ans = ans - F[j][n - j];
  }
  printf ("%.12Lf\n", ans);
}