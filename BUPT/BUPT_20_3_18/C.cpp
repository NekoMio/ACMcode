#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
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
int F[1024], size[1024], ans[6];
int main() {
  size[0] = 0;
  for (int i = 1; i < 1024; i++) size[i] = size[i ^ (i & (-i))] + 1;
  int T = read(), n, m;
  while (T--) {
    scanf ("%d%d", &n, &m);
    memset (F, 0, sizeof(F));
    char c[5];
    int a, b, N = (1 << n) - 1;
    F[0] = 1;
    for (int i = 1; i <= m; i++) {
      scanf ("%s", c);
      a = read(), b = read();
      for (int i = 1; i <= 5; i++) ans[i] = 0;
      int M = (1 << (a - 1)) | (1 << (b - 1));
      if (c[0] == '+') {
        for (int i = 0; i <= N; i++) {
          if ((i & M) == M) {
            F[i] = (F[i] + F[i ^ M]) % MOD;
          }
          if ((size[i] & 1) == 0) {
            ans[size[i] >> 1] = (ans[size[i] >> 1] + F[i]) % MOD;
          }
        }
      } else {
        for (int i = 0; i <= N; i++) {
          if ((i & M) == M) {
            F[i] = ((F[i] - F[i ^ M]) % MOD + MOD) % MOD;
          }
          if ((size[i] & 1) == 0) {
            ans[size[i] >> 1] = (ans[size[i] >> 1] + F[i]) % MOD;
          }
        }
      }
      for (int i = 1; i <= n / 2; i++) {
        printf ("%d%c", ans[i], " \n"[i == n / 2]);
      }
    }
  }
}