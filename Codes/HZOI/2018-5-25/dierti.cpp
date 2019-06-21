#include <bits/stdc++.h>
#undef Mine
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
const int MAXN = 100005;
struct Point {
  double x, y;
  Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
  Point operator+(const Point &a) const { return Point(x + a.x, y + a.y); }
  Point operator-(const Point &a) const { return Point(x - a.x, y - a.y); }
  double operator*(const Point &b) const { return x * b.y - b.x * y; }
};
struct line {
  long double a, b, c, k;
  int id;
  line() {}
  line(double _a, double _b, double _c, int _id) {
    id = _id;
    a = _a, b = _b, c = _c;
    k = atan2(-a, b);
  }
  bool operator==(const line &s) const {
    return fabs(a - s.a) <= 1e-13 && fabs(b - s.b) <= 1e-13 &&
           fabs(c - s.c) <= 1e-13;
  }
} l[MAXN], tmp[MAXN];
Point Cross(const line &a, const line &b) {
  double x = (a.b * b.c - a.c * b.b) / (a.a * b.b - b.a * a.b);
  double y = (a.a * b.c - a.c * b.a) / (a.b * b.a - b.b * a.a);
  return Point(x, y);
}
bool cmp(const line &a, const line &b) {
  if (a.k == b.k) return a.c < b.c;
  return a.k < b.k;
}
bool Judge(const line &a, const Point &x) {
  return a.a * x.x + a.b * x.y + a.c < 0;
}
int cnt;
void addline(double a, double b, double c) {
  if (a != 0) b /= fabs(a), c /= fabs(a), a /= fabs(a);
#ifdef Mine
  printf("%.3f %.3f %.3f %.3f\n", a, b, c, atan2(-a, b));
#endif
  cnt++;
  l[cnt] = line(a, b, c, cnt);
}
double w[MAXN], d[MAXN], f[MAXN], c[MAXN], k[MAXN], L[MAXN], ans[MAXN], Sumlen,
    Sum1, Sum2, Sum3;
