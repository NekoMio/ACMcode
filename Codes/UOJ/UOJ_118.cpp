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
const int MAXN = 1e5 + 5;
int dis[MAXN][5], a[MAXN], b[MAXN];
int main() {
  int n = read(), m = read();
  for (int i = 1; i <= n; ++i) a[i] = read();
  for (int i = 1; i <= m; ++i) b[i] = read();
  for (int i = 2; i <= n; ++i) dis[i][1] = dis[i - 1][1] + (a[i] != a[i - 1]);
  dis[n][2] = a[1] != a[n];
  for (int i = n - 1; i >= 1; --i) dis[i][2] = dis[i + 1][2] + (a[i] != a[i + 1]);
  for (int i = 2; i <= m; ++i) dis[i][3] = dis[i - 1][3] + (b[i] != b[i - 1]);
  dis[m][4] = b[1] != b[m];
  for (int i = m - 1; i >= 1; --i) dis[i][4] = dis[i + 1][4] + (b[i] != b[i + 1]);
  int q = read();
  while (q--) {
    int x1 = read(), y1 = read(), x2 = read(), y2 = read();
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);
    printf ("%d\n", min(dis[x2][1] - dis[x1][1], dis[x1][1] + dis[x2][2]) + min(dis[y2][3] - dis[y1][3], dis[y1][3] + dis[y2][4]));
  }
}
