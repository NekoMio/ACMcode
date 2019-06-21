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
const long long INF = 0x3f3f3f3f3f3f3f3f;
struct Node {
  Node *ch[2];
  long long A, B, HA, HB;
  bool flag;
  Node() {
    ch[0] = ch[1] = NULL;
    A = B = HA = HB = 0;
    flag = 0;
  }
}*root;
void Build(Node *&rt, int l, int r) {
  rt = new Node();
  if (l == r) {
    rt->B = rt->HB = read();
    return;
  }
  int mid = l + r >> 1;
  Build(rt->ch[0], l, mid);
  Build(rt->ch[1], mid + 1, r);
}
void Pushtag(Node *rt, long long a, long long b, long long ha, long long hb) {
  rt->HA = max(rt->HA, rt->A + ha), rt->HB = max(rt->HB, max(rt->B + ha, hb));
  rt->A = max(-INF, rt->A + a), rt->B = max(rt->B + a, b);
  rt->flag = 1;
}
void Pushdown(Node *rt) {
  if (rt->flag) {
    Pushtag(rt->ch[0], rt->A, rt->B, rt->HA, rt->HB);
    Pushtag(rt->ch[1], rt->A, rt->B, rt->HA, rt->HB);
    rt->A = rt->B = rt->HA = rt->HB = rt->flag = 0;
  }
}
void Update(Node *rt, int l, int r, int L, int R, long long a, long long b) {
  if (L <= l && R >= r) {
    Pushtag(rt, a, b, a, b);
    return;
  }
  int mid = l + r >> 1;
  Pushdown(rt);
  if (L <= mid) Update(rt->ch[0], l, mid, L, R, a, b);
  if (R > mid) Update(rt->ch[1], mid + 1, r, L, R, a, b);
}
long long Query(Node *rt, int l, int r, int x, int op) {
  if (l == r) return op ? max(rt->A, rt->B) : max(rt->HA, rt->HB);
  int mid = l + r >> 1;
  Pushdown(rt);
  if (x <= mid) return Query(rt->ch[0], l, mid, x, op);
  else return Query(rt->ch[1], mid + 1, r, x, op);
}
int main() {
  int n = read(), m = read();
  Build(root, 1, n);
  while (m--) {
    int t = read();
    if (t == 1) {
      int l = read(), r = read(), x = read();
      Update(root, 1, n, l, r, x, 0);
    }
    if (t == 2) {
      int l = read(), r = read(), x = read();
      Update(root, 1, n, l, r, -x, 0);
    }
    if (t == 3) {
      int l = read(), r = read(), x = read();
      Update(root, 1, n, l, r, -INF, x);
    }
    if (t == 4) {
      printf ("%lld\n", Query(root, 1, n, read(), 1));
    }
    if (t == 5) {
      printf ("%lld\n", Query(root, 1, n, read(), 0));
    }
  }
}