int q[MAXN];
bool Test(int n, int a) {
  for (int i = 1; i < n - 1; ++i)
    if (w[i] != w[i + 1]) return 0;
  for (int i = 1; i <= n; ++i)
    if (d[i] != 1) return 0;
  return w[n - 1] < a;
}
int fa[MAXN], size[MAXN];
int main() {
  // freopen ("dierti7.in", "r", stdin);
  // freopen ("dierti1.out", "w", stdout);
  int n = read(), a = read(), b = read();
  for (int i = 1; i <= n - 1; ++i) scanf("%lf", w + i);
  w[n] = a;
  for (int i = 1; i <= n; ++i) scanf("%lf", d + i);
  if (Test(n, a)) {
    for (int i = 1; i <= n - 1; ++i) printf("0.000\n");
    printf("1.000\n");
    return 0;
  } else if (a == b) {
    L[n] = d[1];
    for (int i = n - 1; i >= 1; --i) L[i] = L[i + 1] + d[i + 1];
    Sumlen = L[1];
    for (int i = 1; i <= n; ++i)
      Sum1 += L[i] * w[i], Sum2 += L[i] * L[i] * w[i], Sum3 += w[i];
    for (int i = 1; i <= n; ++i) {
      c[i] = Sum1 * Sumlen - Sum2;
      Sum1 = Sum1 - Sumlen * w[i];
      Sum2 = Sum2 - Sumlen * Sumlen * w[i];
      Sum2 = Sum2 + 2 * d[i + 1] * Sum1 + Sum3 * d[i + 1] * d[i + 1];
      Sum1 = Sum1 + d[i + 1] * Sum3;
    }
    double Min = 1e60;
    int Sum = 0;
    for (int i = 1; i <= n; ++i) {
      if (c[i] - Min < -1e-13) {
        Min = c[i];
        Sum = 1;
      } else if (fabs(c[i] - Min) <= 1e-13) {
        Sum++;
      }
    }
    for (int i = 1; i <= n; ++i) {
      if (fabs(c[i] - Min) <= 1e-13) {
        printf("%.3f\n", 1.0 / Sum);
      } else
        printf("0.000\n");
    }
  } else {
    L[n] = d[1];
    for (int i = n - 1; i >= 1; --i) L[i] = L[i + 1] + d[i + 1];
    Sumlen = L[1];
    for (int i = 1; i <= n; ++i)
      Sum1 += L[i] * w[i], Sum2 += L[i] * L[i] * w[i], Sum3 += w[i];
    for (int i = 1; i <= n; ++i) {
      c[i] = Sum1 * Sumlen - Sum2;
      Sum1 = Sum1 - Sumlen * w[i];
      Sum2 = Sum2 - Sumlen * Sumlen * w[i];
      Sum2 = Sum2 + 2 * d[i + 1] * Sum1 + Sum3 * d[i + 1] * d[i + 1];
      Sum1 = Sum1 + d[i + 1] * Sum3;
    }
    for (int i = 1; i <= n; ++i)
      addline((L[i] - d[1]) * (Sumlen - L[i] + d[1]), -1, c[i]);
    addline(1, 0, 0);
    addline(-1, 0, (b - a));
    sort(l + 1, l + cnt + 1, cmp);
    for (int i = 1; i <= n; ++i) fa[i] = i, size[i] = 1;
    for (int i = 2; i <= cnt; ++i) {
      if (l[i] == l[i - 1]) {
        fa[l[i].id] = fa[l[i - 1].id];
        size[fa[l[i].id]]++;
      }
    }
#ifdef Mine
    printf("\n");
    for (int i = 1; i <= cnt; ++i) {
      printf("%.3f %.3f %.3f\n", l[i].a, l[i].b, l[i].c);
    }
    for (int i = 1; i <= n; ++i) {
      printf("%d %d\n", i, fa[i]);
    }
#endif
    int h = 1, t = 0;
    // q[1] = 1, q[2] = 2;
    int top = 0;
    tmp[++top] = l[1];
    for (int i = 2; i <= cnt; ++i)
      if (l[i].k - l[i - 1].k >= 1e-18) tmp[++top] = l[i];
#ifdef Mine
    printf("\n");
    for (int i = 1; i <= top; ++i) {
      printf("%.3f %.3f %.3f %.10f %d\n", (double)tmp[i].a, (double)tmp[i].b, (double)tmp[i].c, (double)tmp[i].k, tmp[i].id);
    }
#endif
    for (int i = 1; i <= top; ++i) {
      while (t > h && Judge(tmp[i], Cross(tmp[q[t]], tmp[q[t - 1]]))) t--;
      while (t > h && Judge(tmp[i], Cross(tmp[q[h]], tmp[q[h + 1]]))) h++;
      q[++t] = i;
    }
    while (t > h && Judge(tmp[q[h]], Cross(tmp[q[t]], tmp[q[t - 1]]))) t--;
    while (t > h && Judge(tmp[q[t]], Cross(tmp[q[h]], tmp[q[h + 1]]))) h++;
#ifdef Mine
    printf("\n");
    for (int i = h; i <= t; ++i) {
      printf("%.3f %.3f %.3f %.10f %d\n", (double)tmp[q[i]].a, (double)tmp[q[i]].b, (double)tmp[q[i]].c, (double)tmp[q[i]].k, tmp[q[i]].id);
    }
#endif
#define pre(_) ((_) == h ? (t) : (_)-1)
#define nxt(_) ((_) == t ? (h) : (_) + 1)
    for (int i = h; i <= t; ++i) {
      double x1 = Cross(tmp[q[pre(i)]], tmp[q[i]]).x,
             x2 = Cross(tmp[q[i]], tmp[q[nxt(i)]]).x;
#ifdef Mine
      printf("%.4f %.4f\n", x1, x2);
#endif
      // if (x2 >= 0 && x1 <= b - a)
      ans[tmp[q[i]].id] = fabs(x2 - x1) / (b - a) / size[tmp[q[i]].id];
    }
#undef pre
#undef nxt
    for (int i = 1; i <= n; ++i) {
      ans[i] = ans[fa[i]];
      printf("%.3f\n", ans[i]);
    }
  }
}
