#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
long long f[3005][3005];
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i <= m; ++i) f[0][i] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      f[i][j] = (f[i - 1][j] + (j == 0 ? 0 : 4 * j * f[i - 1][j - 1]) +
                (i > 1 && j > 0 ? (i - 1) * j * f[i - 2][j - 1] : 0) +
                (j > 1 ? ((j - 1) * j / 2) * f[i - 1][j - 2] : 0)) % MOD;
      // printf ("%d %d %lld\n", i, j, f[i][j]);
    }
  }
  printf("%lld\n", f[n][m] - 1);
}