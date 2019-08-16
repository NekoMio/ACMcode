#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
const int MAXN = 1e5 + 5;
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
const int MAXM = 1e6;
struct Node {
  Node *ch[2];
  int s;
} * root[MAXN], *null;
Node *NewNode() {
  Node *rt = new Node();
  rt->ch[0] = null, rt->ch[1] = null;
  rt->s = 0;
  return rt;
}
void Copy(Node *&rt2, Node *rt1) {
  if (rt1 == null)
    return rt2 = null, void();
  else
    rt2 = NewNode(), *rt2 = *rt1;
}
void Add(Node *rt1, Node *&rt2, int x, int l, int r) {
  Copy(rt2, rt1);
  if (rt2 == null) rt2 = NewNode();
  if (l == r) {
    rt2->s = 1;
    return;
  }
  int mid = l + r >> 1;
  if (x <= mid)
    Add(rt1->ch[0], rt2->ch[0], x, l, mid);
  else
    Add(rt1->ch[1], rt2->ch[1], x, mid + 1, r);
  rt2->s++;
}
int Query(Node *rt1, Node *rt2, int L, int R, int l, int r) {
  if (L <= l && R >= r) return rt2->s - rt1->s;
  int mid = l + r >> 1;
  int ans = 0;
  if (L <= mid) ans += Query(rt1->ch[0], rt2->ch[0], L, R, l, mid);
  if (R > mid) ans += Query(rt1->ch[1], rt2->ch[1], L, R, mid + 1, r);
  return ans;
}
bool Judge(int L, int R, int p, int mid, int k) {
  return Query(root[L - 1], root[R], max(p - mid, 1), min(p + mid, MAXM), 1,
               MAXM) >= k;
}
int solve(int L, int R, int p, int k) {
  int l = 0, r = MAXM, ans = 0;
  while (l < r) {
    int mid = l + r >> 1;
    if (Judge(L, R, p, mid, k))
      ans = mid, r = mid;
    else
      l = mid + 1;
  }
  return ans;
}
int main() {
  int T = read();
  null = new Node();
  null->ch[0] = null->ch[1] = null;
  while (T--) {
    root[0] = null;
    int n = read(), m = read();
    for (int i = 1; i <= n; i++) Add(root[i - 1], root[i], read(), 1, MAXM);
    int lastans = 0;
    for (int i = 1; i <= m; i++) {
      int l = read() ^ lastans, r = read() ^ lastans, p = read() ^ lastans,
          k = read() ^ lastans;
      printf("%d\n", lastans = solve(l, r, p, k));
    }
  }
  // while (1);
}