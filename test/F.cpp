#include <bits/stdc++.h>
using namespace std;
struct Point {
  double x, y;
}a[1005], b[1005];
double d[1005];
int ans[1005];
double dis(Point &a, Point &b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
int main() {
  int n, m;
  while (scanf ("%d%d", &n, &m)) {
    if (n == 0 && m == 0) break;
    getchar();
    for (int i = 1; i <= n; i++) 
      scanf("%*c%lf%*c%lf%*c", &a[i].x, &a[i].y);
    for (int i = 1; i <= m; i++)
      scanf("(%lf,%lf)", &b[i].x, &b[i].y);
    for (int i = 1; i <= m; i++)
      scanf ("%lf", &d[i]);
    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= n; j++) {
        if (dis(b[i], a[j]) <= d[i])
          ans[i]++;
      }
    }
    for (int i = 1; i <= m; i++)
      printf ("%d ", ans[i]), ans[i] = 0;
  }
}