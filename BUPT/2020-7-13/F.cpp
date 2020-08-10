#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;
int lcm[5001][5001][14];
inline int Max(int a, int b, int c, int d) {
  if (a >= b && a >= c && a >= d) return a;
  if (b >= a && b >= c && b >= d) return b;
  if (c >= a && c >= b && c >= d) return c;
  if (d >= a && d >= b && d >= c) return d;
}
int main() {
  int n, m, K;
  scanf("%d%d%d", &n, &m, &K);
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= m; j++)
      lcm[i][j][0] = [&]() -> int {
        if (i && j)
          return i < j ? lcm[i][j - i][0] : lcm[i - j][j][0];
        else
          return i | j;
      }();
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) lcm[i][j][0] = i / lcm[i][j][0] * j;
  for (int k = 1; k <= 13; k++) {
    for (int i = 1; i + (1 << k) - 1 <= n; i++) {
      for (int j = 1; j + (1 << k) - 1 <= m; j++) {
        lcm[i][j][k] = Max(lcm[i][j][k - 1], lcm[i + (1 << (k - 1))][j][k - 1],
                           lcm[i][j + (1 << (k - 1))][k - 1],
                           lcm[i + (1 << (k - 1))][j + (1 << (k - 1))][k - 1]);
      }
    }
  }
  int tmp = (int)(log(K) / log(2));
  long long ans = 0;
  for (int i = 1; i + K - 1 <= n; i++) {
    for (int j = 1; j + K - 1 <= m; j++)
      ans = ans + Max(lcm[i][j][tmp], lcm[i - (1 << tmp) + 1][j][tmp],
                      lcm[i][j - (1 << tmp) + 1][tmp],
                      lcm[i - (1 << tmp) + 1][j - (1 << tmp) + 1][tmp]);
  }
  printf ("%lld\n", ans);
}