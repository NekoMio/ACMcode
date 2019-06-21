#include <bits/stdc++.h>
using namespace std;
char s[705];
int f[705][705][10][2];
const int MOD = 1e9 + 7;
int main() {
  scanf ("%s", s + 1);
  int n = strlen(s + 1);
  for (int i = 1; i <= 9; ++i) f[0][0][i][1] = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= n; ++j) {
      for (int k = 1; k <= 9; ++k) {
        for (int l = 0; l <= 1; ++l) if (f[i][j][k][l]) {
          for (int m = 0; m <= (l ? s[i + 1] - '0' : 9); ++m) {
            (f[i + 1][j + (m >= k)][k][l & (m == s[i + 1] - '0')] += f[i][j][k][l]) %= MOD;
          }
        }
      }
    }
  }
  int ans = 0;
  for (int i = 1, tmp = 1; i <= n; ++i, tmp = (1ll * tmp * 10 + 1) % MOD) {
    for (int j = 1; j <= 9; ++j) {
      ans = (ans + 1ll * tmp * (f[n][i][j][0] + f[n][i][j][1])) % MOD;
    }
  }
  printf ("%d\n", ans);
}