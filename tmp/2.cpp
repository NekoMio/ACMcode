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
const int MAXN = 1005;
const int eps = 1e6;
struct Point {
  long long a, b;
  Point(const double &_a = 0, const double &_b = 0) {
    a = round(_a * eps), b = round(_b * eps);
  }
  bool operator == (const Point &c) const {
    return a == c.a && b == c.b;
  }
};
struct data {
  int a, b;
  bool operator < (const data &c) const {
    return a == c.a ? b < c.b : a < c.a;
  }
  bool operator == (const data &c) const {
    return a == c.a && b == c.b;
  }
}v[MAXN];
Point Cross(const data &a, const data &b) {
  double x = (1.0 * (a.b - b.b) / (a.a - b.a) + 1.0 * (a.a + b.a)) / 2;
  double y = (x - a.a) * (x - a.a) + a.b;
  return Point(x, y);
}
struct Hash_Table {
  struct edge {
    int next, v;
    Point a;
  }v[MAXN * MAXN];
  // 9901 7717
  int first[1010], p;
  Hash_Table() {
    memset (first, -1, sizeof (first));
    p = 0;
  }
  int &operator[] (const Point &a) {
    int H = (a.a % 9901 + 9901) * (a.b % 7717 + 7717) % 1009;
    for (int i = first[H]; i != -1; i = v[i].next) {
      if (v[i].a == a) {
        return v[i].v;
      }
    }
    v[p].a = a;
    v[p].next = first[H];
    first[H] = p++;
    return v[p - 1].v = 0;
  }
  void clear() {
    memset (first, -1, sizeof (first));
    p = 0;
  }
}mp;
int main() {
  int n = read();
  for (int i = 1; i <= n; i++)
    v[i].a = read(), v[i].b = read();
  sort(v + 1, v + n + 1);
  n = unique(v + 1, v + n + 1) - v - 1;
  int ans = 1;
  for (int i = 1; i <= n; i++) {
    ans++;
    mp.clear();
    for (int j = 1; j < i; j++) {
      if (v[i].a != v[j].a) {
        int &t = mp[Cross(v[i], v[j])];
        if (t == 0) {
          ans++;
          t++;
        }
      }
    }
  }
  printf ("%d\n", ans);
}