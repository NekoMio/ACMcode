#include <bits/stdc++.h>
using namespace std;
inline long long read() {
  long long x = 0, f = 1;
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
long long f[20][170][170][2];
int C[20];
long long Calc(int t, int n) {
  memset (f, 0, sizeof (f));
  f[0][0][0][1] = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= t; ++j) {
      for (int k = 0; k <= t; ++k) {
        for (int o = 0; o <= 1; ++o) if (f[i][j][k][o]) {
          int tp = (o ? C[i + 1] : 9);
          for (int l = 0; l <= tp; ++l) {
            if (j + l <= t)
              f[i + 1][j + l][(k * 10 + l) % t][o && (l == tp)] += f[i][j][k][o];
          }
        }
      }
    }
  }
  return f[n][t][0][0] + f[n][t][0][1];
}
int main() {
  long long n = read();
  int cnt = 0;
  while (n) {
    C[++cnt] = n % 10;
    n /= 10;
  }
  n = cnt;
  reverse(C + 1, C + n + 1);
  long long ans = 0;
  for (int i = 1; i <= 162; ++i) {
    ans += Calc(i, n);
  }
  printf ("%lld\n", ans);
  // printf ("%.3f\n", (double)clock() / CLOCKS_PER_SEC);
}