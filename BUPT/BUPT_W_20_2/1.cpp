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
const int MAXN = 3e5 + 4;
long long a[MAXN];
long long f[MAXN][4];
int main() {
  int n = read(), x = read();
  for (int i = 1; i <= n; i++) {
    a[i] = read();
  }
  for (int i = 1; i <= n; i++) {
    f[i][1] = max(f[i - 1][1] + a[i], a[i]);
    f[i][2] = max(max(f[i - 1][1], f[i - 1][2]), 0ll) + a[i] * x;
    f[i][3] = max(f[i - 1][3], f[i - 1][2]) + a[i];
    f[i][0] = max(f[i - 1][0], max(f[i][1], max(f[i][2], f[i][3])));
  }
  printf ("%lld\n", f[n][0]);
  // while (1);
}