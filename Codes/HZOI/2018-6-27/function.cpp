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
const int MAXN = 5e5 + 5;
int A[MAXN];
struct data {
  int x, y, id;
  bool operator < (const data &a) const {
    return y < a.y;
  }
}Q[MAXN];
struct line {
  long long x, y, k;
  bool operator < (const line &a) const {
    return x > a.x;
  }
}st[MAXN];
const int INF = 0x3f3f3f3f;
line CrossPoint(const line &x, const line &y) {
  long double a1 = x.k, a2 = y.k, b1 = -1, b2 = -1, c1 = x.y - 1ll * x.x * x.k, c2 = y.y - 1ll * y.x * y.k;
  long long X;
  if (y.k != 0) X = ceil((b1 * c2 - c1 * b2) / (a1 * b2 - a2 * b1));
  else X = 0;
  long long Y = a1 * X + c1;
  return (line) {X, Y, 0};
}
bool Cross(const line &x, const line &y, int nxtx) {
  long long val1 = x.k * nxtx + x.y - x.x * x.k;
  long long val2 = y.k * nxtx + y.y - y.x * y.k;
  if (val1 <= val2) return 1;
  else return 0;
}
int bound(int l, int r, int x) {
  int ans = r + 1;
  while (l <= r) {
    int mid = l + r >> 1;
    if (st[mid].x <= x) ans = mid, r = mid - 1;
    else l = mid + 1;
  }
  return ans;
}
long long Query(int x, int t) {
  int tmp = bound(1, t, x);
  return st[tmp].k * x + st[tmp].y - st[tmp].x * st[tmp].k;
}
long long ans[MAXN];
int main() {
  // freopen ("test/function2.in", "r", stdin);
  // freopen ("function.out", "w", stdout);
  int n = read();
  for (int i = 1; i <= n; ++i)
    A[i] = read();
  int q = read();
  for (int i = 1; i <= q; ++i) Q[i].x = read(), Q[i].y = read(), Q[i].id = i;
  sort(Q + 1, Q + q + 1);
  int top = 0, s = 1;
  long long Val = 0;
  for (int i = 1; i <= n; ++i) {
    Val += A[i];
    while (top > 0 && st[top].k >= A[i]) top--;
    while (top > 0 && !Cross(st[top], (line){0 - i, 0 - Val, A[i]}, top == 1 ? INF : st[top - 1].x)) top--;
    line c = CrossPoint(st[top], (line){0 - i, 0 - Val, A[i]});
    if (top != 0) st[top].x = c.x, st[top].y = c.y;
    st[++top] = (line){0 - i, 0 - Val, A[i]};
    while (Q[s].y == i) {
      ans[Q[s].id] = Query(Q[s].x - i, top) + Val;
      s++;
    }
  }
  for (int i = 1; i <= q; ++i)
    printf ("%lld\n", ans[i]);
}
