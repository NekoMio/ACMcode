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
bool Merge(double &L, double &R, double l, double r) {
  double LL = max(L, l), RR = min(R, r);
  if (RR < LL) return 0;
  else return L = LL, R = RR, 1;
}
bool Judge(double x) {
  int Num = 0;
  double h = x, d = 0;
  for (int i = 1; i <= n; i++) {
    double th = a[i].b + x, td = a[i].b - x;
    if (!Merge(h, d, th, td)) {
      Num++;
      h = th, d = td;
    }
  }
  if (Num > 2) return 0;
  else return 1;
}
int main() {
  n = read();
  for (int i = 1; i <= n; i++) {
    a[i].a = read(), a[i].b = read();
  }
  sort(a + 1, a + n + 1, [&](const data &c, const data &d) -> bool {
    return c.a < d.a;
  });
  double l = 0, r = 1e9;
  while (r - l > 1e-2) {
    double mid = (l + r) / 2;
    if (Judge(mid)) r = mid;
    else l = mid;
  }
  printf ("%.1f\n", l);
}