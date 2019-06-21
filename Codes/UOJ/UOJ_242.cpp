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
const int INF = 0x3f3f3f3f;
const int MAXN = 1e5 + 5;
const long double pi = acos(-1.);
int n;
struct Point {
  long double x, y;
  Point() {}
  Point(long double _x, long double _y): x(_x), y(_y) {}
  bool operator < (const Point &a) const {
    return x < a.x;
  }
  Point operator - (const Point &a) {
    return Point(x - a.x, y - a.y);
  }
  double operator * (const Point &a) {
    return x * a.y - y * a.x;
  }
};
struct line {
  Point a, b;
  long double k;
  line() {}
  line(const Point &_a, const Point &_b) {
    a = _a, b = _b;
  }
}c[MAXN], s;
Point Cross(line a, line b) {
  double x = (b.a - a.a) * (b.b - a.a);
  double y = (b.b - a.b) * (b.a - a.b);
  double t = x / (x + y);
  return Point(a.a.x + (a.b.x - a.a.x) * t, a.a.y + (a.b.y - a.a.y) * t);
}
Point Mid(const Point &a, const Point &b) {
  return Point((a.x + b.x) / 2, (a.y + b.y) / 2);
}
long double K(const line &a) {
  return atan2l(a.b.y - a.a.y, a.b.x - a.a.x);
}
struct data {
  Point p;
  int id;
  bool operator < (const data &c) const {
    return p < c.p;
  }
}p[MAXN];
multiset<long double> st;
int cnt = 0;
bool Judge(long double x, long double y, int op) {
  if (op) x += 2 * pi;
  return x - y > pi - 1e-13;
}
void Delete(long double x) {
  multiset<long double>::iterator pre, nxt, it;
  int tmp1 = 0, tmp2 = 0;
  pre = nxt = it = st.find(x);
  if (pre == st.begin()) pre = --st.end(), tmp1 = 1;
  else --pre;
  if (++nxt == st.end()) nxt = st.begin(), tmp2 = 1;
  cnt = cnt + Judge(*nxt, *pre, tmp1 || tmp2) - Judge(*it, *pre, tmp1) - Judge(*nxt, *it, tmp2);
  st.erase(it);
}
void Insert(long double x) {
  multiset<long double>::iterator pre, nxt, it;
  int tmp1 = 0, tmp2 = 0;
  pre = nxt = it = st.insert(x);
  if (pre == st.begin()) pre = --st.end(), tmp1 = 1;
  else --pre;
  if (++nxt == st.end()) nxt = st.begin(), tmp2 = 1;
  cnt = cnt - Judge(*nxt, *pre, tmp1 || tmp2) + Judge(*it, *pre, tmp1) + Judge(*nxt, *it, tmp2);
}
void Init(Point x) {
  for (int i = 1; i <= n; ++i) {
    if ((c[i].a - x) * (c[i].b - x) < 0)
      st.insert(c[i].k = K(c[i]));
    else st.insert(c[i].k = K(line(c[i].b, c[i].a)));
  }
  cnt += Judge(*st.begin(), *(--st.end()), 1);
  for (auto t1 = st.begin(), t2 = ++st.begin(); t2 != st.end(); t1++, t2++)
    cnt += Judge(*t2, *t1, 0);
}
int main() {
  n = read();
  Point a, b;
  for (int i = 1; i <= n; ++i) {
    a.x = read(), a.y = read(), b.x = read(), b.y = read( );
    c[i] = line(a, b);
  }
  a.x = read(), a.y = read(), b.x = read(), b.y = read();
  s = line(a, b);
  for (int i = 1; i <= n; ++i)
    p[i].p = Cross(s, c[i]), p[i].id = i;
  sort(p + 1, p + n + 1);
  printf ("0");
  Init(Mid(p[1].p, Cross(s, line(Point(p[1].p.x - 1, -1), Point(p[1].p.x - 1, 1)))));
  for (int i = 1; i < n; ++i) {
    int t = p[i].id;
    Delete(c[t].k);
    c[t].k += pi;
    if (c[t].k > pi) c[t].k -= 2 * pi;
    Insert(c[t].k);
    printf (cnt == 0 ? "1" : "0");
  }
  printf ("0\n");
}
