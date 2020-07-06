#include <bits/stdc++.h>
using namespace std;
long double C[501][501];
double s[505];
long double ans[505];
int main() {
  int n, k;
  C[0][0] = 1;
  C[1][0] = C[1][1] = 1;
  for (int i = 2; i <= 500; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++)
      C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
  }
  scanf ("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) scanf ("%lf", &s[i]);
  for (int i = 1; i <= n; i++) {
    int cnt = 0;
    ans[i] += C[n - 1][k - 1] / C[n][k] * s[i];
    for (int j = (i == n ? 0 : i) + 1; j != i; (j == n) ? (j = 1) : j++) {
      if (C[n - cnt - 1][k - 1] == 0) break;
      cnt++;
      ans[j] += C[n - cnt - 1][k - 1] / C[n][k] * s[i];
    }
  }
  for (int i = 1; i <= n; i++) {
    printf ("%.8Lf ", ans[i]);
  }
}