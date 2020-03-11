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
struct data {
  int a, b;
}a[300005];
int n;
bool Merge(double &R, double &L, double r, double l) {
  double LL = max(L, l), RR = min(R, r);
  if (RR < LL) return 0;
  else return L = LL, R = RR, 1;
}
bool Judge(double x) {
  int Num = 0;
  double x1 = 0, x2 = 0;
  double h = -1, d = -1;
  int i;
  for (i = 1; i <= n; i++) {
    if (a[i].b - 0 > x) break;
  }
  Num = 0;
  for (; i <= n; i++) {
    double th = a[i].b + x, td = max(a[i].b - x, 0.);
    if (!Merge(h, d, th, td)) {
      if (Num == 1) {
        x1 = d;
      }
      Num++;
      h = th, d = td;
    }
  }
  if (Num == 2) {
    x2 = h;
  }
  if (Num > 2) return 0;
  else if (x1 > x2) return 0;
  else return 1;
}
int main() {
  n = read();
  double r = 0;
  for (int i = 1; i <= n; i++) {
    a[i].a = read(), a[i].b = read();
    r = max(r, a[i].b * 1.);
  }
  sort(a + 1, a + n + 1, [&](const data &c, const data &d) -> bool {
    return c.a < d.a;
  });
  double l = 0;
  if (a[1].a == 0) {
    l = a[1].b;
  }
  while (r - l > 1e-2) {
    double mid = (l + r) / 2;
    if (Judge(mid)) r = mid;
    else l = mid;
  }
  printf ("%.1f\n", l);
}