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
const int MAXN = 3005;
const double eps = 1e-9;
struct Point {
  double x, y;
  int color, id;
  Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
  void read() { x = ::read(), y = ::read(); }
  Point operator-(const Point &a) { return Point(x - a.x, y - a.y); }
  Point operator-(const Point &a) const { return Point(x - a.x, y - a.y); }
  double operator*(const Point &a) { return x * a.y - y * a.x; }
  double operator*(const Point &a) const { return x * a.y - y * a.x; }
  double operator==(const Point &a) const {
    return fabs(x - a.x) <= eps && fabs(y - a.y) <= eps;
  }
} a[MAXN], b[MAXN], c[MAXN << 1], Cvx[MAXN << 1];
#define sqr(_) ((_) * (_))
double dis(const Point &x, const Point &y) {
  return sqrt(sqr(x.x - y.x) + sqr(x.y - y.y));
}
bool cmp(Point x, Point y) {
  double s = (x - c[1]) * (y - c[1]);
  if (fabs(s) < eps) return dis(x, c[1]) < dis(y, c[1]);
  return s > 0;
}
int Run_Cvx(int n) {
  int top = 0;
  int k = 1;
  for (int i = 1; i <= n; i++) {
    if (c[i].x < c[k].x)
      k = i;
    else if (c[i].x == c[k].x && c[i].y < c[k].y)
      k = i;
  }
  swap(c[1], c[k]);
  // a[1].print();
  sort(c + 2, c + n + 1, cmp);
  Cvx[++top] = c[1];
  for (int i = 2; i <= n; i++) {
    if (c[i] == c[i - 1]) continue;
    while (top > 1 && (Cvx[top] - Cvx[top - 1]) * (c[i] - Cvx[top]) < 0) top--;
    Cvx[++top] = c[i];
  }
  return top;
}
set<int> st;
vector<pair<int, int> > ansA, ansB;
int Judge(int x) {
  int ans = 0;
  for (int i = 2; i <= x; ++i) {
    if (Cvx[i].color != Cvx[i - 1].color)
      ans++;
  }
  return ans;
}
int n, m, cnt;
int fa[MAXN << 1];
int find(int x) {
  if (fa[x] != x) fa[x] = find(fa[x]);
  return fa[x];
}
void link(const Point &x, const Point &y) {
  if (x.color == 1) {
    ansA.push_back(pair<int, int>(x.id, y.id));
  } else {
    ansB.push_back(pair<int, int>(x.id - n, y.id - n));
  }
  fa[find(x.id)] = find(y.id);
}
bool in(const Point &x, const Point &A, const Point &B, const Point &C) {
  double tmp1 = (A - B) * (x - B);
  double tmp2 = (B - C) * (x - C);
  double tmp3 = (C - A) * (x - A);
  if (tmp1 > 0 && tmp2 > 0 && tmp3 > 0) return 1;
  if (tmp1 < 0 && tmp2 < 0 && tmp3 < 0) return 1;
  return 0;
}
void Work(const Point &A, const Point &B, const Point &C) {
  bool flag1 = 0, flag2 = 0;
  int id1 = 0, id2 = 0;
  for (int i = 1; i <= n; ++i) {
    if (in(a[i], A, B, C)) {
      flag1 = 1;
      id1 = i;
      break;
    }
  }
  for (int i = 1; i <= m; ++i) {
    if (in(b[i], A, B, C)) {
      flag2 = 1;
      id2 = i;
      break;
    }
  }
  if (flag1 && flag2) {
    if (A.color == 1) {
      link(A, a[id1]);
      Work(B, A, a[id1]);
      Work(C, A, a[id1]);
      Work(a[id1], B, C);
    } else {
      link(A, b[id2]);
      Work(B, A, b[id2]);
      Work(C, A, b[id2]);
      Work(b[id2], B, C);
    }
  } else if (flag1 || flag2) {
    if (A.color == 1 && flag1) {
      for (int i = 1; i <= n; ++i) {
        if (in(a[i], A, B, C)) {
          link(A, a[i]);
        }
      }
    } else if (A.color == 2 && flag2) {
      for (int i = 1; i <= m; ++i) {
        if (in(b[i], A, B, C)) {
          link(A, b[i]);
        }
      }
    } else if (A.color == 1 && flag2) {
      for (int i = 1; i <= m; ++i) {
        if (in(b[i], A, B, C)) {
          link(B, b[i]);
        }
      }
    } else {
      for (int i = 1; i <= n; ++i) {
        if (in(a[i], A, B, C)) {
          link(B, a[i]);
        }
      }
    }
  }
}
int main() {
  n = read(), m = read(), cnt = 0;
  for (int i = 1; i <= n; ++i) {
    a[i].id = ++cnt;
    a[i].color = 1;
    a[i].read(), c[cnt] = a[i];
  }
  for (int i = 1; i <= m; ++i) {
    b[i].id = ++cnt;
    b[i].color = 2;
    b[i].read(), c[cnt] = b[i];
  }
  for (int i = 1; i <= cnt; ++i) fa[i] = i;
  cnt = Run_Cvx(cnt);
  int Num = Judge(cnt);
  if (Num == 0) {
    for (int i = 2; i <= cnt; ++i) {
      link(Cvx[i - 1], Cvx[i]);
    }
    if (Cvx[1].color == 1) {
      for (int i = 2; i <= cnt; ++i) {
        Work(b[1], Cvx[i - 1], Cvx[i]);
      }
      Work(b[1], Cvx[cnt], Cvx[1]);
    } else {
      for (int i = 2; i <= cnt; ++i) {
        Work(a[1], Cvx[i - 1], Cvx[i]);
      }
      Work(a[1], Cvx[cnt], Cvx[1]);
    }
    // fprintf (stderr, "%d\n", ansA.size());
    // fprintf (stderr, "%d\n", ansB.size());
    for (auto x : ansA) {
      printf ("%d %d\n", x.first, x.second);
    }
    for (auto x : ansB) {
      printf ("%d %d\n", x.first, x.second);
    }
  } else if (Num == 2 || Num == 1) {
    int S = 0;
    for (int i = 2; i <= cnt; ++i) {
      if (Cvx[i].color != Cvx[i - 1].color) {
        S = i;
        break;
      }
    }
    int z = 0;
#define nxt(_) ((_) == cnt ? 1 : (_) + 1)
#define pre(_) ((_) == 1 ? cnt : (_) - 1)
    for (z = nxt(S); Cvx[z].color == Cvx[S].color; z = nxt(z)) {
      link(Cvx[z], Cvx[pre(z)]);
    }
    for (int i = nxt(z); Cvx[z].color == Cvx[i].color; i = nxt(i)) {
      link(Cvx[i], Cvx[pre(i)]);
    }
    for (int i = nxt(S); Cvx[i].color == Cvx[S].color; i = nxt(i)) {
      Work(Cvx[z], Cvx[pre(i)], Cvx[i]);
    }
    for (int i = nxt(z); Cvx[i].color == Cvx[z].color; i = nxt(i)) {
      Work(Cvx[S], Cvx[pre(i)], Cvx[i]);
    }
    for (auto x : ansA) {
      printf ("%d %d\n", x.first, x.second);
    }
    for (auto x : ansB) {
      printf ("%d %d\n", x.first, x.second);
    }
  } else {
    printf ("GG!\n");
  }
}
