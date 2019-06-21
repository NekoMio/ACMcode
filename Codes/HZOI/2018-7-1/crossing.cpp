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
int X[320][100005];
int dis[350][350];
void add(int a, int b, int v) {
  dis[a][b] = min(dis[a][b], v);
}
int Work(int n, int m) {
  memset (dis, 0x3f, sizeof (dis));
  for (int j = 1; j <= m; ++j) {
    for (int i = 1; i <= n; ++i) {
      for (int k = i + 1; k <= n; ++k) {
        if (X[i][j] != 0 && X[k][j] != 0) {
          if (X[i][j] > X[k][j]) add(i, k, X[i][j] - X[k][j]);
          else if (X[i][j] < X[k][j])
            add(k, i, X[k][j] - X[i][j]);
        }
      }
    }
  }
  for (int k = 1; k <= n; ++k)
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
  int ans = 0x3f3f3f3f;
  for (int i = 1; i <= n; ++i)
    ans = min(ans, dis[i][i]);
  if (ans < 0x3f3f3f3f)
    return ans;
  else return -1;
}
int main() {
  // freopen ("crossing.in", "r", stdin);
  // freopen ("crossing.out", "w", stdout);
  int n = read(), m = read();
  if (n > m) {
    for (int i = 1; i <= m; ++i)
      for (int j = 1; j <= n; ++j)
        X[i][j] = read();
    printf ("%d\n", Work(m, n));
  } else {
    for (int i = 1; i <= m; ++i)
      for (int j = 1; j <= n; ++j)
        X[j][i] = read();
    printf ("%d\n", Work(n, m));
  }
}
