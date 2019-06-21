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
const int MAXN = 20005;
const int N = 20000;
int a[1005], b[1005];
int f[2][MAXN];
int main() {
  freopen("escape.in", "r", stdin);
  freopen("escape.out", "w", stdout);
  int n = read(), m = read(), Max = m;
  for (int i = 1; i < n; ++i) {
    a[i] = read(), b[i] = read();
    Max = max(a[i], Max);
    Max = max(b[i], Max);
  }
  int now = 0;
  for (int i = 0; i < m; ++i)
    f[now][i] = i;
  for (int i = 1; i < n; ++i) {
    now ^= 1;
    int M = 0;
    memset (f[now], 0, sizeof (f[now]));
    for (int j = 0; j <= 2 * Max; ++j) {
      int t = f[now ^ 1][j];
      if (j < a[i]) {
        f[now][j + b[i]] = max(f[now][j + b[i]], t + b[i]);
        M = max(M, t);
      } else if (j >= a[i] && j < a[i] + b[i]) {
        f[now][j - a[i]] = max(f[now][j - a[i]], t);
      } else if (j >= a[i] + b[i]) {
        f[now][j] = max(f[now][j], t);
      }
    }
    for (int j = 0; j < b[i]; ++j)
      f[now][j] = max(f[now][j], M + j);
  }
  int ans = 0;
  for (int i = 0; i <= 2 * Max; ++i) {
    ans = max(ans, f[now][i]);
  }
  printf ("%d\n", ans);
}
