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
const int MAXN = 200005;
struct data {
  int a, b;
  bool operator < (const data &c) const {
    return a < c.a;
  }
}a[MAXN];
struct Node {
  Node *ch[2];
  int s;
  Node() {
    ch[0] = ch[1] = NULL;
    s = 0;
  }
}*root[MAXN], *null;
Node *NewNode() {
  Node *o = new Node();
  o->ch[0] = o->ch[1] = null;
  return o;
}
void Copy(Node *&rt1, Node *rt2) {
  if (rt2 == null) rt1 = null;
  else rt1 = NewNode(), *rt1 = *rt2;
}
void Update(Node *&rt1, Node *rt2, int x, int l, int r) {
  Copy(rt1, rt2);
  if (rt1 == null) rt1 = NewNode();
  rt1->s++;
  if (l == r) return;
  int mid = l + r >> 1;
  if (x <= mid) Update(rt1->ch[0], rt2->ch[0], x, l, mid);
  else Update(rt1->ch[1], rt2->ch[1], x, mid + 1, r);
}
int Query(Node *rt1, Node *rt2, int L, int R, int l, int r) {
  if (L <= l && R >= r)
    return rt2->s - rt1->s;
  int mid = l + r >> 1;
  int ans = 0;
  if (L <= mid) ans += Query(rt1->ch[0], rt2->ch[0], L, R, l, mid);
  if (R > mid) ans += Query(rt1->ch[1], rt2->ch[1], L, R, mid + 1, r);
  return ans;
}
int pos[MAXN], n, q;
int Query(int l, int r) {
  int val = r - l + 1;
  return val - Query(root[pos[l] - 1], root[pos[r + 1] - 1], l, r, 1, n);
}
int main() {
  // freopen ("lct.in", "r", stdin);
  // freopen ("lct.out", "w", stdout);
  null = new Node();
  null->ch[0] = null->ch[1] = null;
  n = read(), q = read();
  for (int i = 1; i < n; ++i)
    a[i].a = read(), a[i].b = read();
  sort(a + 1, a + n);
  root[0] = null;
  for (int i = 1; i < n; ++i)
    Update(root[i], root[i - 1], a[i].b, 1, n);
  int id = 1;
  for (int i = 1; i < n; ++i) {
    while (id <= a[i].a && id <= n) {
      pos[id] = i;
      id++;
    }
  }
  while (id <= n + 1) pos[id] = n, id++;
  while (q--) {
    int l = read(), r = read();
    printf ("%d\n", Query(l, r));
  }
}
