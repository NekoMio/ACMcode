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
const int MAXN = 500005;
struct DAT {
  int a, b, c;
  bool operator<(const DAT &d) const { return a < d.a; }
} a[MAXN];
int Minb[MAXN], Minc[MAXN], Maxb[MAXN], Maxc[MAXN];
int n, p, q, r;
int tag[MAXN << 2], Min[MAXN << 2];
long long Sum[MAXN << 2];
void Pushup(int rt) {
  Sum[rt] = Sum[rt << 1] + Sum[rt << 1 | 1];
  Min[rt] = min(Min[rt << 1], Min[rt << 1 | 1]);
}
void Pushdown(int rt, int m) {
  if (tag[rt]) {
    tag[rt << 1] = tag[rt << 1 | 1] = tag[rt];
    Sum[rt << 1] = 1ll * tag[rt] * (m - (m >> 1));
    Sum[rt << 1 | 1] = 1ll * tag[rt] * (m >> 1);
    Min[rt << 1] = Min[rt << 1 | 1] = tag[rt];
    tag[rt] = 0;
  }
}
void Set(int L, int R, int c, int l, int r, int rt) {
  if (L > R) return;
  if (L <= l && R >= r) {
    tag[rt] = c;
    Sum[rt] = 1ll * (r - l + 1) * c;
    Min[rt] = c;
    return;
  }
  Pushdown(rt, r - l + 1);
  int mid = l + r >> 1;
  if (L <= mid) Set(L, R, c, l, mid, rt << 1);
  if (R > mid) Set(L, R, c, mid + 1, r, rt << 1 | 1);
  Pushup(rt);
}
long long Query(int L, int R, int l, int r, int rt) {
  if (L > R) return 0;
  if (L <= l && R >= r) return Sum[rt];
  int mid = l + r >> 1;
  long long ans = 0;
  Pushdown(rt, r - l + 1);
  if (L <= mid) ans += Query(L, R, l, mid, rt << 1);
  if (R > mid) ans += Query(L, R, mid + 1, r, rt << 1 | 1);
  return ans;
}
int find(int c, int l, int r, int rt) {
  if (l == r) return l;
  int mid = l + r >> 1;
  Pushdown(rt, r - l + 1);
  int ans = 0;
  if (Min[rt << 1] < c)
    ans = find(c, l, mid, rt << 1);
  else
    ans = find(c, mid + 1, r, rt << 1 | 1);
  Pushup(rt);
  return ans;
}
void Update(int pos) {
  int x = find(a[pos].c + 1, 1, q, 1);
  Set(x, a[pos].b, a[pos].c + 1, 1, q, 1);
}
long long Query(int b0, int c0) {
  int x = find(c0, 1, q, 1);
  if (x - 1 >= b0) return 1ll * (x - b0) * (r + 1) - Query(b0, x - 1, 1, q, 1) + 1ll * (q - x + 1) * (r - c0 + 1);
  else return 1ll * (q - b0 + 1) * (r - c0 + 1);
}
int main() {
  n = read(), p = read(), q = read(), r = read();
  for (int i = 1; i <= n; ++i) {
    a[i].a = read(), a[i].b = read(), a[i].c = read();
  }
  sort(a + 1, a + n + 1);
  for (int i = n; i >= 1; i--) {
    Maxb[i] = max(Maxb[i + 1], a[i].b);
    Maxc[i] = max(Maxc[i + 1], a[i].c);
  }
  long long ans = 0;
  int pos = 1;
  for (int i = 1; i <= p; ++i) {
    while (a[pos].a < i && pos <= n) {
      Update(pos);
      pos++;
    }
    // for (int j = Maxb[pos] + 1; j <= q; ++j)
    //   printf ("%d %d %d\n", i, j, max(Query(j, j, 1, q, 1), Maxc[pos] + 1));
    ans += Query(Maxb[pos] + 1, Maxc[pos] + 1);
  }
  printf("%lld\n", ans);
}
