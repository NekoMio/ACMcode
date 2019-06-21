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
const int MAXN = 705;
int h[MAXN];
double g[MAXN][MAXN];
int Sum[MAXN], trans[MAXN][MAXN];
int U[MAXN];
int main() {
  int n = read(), k = read(), p = read();
  for (int i = 1; i <= n; ++i)
    h[i] = read();
  int cnt = 0;
  for (int i = 2; i <= n; ++i)
    if (h[i] > h[1]) U[++cnt] = h[i];
  U[++cnt] = h[1];
  sort(U + 1, U + cnt + 1);
  for (int i = 1; i <= cnt; ++i) U[i] = U[i] + U[i - 1];
  for (int i = 1; i <= cnt; ++i) {
    g[i][0] = U[1];
    for (int j = 1; j < i; ++j) {
      for (int k = 1; k < i; ++k) {
        if (g[i][j] < (g[k][j - 1] + U[i] - U[k]) / (i - k + 1)) {
          g[i][j] = (g[k][j - 1] + U[i] - U[k]) / (i - k + 1);
          trans[i][j] = k;
        }
      }
    }
    for (int j = 1; j < i; ++j) {
      printf ("%d ", trans[i][j]);
    }
    printf ("\n");
  }
  printf ("%.10f\n", g[cnt][min(k, cnt - 1)]);
}
