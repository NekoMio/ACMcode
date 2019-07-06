#include <bits/stdc++.h>
using namespace std;
int ans[65];
int C[65][65];
int main() {
  C[0][0] = 1;
  ans[0] = 1;
  for (int i = 1; i <= 64; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++)
      C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    ans[i] = ans[i - 1] + i - 1 + C[i - 1][3];
  }
  int n;
  while (scanf ("%d", &n) != EOF) {
    printf ("%d\n", ans[n]);
  }
}