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
struct Point {
  int x, y;
  bool operator < (const Point &c) const {
    return x == c.x ? y < c.y : x < c.x;
  }
}c[5000], d[5000];
map<Point, int> mp;
double Rand()
{
    return 1.0 * rand() / RAND_MAX;
}
double dis(Point &a, Point &b) {
  return sqrt(1.0 * (a.x - b.x) * (a.x - b.x) + 1.0 * (a.y - b.y) * (a.y - b.y));
}
int a[5000];
int n, cnt;
double Calc() {
  double ans = 0;
  for (int i = 2; i <= n; ++i) {
    ans += dis(c[a[i]], c[a[i - 1]]);
  }
  ans += dis(c[a[1]], c[a[n]]);
  return ans;
}
int main() {
  srand(time(NULL));
  n = read(), cnt = 0;
  for (int i = 1; i <= n; ++i) {
    Point a, b;
    a.x = read(), a.y = read(), b.x = read(), b.y = read();
    if (!mp.count(a)) {
      mp[a] = ++cnt;
      c[cnt] = a;
      d[cnt] = b;
    }
  }
  for (int i = 1; i <= n; ++i) a[i] = i;
  double ans = Calc();
  double T = 1e18, mint = 1e-6, delta = 0.9999;
  while (T > mint) {
    int t = rand() % n + 1;
    int z = rand() % n + 1;
    swap(a[t], a[z]);
    double tmp = Calc();
    if (tmp < ans || exp((ans - tmp) / T) > Rand()) {
      ans = tmp;
    } else swap(a[t], a[z]);
    T *= delta;
  }
  printf ("%d\n", n * 2);
  for (int i = 1; i <= n; ++i) {
    printf ("%d %d\n", c[a[i]].x, c[a[i]].y);
    printf ("%d %d\n", d[a[i]].x, d[a[i]].y);
  }
}
