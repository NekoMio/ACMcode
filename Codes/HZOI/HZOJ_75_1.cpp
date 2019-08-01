#include <cstdio>
#include <cstring>
#include <algorithm>
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
const int MAXN = 2e3 + 5;
int f[MAXN], c[MAXN], w[MAXN];
int main() {
  int n = read(), m = read();
  for (int i = 1; i <= n; i++)
    w[i] = read();
  f[0] = 1;
  for (int i = 1; i <= n; i++)
    for (int j = m; j >= 0; j--) if (j >= w[i])
      f[j] = (f[j - w[i]] + f[j]) % 10;
  for (int i = 1; i <= n; i++) {
    memset (c, 0, sizeof (c));
    c[0] = 1;
    for (int j = 1; j <= m; j++) {
      if (j < w[i]) c[j] = f[j];
      else c[j] = (f[j] - c[j - w[i]] + 10) % 10;
    }
    for (int i = 1; i <= m; i++) {
      printf ("%d", c[i]);
    }
    printf ("\n");
  }
  // while (1);
}