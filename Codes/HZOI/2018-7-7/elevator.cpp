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
const int MAXN = 1e6 + 5;
const long long INF = 0x3f3f3f3f3f3f3f3f;
struct data {
  int a, b;
  bool operator < (const data &c) const {
    return a < c.a;
  }
}a[MAXN];
long long f[MAXN];
int st[MAXN], top;
struct Node {
  Node *ch[2];
  long long Min;
  Node() {
    ch[0] = ch[1] = NULL;
    Min = INF;
  }
  void Pushup() {
    Min = min(ch[0]->Min, ch[1]->Min);
  }
}*rt;
void Build(Node *&rt, int l, int r) {
  rt = new Node();
  if (l == r) return;
  int mid = l + r >> 1;
  Build(rt->ch[0], l, mid);
  Build(rt->ch[1], mid + 1, r);
}
long long Query(Node *rt, int L, int R, int l, int r) {
  if (L <= l && R >= r)
    return rt->Min;
  int mid = l + r >> 1;
  long long ans = INF;
  if (L <= mid) ans = min(ans, Query(rt->ch[0], L, R, l, mid));
  if (R > mid) ans = min(ans, Query(rt->ch[1], L, R, mid + 1, r));
  return ans;
}
void Update(Node *rt, int x, long long c, int l, int r) {
  if (l == r) {
    rt->Min = min(rt->Min, c);
    return;
  }
  int mid = l + r >> 1;
  if (x <= mid) Update(rt->ch[0], x, c, l, mid);
  else Update(rt->ch[1], x, c, mid + 1, r);
  rt->Pushup();
}
int main() {
  // freopen ("elevator.in", "r", stdin);
  // freopen ("elevator.out", "w", stdout);
  int n = read();
  for (int i = 1; i <= n; ++i) a[i].a = read(), a[i].b = read();
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; ++i) {
    while (top > 0 && a[st[top]].b <= a[i].b) top--;
    st[++top] = i;
  }
  for (int i = 1; i <= top; ++i) a[i] = a[st[i]];
  n = top;
  Build(rt, 0, n);
  memset (f, 0x3f, sizeof (f));
  f[0] = 0;
  Update(rt, 0, 2 * a[1].a, 0, n);
  for (int i = 1; i <= n; ++i) {
    int t = upper_bound(f + 0, f + i, a[i].a) - f - 1;
    f[i] = a[i].a + 2ll * a[t + 1].b;
    f[i] = min(f[i], Query(rt, t + 1, i - 1, 0, n));
    Update(rt, i, f[i] + 2ll * a[i + 1].b, 0, n);
  }
  printf ("%lld\n", f[n]);
}
